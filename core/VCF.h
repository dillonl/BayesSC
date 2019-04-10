#pragma once

#include "Variant.h"
#include "Region.h"
#include "BarCodeContainer.h"

#include <memory>
#include <vector>
#include <string>

namespace scbayes
{
	class VCF
	{
	public:
		//noncopyable stuff
		VCF( const VCF& noncopyable) = delete;
		VCF& operator=( const VCF& noncopyable) = delete;
		VCF() = default;

		typedef std::shared_ptr<VCF> SharedPtr;
		VCF(const std::string& path, BarCodeContainer::SharedPtr barcodeContainerPtr);
		~VCF();

        Variant::SharedPtr getVariantFromLine(const std::string& vcfLine, uint32_t lineNumber);
		std::vector< Variant::SharedPtr > getVariants(Region::SharedPtr regionPtr=nullptr);

	private:
		std::string m_path;
        BarCodeContainer::SharedPtr m_barcode_container_ptr;
	};
}

