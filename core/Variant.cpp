#include "Variant.h"

#include <iostream>

namespace scbayes
{
	Variant::Variant(const std::string& chrom, uint32_t position, const std::string& ref, const std::string& alt, size_t numberOfBarcodes, uint32_t lineNumber) :
		m_chrom(chrom), m_position(position), m_ref(ref), m_alt(alt), m_line_number(lineNumber),
		m_region_ptr(std::make_shared< Region >(chrom, position, position + ref.size(), Region::BASED::ONE))
	{
	}

	Variant::~Variant()
	{
	}

	void Variant::incrementRefCounter(const std::string& barcode)
	{
		auto iter = this->m_barcode_ref_read_counts.find(barcode);
		if (iter == this->m_barcode_ref_read_counts.end())
		{
			this->m_barcode_ref_read_counts[barcode] = 1;
		}
		else
		{
			++iter->second;
		}
	}

	void Variant::incrementAltCounter(const std::string& barcode)
	{
		auto iter = this->m_barcode_alt_read_counts.find(barcode);
		if (iter == this->m_barcode_alt_read_counts.end())
		{
			this->m_barcode_alt_read_counts[barcode] = 1;
		}
		else
		{
			++iter->second;
		}
	}

	uint32_t Variant::getRefCount(const std::string& barcode)
	{
		auto iter = this->m_barcode_ref_read_counts.find(barcode);
		if (iter == this->m_barcode_ref_read_counts.end())
		{
			return 0;
		}
		else
		{
			return iter->second;
		}
	}

	uint32_t Variant::getAltCount(const std::string& barcode)
	{
		auto iter = this->m_barcode_alt_read_counts.find(barcode);
		if (iter == this->m_barcode_alt_read_counts.end())
		{
			return 0;
		}
		else
		{
			return iter->second;
		}
	}
}
