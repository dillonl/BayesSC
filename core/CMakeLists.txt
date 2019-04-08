INCLUDE_DIRECTORIES(
    ${BAMTOOLS_INCLUDE}
	${ZLIB_INCLUDE}
	${CXXOPTS_INCLUDE}
)

set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")


add_library(scbayes_core STATIC
  BamReader.cpp
  VCF.cpp
  Variant.cpp
  Region.cpp
  Params.cpp
  Utils.cpp
  BarCodeParser.cpp
  )

SET(CORE_LIB scbayes_core CACHE STRING "THE CORE LIBRARY") #add scbayes_core and scbayes_utils to the list of core libs

TARGET_LINK_LIBRARIES(${CORE_LIB}
  ${BAMTOOLS_LIB}
  ${BAMTOOLS_UTIL_LIB}
  ${ZLIB_LIBRARY}
)

add_dependencies(${CORE_LIB} ${SCBAYES_EXTERNAL_PROJECT})

