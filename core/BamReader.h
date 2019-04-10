#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Variant.h"
#include "Region.h"
#include "ThreadPool.hpp"

#include "api/BamReader.h"
#include "api/BamAlignment.h"
#include "api/BamAux.h"

namespace scbayes
{
	class BamReader
	{
	public:
		//noncopyable stuff
		BamReader( const BamReader& noncopyable) = delete;
		BamReader& operator=( const BamReader& noncopyable) = delete;
		BamReader() = default;

		typedef std::shared_ptr< BamReader > SharedPtr;
		BamReader(const std::string& path, BarCodeContainer::SharedPtr barcodeContainer);
		~BamReader();

		void processVariants(const std::vector< Variant::SharedPtr >& variantPtrs);

		void processVariantCounts(Variant::SharedPtr variantPtr);
	private:
		std::shared_ptr< BamTools::BamReader > getBamToolsReader();
		ThreadPool m_thread_pool;

		BarCodeContainer::SharedPtr m_bar_code_container;
		std::unordered_map< std::thread::id, std::shared_ptr< BamTools::BamReader > > m_bam_readers;
		std::mutex m_bam_readers_mutex;
		std::string m_path;
	};
}
