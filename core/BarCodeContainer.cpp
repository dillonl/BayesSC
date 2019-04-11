#include "BarCodeContainer.h"
#include "Utils.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace scbayes
{
	BarCodeContainer::BarCodeContainer(const std::string& path):
		m_path(path)
	{
		initBarCodes();
	}
	BarCodeContainer::~BarCodeContainer() {}

	bool BarCodeContainer::doesBarCodeExist(const std::string& barcode)
	{
	    return (this->m_barcode_with_order_map.find(barcode) != this->m_barcode_with_order_map.end());
	}

    void BarCodeContainer::initBarCodes()
	{
		this->m_barcode_with_order_map.clear();

		FILE* fp;
		char* line = (char*)malloc(sizeof(char) * 5000); // reserve for 5k line of chars, probably can't use this with RUFUS :p
		size_t len = 0;
		ssize_t read;

		fp = fopen(this->m_path.c_str(), "r");
		if (fp == NULL)
		{
			std::cout << m_path << " is not a valid file" << std::endl;
			exit(0);
		}
		uint32_t count = 0;
		while ((read = getline(&line, &len, fp)) != -1)
		{
			++count;
			if (count == 1)
			{
				continue;
			}
			std::vector< std::string > lineSplit;
			split(line, ',', lineSplit);
			this->m_barcode_with_order_map.emplace(lineSplit[0], count);
			m_barcodes.emplace_back(lineSplit[0]);
		}
		free(line);
	}
}
