#pragma once

#include <vector>
#include <string>
#include <memory>

namespace scbayes
{
	class BarCodeParser
	{
	public:
		//noncopyable stuff
		BarCodeParser( const BarCodeParser& noncopyable) = delete;
		BarCodeParser& operator=( const BarCodeParser& noncopyable) = delete;
		BarCodeParser() = default;

		typedef std::shared_ptr< BarCodeParser > SharedPtr;
		BarCodeParser(const std::string& path);

        std::vector< std::string > getBarCodes();

	private:
		std::string m_path;
	};
}
