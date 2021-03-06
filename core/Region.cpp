#include "Region.h"
#include "Utils.h"

#include <limits>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

namespace scbayes
{

	Region::Region(const std::string& regionString, BASED based) :
		m_region_string(regionString),
		m_start_position(0),
		m_end_position(0),
		m_based(based)
	{
		std::vector< std::string > chromWithPositionComponents;
		std::vector< std::string > positionComponents;
		split(regionString, ':', chromWithPositionComponents);

		if (chromWithPositionComponents.size() == 0)
		{
			this->m_reference_id = regionString;
		}
		else
		{
			this->m_reference_id = chromWithPositionComponents[0];
			split(chromWithPositionComponents[1], '-', positionComponents);

			if (positionComponents.size() == 2)
			{
				m_start_position = std::stol(positionComponents[0]);
				m_end_position = std::stol(positionComponents[1]);
			}
		}
		if (this->m_start_position > this->m_end_position || regionString.size() == 0)
		{
			throw std::invalid_argument("Region format is invalid");
		}
		if (this->m_start_position == 0 && this->m_end_position == 0)
		{
			this->m_end_position = std::numeric_limits< uint32_t >::max();
		}
	}


	Region::Region(const std::string& referenceID, uint32_t startPosition, uint32_t endPosition, BASED based) :
	    m_reference_id(referenceID),
		m_start_position(startPosition),
		m_end_position(endPosition),
		m_region_string(referenceID + ":" + std::to_string(startPosition) + "-" + std::to_string(endPosition)),
		m_based(based)
	{
	}

	Region::~Region()
	{
	}

	void Region::setBased(BASED based)
	{
		m_based = based;
	}

	uint32_t Region::getStartPosition(BASED based)
	{
		if (m_based == based)
		{
			return this->m_start_position;
		}
		else if (m_based == BASED::ZERO)
		{
			return this->m_start_position - 1;
		}
		else // must be based one
		{
			return this->m_start_position + 1;
		}
	}

	uint32_t Region::getEndPosition(BASED based)
	{
		if (m_based == based)
		{
			return this->m_end_position;
		}
		else if (m_based == BASED::ZERO)
		{
			return this->m_end_position - 1;
		}
		else // must be based one
		{
			return this->m_end_position + 1;
		}
	}
}
