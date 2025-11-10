cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

# set up project
project(fgptool
        DESCRIPTION "A tool to crack the filepath hashes in The Orange Box PS3 file groups."
        VERSION 0.2.0
        HOMEPAGE_URL "https://github.com/craftablescience/fgptool")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add helpers
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/helpers")
include(CS_All)

# extra metadata variables
set(PROJECT_ORGANIZATION_NAME "craftablescience" CACHE INTERNAL "" FORCE)

# initial VS integration
cs_setup_vs_defaults(STARTUP_PROJECT "${PROJECT_NAME}")

# set common compile options
option(FGPTOOL_USE_LTO "Compile ${PROJECT_NAME} with LTO/IPO" OFF)
cs_configure_defaults(FGPTOOL_USE_LTO)

# external libraries
cs_include_directory(ext)

# fgptool
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h")
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/fgptool.cpp")
cs_configure_target(${PROJECT_NAME} MANIFEST)
target_link_libraries(${PROJECT_NAME} PRIVATE argparse::argparse sourcepp::kvpp sourcepp::vpkpp)
