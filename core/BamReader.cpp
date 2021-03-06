#include "BamReader.h"

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace scbayes
{
	BamReader::BamReader(const std::string& path, BarCodeContainer::SharedPtr barcodeContainer) :
		m_path(path), m_bar_code_container(barcodeContainer), m_thread_pool(std::thread::hardware_concurrency() * 2)
	{
	}

	BamReader::~BamReader()
	{
		std::lock_guard< std::mutex > l(this->m_bam_readers_mutex);
		for (auto iter : this->m_bam_readers)
		{
			iter.second->Close();
		}
	}

	void BamReader::processVariants(const std::vector< Variant::SharedPtr >& variantPtrs)
	{
		for (auto variantPtr : variantPtrs)
		{
			auto funct = [this, variantPtr]()
				{
					this->processVariantCounts(variantPtr);
				};
			m_thread_pool.enqueue(funct);
		}
		m_thread_pool.join();
	}

	void BamReader::processVariantCounts(Variant::SharedPtr variantPtr)
	{
		std::shared_ptr< BamTools::BamReader > bamtoolsReader = getBamToolsReader();
		Region::SharedPtr regionPtr = variantPtr->getRegionPtr();
		int refID = bamtoolsReader->GetReferenceID(regionPtr->getReferenceID());
		if (!bamtoolsReader->SetRegion(refID, regionPtr->getStartPosition(Region::BASED::ZERO), refID, regionPtr->getEndPosition(Region::BASED::ZERO)))
		{
			std::cout << "Reader was not able to go to the region: " << regionPtr->getRegionString() << " so it was skipped" << std::endl;
			return;
		}

		BamTools::BamAlignment* bamtoolsAlignmentPtr = new BamTools::BamAlignment();
		uint32_t startPosition = regionPtr->getStartPosition(Region::BASED::ZERO);
		uint32_t endPosition = regionPtr->getEndPosition(Region::BASED::ZERO);
		while (bamtoolsReader->GetNextAlignment(*bamtoolsAlignmentPtr))
		{
			if (bamtoolsAlignmentPtr->AlignedBases.find('N') != std::string::npos) { continue; }
			bool isInRegion = (bamtoolsAlignmentPtr->Position <= startPosition && startPosition <= (bamtoolsAlignmentPtr->Position + bamtoolsAlignmentPtr->Length));
			std::string alignmentBarcode;
			std::string umi;
			bamtoolsAlignmentPtr->GetTag("UB", umi);
			if (isInRegion && !bamtoolsAlignmentPtr->IsDuplicate() && bamtoolsAlignmentPtr->GetTag("CB", alignmentBarcode) && this->m_bar_code_container->doesBarCodeExist(alignmentBarcode))
			{
                uint32_t offset = (startPosition - bamtoolsAlignmentPtr->Position);
				std::string alignmentSequenceRefLength = bamtoolsAlignmentPtr->QueryBases.substr(offset, variantPtr->getRef().size());
				/*
				static std::mutex l;
				l.lock();
				if (alignmentBarcode.compare("CTACCCACAACGATGG-1") == 0)
				{
					std::string alignmentSequenceAltLength = bamtoolsAlignmentPtr->QueryBases.substr(offset, variantPtr->getAlt().size());
					std::cout << "--------------------" << std::endl;
					std::cout << "offset: " << offset << std::endl;
					std::cout << "UMI: " << umi << std::endl;
					std::cout << "Position: " << bamtoolsAlignmentPtr->Position << std::endl;
					std::cout << variantPtr->getKey() << std::endl;
					std::cout << alignmentSequenceRefLength << std::endl;
					std::cout << bamtoolsAlignmentPtr->QueryBases << std::endl;
					if (alignmentSequenceAltLength.compare(variantPtr->getAlt()) == 0)
					{
						std::cout << "incremented" << std::endl;
					}
					std::cout << "--------------------" << std::endl;
				}
				l.unlock();
				*/
				if (alignmentSequenceRefLength.compare(variantPtr->getRef()) == 0)
				{
					variantPtr->incrementRefCounter(alignmentBarcode);
				}
				else
				{
					std::string alignmentSequenceAltLength = bamtoolsAlignmentPtr->QueryBases.substr(offset, variantPtr->getAlt().size());
					if (alignmentSequenceAltLength.compare(variantPtr->getAlt()) == 0)
					{
						variantPtr->incrementAltCounter(alignmentBarcode);
					}
				}



			}
		}
		delete bamtoolsAlignmentPtr;
	}

	std::shared_ptr< BamTools::BamReader > BamReader::getBamToolsReader()
	{
		std::lock_guard< std::mutex > l(this->m_bam_readers_mutex);
		auto iter = m_bam_readers.find(std::this_thread::get_id());
		if (iter == m_bam_readers.end())
		{
			std::shared_ptr< BamTools::BamReader > bamtoolsReader = std::make_shared< BamTools::BamReader >();
			if (!bamtoolsReader->Open(this->m_path))
			{
				throw "Unable to open bam file";
			}
			bamtoolsReader->LocateIndex();
			m_bam_readers.emplace(std::this_thread::get_id(), bamtoolsReader);
			return bamtoolsReader;
		}
		return iter->second;
	}
}
