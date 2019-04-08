#pragma once

#include <memory>
#include <string>

namespace scbayes
{
	class BamReader
	{
	public:
		//noncopyable stuff
		BamReader( const BamReader& noncopyable) = delete;
		BamReader& operator=( const BamReader& noncopyable) = delete;
		BamReader() = default;

		typedef std::shared_ptr< BamReader > SharedPtr;
		BamReader(const std::string& path);
		~BamReader();

		//std::vector< std::string > getCellSampleNames
	private:
		std::string m_path;
	};
}
