#pragma once

#include <string>
#include <memory>


namespace scbayes
{

	/*
	 * This class represents a reference id, start position and an end position.
	 */
	class Region
	{
	public:
		typedef std::shared_ptr< Region > SharedPtr;

		enum class BASED { ZERO = 0, ONE = 1 }; // based on this https://www.biostars.org/p/84686/ interpretation of zero and one based

		//noncopyable stuff
		Region( const Region& noncopyable) = delete;
		Region& operator=( const Region& noncopyable) = delete;
		Region() = default;

		Region(const std::string& regionString, BASED based);
		Region(const std::string& referenceID, uint32_t startPosition, uint32_t endPosition, BASED based);
		~Region();

		std::string getRegionString() const { return m_region_string; }
		std::string getReferenceID() const { return this->m_reference_id; }
		uint32_t getStartPosition() const { return this->m_start_position; }
		uint32_t getEndPosition() const { return this->m_end_position; }
		void setStartPosition(uint32_t startPosition) { this->m_start_position = startPosition; }
		void setEndPosition(uint32_t endPosition) { this->m_end_position = endPosition; }
		BASED getBased() { return m_based; }
		void setBased(BASED based);

	private:
		std::string m_region_string;
		std::string m_reference_id;
		uint32_t m_start_position;
		uint32_t m_end_position;
		BASED m_based;
	};

}
