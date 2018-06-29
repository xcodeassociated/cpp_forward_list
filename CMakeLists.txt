cmake_minimum_required(VERSION 3.5)
project(forward_list)

option(DISABLE_TEST "Disable CPP_UNIT Test" OFF)
option(DISABLE_DOCS "Disable oxygen documentation" OFF)

set(MASTER_BUILD_TYPES "Debug Release RelWithDebInfo MinSizeRel")
string(REPLACE " " ";" MASTER_BUILD_TYPES_AVAILABLE ${MASTER_BUILD_TYPES})
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${MASTER_BUILD_TYPES_AVAILABLE})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g")
else()
    message (STATUS "MSVC ${MSVC_VERSION}v")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /W2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O2")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_MACOSX_RPATH OFF)
endif()

## include project source
include_directories("${CMAKE_SOURCE_DIR}/src/")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

if(NOT ${DISABLE_DOCS})
    find_package(Doxygen REQUIRED dot)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen error occured!")
    endif()
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)

    doxygen_add_docs(docs ${PROJECT_SOURCE_DIR}/docs COMMENT "Generate man pages")
endif()

if(NOT ${DISABLE_TEST})
    enable_testing()

    find_package(cppunit REQUIRED)
    if(NOT CPPUNIT_FOUND)
        message(FATAL_ERROR "CPP UNIT NOT FOUND!")
    endif()

    include_directories(${CPPUNIT_INCLUDE_DIRS})
    add_executable("${PROJECT_NAME}_TEST" test/ListTest.cpp test/test_main.cpp)
    target_link_libraries("${PROJECT_NAME}_TEST" ${CPPUNIT_LIBRARIES})
    add_test(NAME test COMMAND "${PROJECT_NAME}_TEST")
endif()

add_executable(${PROJECT_NAME} main.cpp)


