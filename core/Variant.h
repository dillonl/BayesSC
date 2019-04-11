#pragma once

#include "BarCodeContainer.h"
#include "Region.h"

#include <memory>
#include <unordered_map>
namespace scbayes
{
	class Variant
	{
	public:
		//noncopyable stuff
		Variant( const Variant& noncopyable) = delete;
		Variant& operator=( const Variant& noncopyable) = delete;
		Variant() = default;

		typedef std::shared_ptr< Variant > SharedPtr;
		Variant(const std::string& chrom, uint32_t position, const std::string& ref, const std::string& alt, size_t numberOfBarcodes, uint32_t lineNumber);
		~Variant();

		std::string getChrom() { return this->m_chrom; }
		std::string getRef() { return this->m_ref; }
		std::string getAlt() { return this->m_alt; }
		uint32_t getPosition() { return this->m_position; }

		void incrementRefCounter(const std::string& barcode);
		void incrementAltCounter(const std::string& barcode);

		uint32_t getRefCount(const std::string& barcode);
		uint32_t getAltCount(const std::string& barcode);

		Region::SharedPtr getRegionPtr() { return this->m_region_ptr; }
		std::string getKey() { return this->m_chrom + ":" + std::to_string(this->m_position) + ":" + this->m_ref + ":" + this->m_alt; }

	private:
		std::string m_chrom;
		std::string m_ref;
		std::string m_alt;
		uint32_t m_position;
		uint32_t m_line_number;
		Region::SharedPtr m_region_ptr;
		std::unordered_map< std::string, uint32_t > m_barcode_ref_read_counts;
		std::unordered_map< std::string, uint32_t > m_barcode_alt_read_counts;
	};
}
