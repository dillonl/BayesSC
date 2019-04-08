#include "VCF.h"
#include "Utils.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace scbayes
{
	VCF::VCF(const std::string& path) :
		m_path(path)
	{
		if (!fileExists(m_path, false))
		{
			std::cout << m_path << " is not a valid file" << std::endl;
			exit(0);
		}
	}

	VCF::~VCF()
	{
	}

	Variant::SharedPtr VCF::getVariantFromLine(const std::string& vcfLine)
	{
		std::vector< std::string > lineSplit;
		split(vcfLine, '\t', lineSplit);
		return std::make_shared< Variant >(lineSplit[0], std::stoi(lineSplit[1]), lineSplit[3], lineSplit[4]);
	}

	std::vector< Variant::SharedPtr > VCF::getVariants(Region::SharedPtr regionPtr)
	{
		std::vector< Variant::SharedPtr > variants;

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
		while ((read = getline(&line, &len, fp)) != -1)
		{
			if (len == 0 || line[0] == '#')
			{
				continue;
			}
			auto variantPtr = getVariantFromLine(std::string(line));
			if (regionPtr == nullptr || (regionPtr->getReferenceID().compare(variantPtr->getChrom()) && regionPtr->getStartPosition() <= (variantPtr->getPosition() + variantPtr->getRef().size()) && variantPtr->getPosition() <= regionPtr->getEndPosition()))
			{
				variants.emplace_back(variantPtr);
			}
		}
		free(line);
		fclose(fp);

		return variants;
	}
}
