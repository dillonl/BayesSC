set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)


set(SCBAYES_TOOLS_SOURCES
    scbayes.cpp
)

INCLUDE_DIRECTORIES(
  ${ZLIB_INCLUDE}
  ${BAMTOOLS_INCLUDE}
  ${CXXOPTS_INCLUDE}
)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lstdc++fs -std=c++11") # testing out newer compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build

add_executable(scbayes
  ${SCBAYES_TOOLS_SOURCES}
)

# link libraries to executables
target_link_libraries(scbayes
  ${CORE_LIB}
)

add_dependencies(scbayes ${SCBAYES_EXTERNAL_PROJECT})