#include "Variant.h"

namespace scbayes
{
	Variant::Variant(const std::string& chrom, uint32_t position, const std::string& ref, const std::string& alt) :
		m_chrom(chrom), m_position(position), m_ref(ref), m_alt(alt)
	{
	}

	Variant::~Variant()
	{
	}
}
