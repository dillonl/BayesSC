#include "core/Params.h"
#include "core/VCF.h"
#include "core/Variant.h"
#include "core/BamReader.h"
#include "core/BarCodeParser.h"

#include <iostream>

int main(int argc, char** argv)
{
	// get all param properties
	scbayes::Params params;
	params.parseSCBayes(argc, argv);
	if (params.showHelp() || !params.validateRequired())
	{
		params.printHelp();
		return 0;
	}
	auto bamPath = params.getBAMPath();
	auto vcfPath = params.getVCFPath();
	auto barcodePath = params.getBarCodePath();
	auto regionPtr = params.getRegion();

	auto barcodeParser = std::make_shared< scbayes::BarCodeParser >(barcodePath);
	auto barcodes = barcodeParser->getBarCodes();
	auto vcf = std::make_shared< scbayes::VCF >(vcfPath);
	auto variants = vcf->getVariants(regionPtr);

	// now do the bam magic

	return 0;
}
