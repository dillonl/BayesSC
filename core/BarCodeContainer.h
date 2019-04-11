#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace scbayes
{
	class BarCodeContainer
	{
	public:
		//noncopyable stuff
		BarCodeContainer( const BarCodeContainer& noncopyable) = delete;
		BarCodeContainer& operator=( const BarCodeContainer& noncopyable) = delete;
		BarCodeContainer() = default;

		typedef std::shared_ptr< BarCodeContainer > SharedPtr;
		BarCodeContainer(const std::string& path);
		~BarCodeContainer();

		bool doesBarCodeExist(const std::string& barcode);

		size_t getBarCodeCount() { return this->m_barcode_with_order_map.size(); }
		std::vector< std::string > getBarCodes() { return m_barcodes; }

	private:
		void initBarCodes();

		std::string m_path;
		std::unordered_map< std::string, uint32_t > m_barcode_with_order_map;
		std::vector< std::string > m_barcodes;
	};
}
