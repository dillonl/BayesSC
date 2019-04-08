#include "Params.h"
#include "Utils.h"

#include <string.h>
#include <thread>
#include <iostream>

namespace scbayes
{

	Params::Params() :
		m_options("SCBAYES", "Subclone Bayes - The world's best Bayesian Subclone Software")
	{

	}

	Params::~Params()
	{
	}

	void Params::parseSCBayes(int argc, char** argv)
	{
		this->m_options.add_options()
			("h,help","Print help message")
			("v,vcf", "Path to the input VCF file", cxxopts::value< std::string >())
			("b,bam", "Path to the input BAM file", cxxopts::value< std::string >())
			("c,barcode", "Path to the input BarCode file", cxxopts::value< std::string >())
			("r,region", "Region information", cxxopts::value< std::string >());
		this->m_options.parse(argc, argv);
	}

	bool Params::showHelp()
	{
		return m_options.count("h");
	}

	void Params::printHelp()
	{
		std::cout << "SCBayes: V1.0" << std::endl;
		std::cout << this->m_options.help() << std::endl;
	}

	bool Params::validateRequired()
	{
		std::vector< std::string > errorMessages;
		if (!m_options.count("v"))
		{
			errorMessages.emplace_back("vcf path required");
		}
		if (!m_options.count("b"))
		{
			errorMessages.emplace_back("bam path required");
		}
		if (errorMessages.size() > 0)
		{
			std::cout << "There was a problem parsing commands" << std::endl;
			for (auto message : errorMessages)
			{
				std::cout << message << std::endl;
			}
			return false;
		}
		else
		{
			return true;
		}
	}


    std::string Params::getVCFPath()
	{
		auto vcfPath =  m_options["v"].as< std::string >();
		validateFilePath(vcfPath, true);
		return vcfPath;
	}

	std::string Params::getBAMPath()
	{
		auto bamPath =  m_options["b"].as< std::string >();
		validateFilePath(bamPath, true);
		return bamPath;
	}

	std::string Params::getBarCodePath()
	{
		auto barcodePath =  m_options["c"].as< std::string >();
		validateFilePath(barcodePath, true);
		return barcodePath;
	}

	Region::SharedPtr Params::getRegion()
	{
		if (m_options.count("r"))
		{
			return std::make_shared< Region >(m_options["r"].as< std::string >(), Region::BASED::ONE);
		}
		return nullptr;
	}

	void Params::validateFilePath(const std::string& path, bool exitOnFailure)
	{
		fileExists(path, exitOnFailure);
	}

}
