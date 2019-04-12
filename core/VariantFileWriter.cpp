#include "VariantFileWriter.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace scbayes
{

	VariantFileWriter::VariantFileWriter(const std::vector< Variant::SharedPtr >& variantPtrs, BarCodeContainer::SharedPtr barcodeContainerPtr):
		m_variant_ptrs(variantPtrs), m_barcode_container_ptr(barcodeContainerPtr)
	{
	}

	VariantFileWriter::~VariantFileWriter()
	{
	}

	void VariantFileWriter::writeToCSV(const std::string& ref_filename, const std::string& alt_filename, const std::string& bin_filename, char separator)
	{
		/*
		for (auto variantPtr : this->m_variant_ptrs)
		{
			if (variantPtr->getKey().compare("1:40779145:G:A") == 0)
			{
				auto refCount = variantPtr->getRefCount("CTACCCACAACGATGG-1");
				auto altCount = variantPtr->getAltCount("CTACCCACAACGATGG-1");
				std::cout << "dillons output" << std::endl;
				std::cout << "ref: " << refCount << std::endl;
				std::cout << "alt: " << altCount << std::endl;
			}
		}
		*/

		FILE* fpRef;
		FILE* fpAlt;
		FILE* fpBin;
		fpRef = fopen(ref_filename.c_str(), "w");
		fpAlt = fopen(alt_filename.c_str(), "w");
		fpBin = fopen(bin_filename.c_str(), "w");
		if (fpRef == NULL || fpAlt == NULL || fpBin == NULL)
		{
			std::cout << "one of your output file paths is not a valid file" << std::endl;
			exit(0);
		}
		fprintf(fpRef, "%s", "variant_key");
		fprintf(fpAlt, "%s", "variant_key");
		fprintf(fpBin, "%s", "variant_key");

		std::vector< std::string > barcodes = this->m_barcode_container_ptr->getBarCodes();
		for (auto i = 0; i < barcodes.size(); ++i)
		{
			fprintf(fpRef, "%c%s", separator, barcodes[i].c_str());
			fprintf(fpAlt, "%c%s", separator, barcodes[i].c_str());
			fprintf(fpBin, "%c%s", separator, barcodes[i].c_str());
		}
		for (auto variantPtr : this->m_variant_ptrs)
		{
			// auto refCounts = variantPtr->getBarCodeRefCounts();
			// auto altCounts = variantPtr->getBarCodeAltCounts();
			fprintf(fpRef, "%s", variantPtr->getKey().c_str());
			fprintf(fpAlt, "%s", variantPtr->getKey().c_str());
			fprintf(fpBin, "%s", variantPtr->getKey().c_str());
			//for (auto i = 0; i < refCounts.size(); ++i)
			for (auto barcode : barcodes)
			{
				auto refCount = variantPtr->getRefCount(barcode);
				auto altCount = variantPtr->getAltCount(barcode);
				fprintf(fpRef, "%c%d", separator, refCount);
				fprintf(fpAlt, "%c%d", separator, altCount);
				if (altCount > 0)
				{
					fprintf(fpBin, "%c1", separator);
				}
				else if (refCount > 0)
				{
					fprintf(fpBin, "%c0", separator);
				}
				else
				{
					fprintf(fpBin, "%c-1", separator);
				}
			}
			fprintf(fpRef, "\n");
			fprintf(fpAlt, "\n");
			fprintf(fpBin, "\n");
		}
		fclose(fpRef);
		fclose(fpAlt);
		fclose(fpBin);
	}
}
