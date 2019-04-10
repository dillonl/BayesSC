#include "core/Params.h"
#include "core/VCF.h"
#include "core/Variant.h"
#include "core/BamReader.h"
#include "core/VariantFileWriter.h"
#include "core/BarCodeContainer.h"

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

	auto barcodeContainerPtr = std::make_shared< scbayes::BarCodeContainer >(barcodePath);
	auto vcf = std::make_shared< scbayes::VCF >(vcfPath, barcodeContainerPtr);
	auto variantPtrs = vcf->getVariants(regionPtr);

	// now do the bam magic
	scbayes::BamReader::SharedPtr bamReaderPtr = std::make_shared< scbayes::BamReader >(bamPath, barcodeContainerPtr);
	bamReaderPtr->processVariants(variantPtrs);
	auto variantFileWriterPtr = std::make_shared< scbayes::VariantFileWriter >(variantPtrs, barcodeContainerPtr);
	variantFileWriterPtr->writeToCSV("variant_ref_matrix.csv", "variant_alt_matrix.csv", "variant_bin_matrix.csv", '\t');
	return 0;
}
