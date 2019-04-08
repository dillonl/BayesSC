#pragma once

#include "Variant.h"
#include "Region.h"

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
		VCF(const std::string& path);
		~VCF();

        Variant::SharedPtr getVariantFromLine(const std::string& vcfLine);
		std::vector< Variant::SharedPtr > getVariants(Region::SharedPtr regionPtr=nullptr);

	private:
		std::string m_path;
	};
}

