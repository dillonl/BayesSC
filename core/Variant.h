#pragma once

#include <memory>
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
		Variant(const std::string& chrom, uint32_t position, const std::string& ref, const std::string& alt);
		~Variant();

		std::string getChrom() { return this->m_chrom; }
		std::string getRef() { return this->m_ref; }
		std::string getAlt() { return this->m_alt; }
		uint32_t getPosition() { return this->m_position; }

		std::string getKey() { return this->m_chrom + ":" + std::to_string(this->m_position) + ":" + this->m_ref + ":" + this->m_alt; }

	private:
		std::string m_chrom;
		std::string m_ref;
		std::string m_alt;
		uint32_t m_position;
	};
}
