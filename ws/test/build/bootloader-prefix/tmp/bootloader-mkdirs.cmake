# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/opt/esp/esp/esp/esp-idf/components/bootloader/subproject"
  "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader"
  "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix"
  "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix/tmp"
  "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix/src/bootloader-stamp"
  "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix/src"
  "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/javierfernandez/workspace/water-station/Water-Station/ws/test/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
