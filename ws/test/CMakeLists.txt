# This is the project CMakeLists.txt file for the test subproject
cmake_minimum_required(VERSION 3.16)

# Include the components directory of the main application:
#


# Set the components to include the tests for.
# This can be overriden from CMake cache:
# - when invoking CMake directly: cmake -D TEST_COMPONENTS="xxxxx" ..
# - when using idf.py: idf.py -T xxxxx build
#
set(TEST_COMPONENTS "parameters" "nominal-mode" "drivers" CACHE STRING "List of components to test")
set(EXTRA_COMPONENT_DIRS /opt/eps-idf/lib/esp-idf-lib/components ../components)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ws_tests)
