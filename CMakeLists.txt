# CMake build for the BBarolo library (libbbarolo).
#
# Upstream BBarolo builds with autotools; this file builds the same library
# sources (no executable, no GUI) so that BBarolo can be used as a superbuild
# dependency (e.g. by SlicerAstro) on Linux, macOS and Windows.
cmake_minimum_required(VERSION 3.20...3.31)

project(BBarolo VERSION 1.8 LANGUAGES C CXX)

include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BBAROLO_USE_OPENMP "Enable OpenMP multi-threading inside BBarolo (if available)" ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#-----------------------------------------------------------------------------
# Dependencies: CFITSIO, WCSLIB and FFTW3 (double precision).
# Each can be given as <NAME>_INCLUDE_DIR / <NAME>_LIBRARY_DIR hints.

find_path(CFITSIO_INCLUDE_DIR fitsio.h HINTS ${CFITSIO_INCLUDE_DIR})
find_library(CFITSIO_LIBRARY cfitsio HINTS ${CFITSIO_LIBRARY_DIR})

# BBarolo includes <wcslib/wcs.h>
find_path(WCSLIB_INCLUDE_DIR wcslib/wcs.h HINTS ${WCSLIB_INCLUDE_DIR})
find_library(WCSLIB_LIBRARY NAMES wcslib wcs HINTS ${WCSLIB_LIBRARY_DIR})

find_path(FFTW3_INCLUDE_DIR fftw3.h HINTS ${FFTW3_INCLUDE_DIR})
find_library(FFTW3_LIBRARY NAMES fftw3 libfftw3-3 HINTS ${FFTW3_LIBRARY_DIR})

foreach(_var CFITSIO_INCLUDE_DIR CFITSIO_LIBRARY WCSLIB_INCLUDE_DIR WCSLIB_LIBRARY
             FFTW3_INCLUDE_DIR FFTW3_LIBRARY)
  if(NOT ${_var})
    message(FATAL_ERROR "BBarolo: ${_var} not found. Set the corresponding "
                        "*_INCLUDE_DIR / *_LIBRARY_DIR variables.")
  endif()
endforeach()

if(BBAROLO_USE_OPENMP)
  find_package(OpenMP COMPONENTS CXX)
endif()

#-----------------------------------------------------------------------------
# Sources (same set as Makefile.in: BB_interface + Arrays, Map, Utilities, Tasks)

file(GLOB BBAROLO_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Arrays/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Tasks/*.cpp)
list(APPEND BBAROLO_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/BB_interface.cpp)

add_library(bbarolo ${BBAROLO_SOURCES})
add_library(BBarolo::bbarolo ALIAS bbarolo)
set_target_properties(bbarolo PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  POSITION_INDEPENDENT_CODE ON)

target_include_directories(bbarolo PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/bbarolo>
  ${CFITSIO_INCLUDE_DIR} ${WCSLIB_INCLUDE_DIR} ${FFTW3_INCLUDE_DIR})

target_link_libraries(bbarolo PUBLIC ${CFITSIO_LIBRARY} ${WCSLIB_LIBRARY} ${FFTW3_LIBRARY})

target_compile_definitions(bbarolo PRIVATE HAVE_FFTW3)
if(APPLE)
  target_compile_definitions(bbarolo PRIVATE MACOS)
endif()
if(WIN32)
  target_compile_definitions(bbarolo PRIVATE _USE_MATH_DEFINES NOMINMAX _CRT_SECURE_NO_WARNINGS)
  set_target_properties(bbarolo PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if(OpenMP_CXX_FOUND)
  target_link_libraries(bbarolo PRIVATE OpenMP::OpenMP_CXX)
endif()

if(NOT WIN32)
  target_link_libraries(bbarolo PRIVATE m)
endif()

#-----------------------------------------------------------------------------
# Install

install(TARGETS bbarolo EXPORT BBaroloTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

install(DIRECTORY src/Arrays src/Map src/Tasks src/Utilities
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bbarolo COMPONENT Development
  FILES_MATCHING PATTERN "*.hh" PATTERN "*.hpp" PATTERN "*.h")
