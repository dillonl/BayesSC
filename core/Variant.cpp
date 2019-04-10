#include "Variant.h"

#include <iostream>

namespace scbayes
{
	Variant::Variant(const std::string& chrom, uint32_t position, const std::string& ref, const std::string& alt, size_t numberOfBarcodes, uint32_t lineNumber) :
		m_chrom(chrom), m_position(position), m_ref(ref), m_alt(alt), m_line_number(lineNumber), m_barcode_ref_read_counts(numberOfBarcodes, 0),
		m_barcode_alt_read_counts(numberOfBarcodes, 0), m_region_ptr(std::make_shared< Region >(chrom, position, position + ref.size(), Region::BASED::ONE))
	{
	}

	Variant::~Variant()
	{
	}

	void Variant::incrementRefCounter(uint32_t barcodeID)
	{
		this->m_barcode_ref_read_counts[barcodeID] = this->m_barcode_ref_read_counts[barcodeID] + 1;
	}

	void Variant::incrementAltCounter(uint32_t barcodeID)
	{
		this->m_barcode_alt_read_counts[barcodeID] = this->m_barcode_alt_read_counts[barcodeID] + 1;
	}
}
