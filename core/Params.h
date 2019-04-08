#pragma once

#include "Region.h"

#include <cstring>
#include <vector>

#include <cxxopts.hpp>

namespace scbayes
{
	class Params
	{
	public:
		//noncopyable stuff
		Params( const Params& noncopyable) = delete;
		Params& operator=( const Params& noncopyable) = delete;

		Params();
		~Params();

		void parseSCBayes(int argc, char** argv);
		bool showHelp();
		void printHelp();
		bool validateRequired();

		std::string getVCFPath();
		std::string getBAMPath();
		std::string getBarCodePath();
		Region::SharedPtr getRegion();
	private:
		void validateFilePath(const std::string& path, bool exitOnFailure);

		cxxopts::Options m_options;
	};
}
