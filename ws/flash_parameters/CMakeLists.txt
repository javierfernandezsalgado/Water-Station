# This is the project CMakeLists.txt file for the test subproject
cmake_minimum_required(VERSION 3.16)

# Include the components directory of the main application:
#
#set(EXTRA_COMPONENT_DIRS "../components")

# Set the components to include the tests for.
# This can be overriden from CMake cache:
# - when invoking CMake directly: cmake -D TEST_COMPONENTS="xxxxx" ..
# - when using idf.py: idf.py -T xxxxx build
#
set(EXTRA_COMPONENT_DIRS /opt/eps-idf/lib/esp-idf-lib/components ../components/parameters)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ws_flash_parameters)
