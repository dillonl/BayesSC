#pragma once

#include "Variant.h"

#include <memory>
#include <vector>
#include <string>

namespace scbayes
{
	class VariantFileWriter
	{
	public:
		VariantFileWriter( const VariantFileWriter& noncopyable) = delete;
		VariantFileWriter& operator=( const VariantFileWriter& noncopyable) = delete;
		VariantFileWriter() = default;

		typedef std::shared_ptr< VariantFileWriter > SharedPtr;
		VariantFileWriter(const std::vector< Variant::SharedPtr >& variantPtrs, BarCodeContainer::SharedPtr barcodeContainerPtr);
		~VariantFileWriter();

		void writeToCSV(const std::string& ref_filename, const std::string& alt_filename, const std::string& bin_filename, char separator);

	private:
		std::vector< Variant::SharedPtr > m_variant_ptrs;
		BarCodeContainer::SharedPtr m_barcode_container_ptr;
	};
}
