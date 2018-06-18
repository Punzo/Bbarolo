PROJECT(BBAROLO)
CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)
SET(CMAKE_MACOSX_RPATH OFF)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
SET(LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
SET(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/")
SET(CMAKE_ARRAY_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/Arrays")
SET(CMAKE_MAP_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/Map")
SET(CMAKE_TASKS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/Tasks")
SET(CMAKE_UTILITIES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/Utilities")


#-----------------------------------------------------------------------------
# configurating additional Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -ftree-vectorize -fPIC -Wuninitialized -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ftree-vectorize -fPIC -Wuninitialized -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O2 -ftree-vectorize -fPIC -Wuninitialized -flto -std=c++11")

#-----------------------------------------------------------------------------
# configurating FFTW3
SET(status "disabled")
IF(NOT DEFINED FFTW3_INCLUDE_DIR AND NOT DEFINED FFTW3_LIBRARY_DIR)
  IF(DEFINED FFTW3_DIR)
    SET (FFTW3_INCLUDE_DIR "${FFTW3_DIR}/include")
    SET (FFTW3_LIBRARY_DIR "${FFTW3_DIR}/lib")
    SET(BBAROLO_SUPPORT_FFTW3 1)
  ELSE()
    SET(BBAROLO_SUPPORT_FFTW3 0)
  ENDIF()
ELSE()
  SET(BBAROLO_SUPPORT_FFTW3 1)
ENDIF()

IF(BBAROLO_SUPPORT_FFTW3)
  SET(status "enabled")
ENDIF()

MESSAGE(STATUS "FFTW3 support ${status}")
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/CMake/BbaroloConfigure.h.in
  ${CMAKE_BINARY_DIR}/BbaroloConfigure.h
  )

#-----------------------------------------------------------------------------
# configurating OpenMP
find_package(OpenMP)
set(BBAROLO_SUPPORT_OPENMP ${OPENMP_FOUND})
set(status "disabled")
if(BBAROLO_SUPPORT_OPENMP)
  set(status "enabled")
endif()
message(STATUS "OpenMP support ${status}")
configure_file(
  ${CMAKE_SOURCE_DIR}/CMake/BbaroloConfigure.h.in
  ${CMAKE_BINARY_DIR}/BbaroloConfigure.h
  )

#-----------------------------------------------------------------------------
# configurating OpenMP Flags
if(BBAROLO_SUPPORT_OPENMP)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#-----------------------------------------------------------------------------
# configurating Gnuplot (disable)
SET(HAVE_GNUPLOT 0)
configure_file(
  ${CMAKE_SOURCE_DIR}/CMake/BbaroloConfigure.h.in
  ${CMAKE_BINARY_DIR}/BbaroloConfigure.h
  )

#-----------------------------------------------------------------------------
# configurating Python (disable)
SET(HAVE_PYTHON 0)
configure_file(
  ${CMAKE_SOURCE_DIR}/CMake/BbaroloConfigure.h.in
  ${CMAKE_BINARY_DIR}/BbaroloConfigure.h
  )

#-----------------------------------------------------------------------------
# configurating Mac
if(APPLE)
  SET(MACOSX 1)
elseif(UNIX)
  SET(MACOSX 0)
endif()
configure_file(
  ${CMAKE_SOURCE_DIR}/CMake/BbaroloConfigure.h.in
  ${CMAKE_BINARY_DIR}/BbaroloConfigure.h
  )

#-----------------------------------------------------------------------------
# configurating CFITSIO
IF(NOT DEFINED CFITSIO_INCLUDE_DIR AND NOT DEFINED CFITSIO_LIBRARY_DIR)
  IF(DEFINED CFITSIO_DIR)
    SET(CFITSIO_INCLUDE_DIR "${CFITSIO_DIR}/include")
    SET(CFITSIO_LIBRARY_DIR "${CFITSIO_DIR}/lib")
  ELSE()
    MESSAGE(STATUS "CFITSIO_DIR : ${CFITSIO_DIR}")
    MESSAGE(FATAL_ERROR "Undefined CFITSIO_DIR var.")
  ENDIF()
ENDIF()

#-----------------------------------------------------------------------------
# configurating WCSLIB
IF(NOT DEFINED WCSLIB_INCLUDE_DIR AND NOT DEFINED WCSLIB_LIBRARY_DIR)
  IF(DEFINED WCSLIB_DIR)
    SET(WCSLIB_INCLUDE_DIR "${WCSLIB_DIR}/include")
    SET(WCSLIB_LIBRARY_DIR "${WCSLIB_DIR}/lib")
  ELSE()
    MESSAGE(STATUS "WCSLIB_DIR : ${WCSLIB_DIR}")
    MESSAGE(FATAL_ERROR "Undefined WCSLIB_DIR var.")
  ENDIF()
ENDIF()

SET(INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_ARRAY_SOURCE_DIR}"
    "${CMAKE_MAP_SOURCE_DIR}"
    "${CMAKE_TASKS_SOURCE_DIR}"
    "${CMAKE_UTILITIES_SOURCE_DIR}"
    "${CFITSIO_INCLUDE_DIR}"
    "${WCSLIB_INCLUDE_DIR}"
)

IF(BBAROLO_SUPPORT_FFTW3)
  SET(INCLUDE_DIRS
     ${INCLUDE_DIRS}
     ${FFTW3_INCLUDE_DIR}
     )
ENDIF()

# Define project version
SET(${PROJECT_NAME}_MAJOR_VERSION 1)
SET(${PROJECT_NAME}_MINOR_VERSION 4)
SET(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION})
SET(LIB_NAME bbarolo)

SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

SET(H_FILES
    ${CMAKE_SOURCE_DIR}/src/bbarolo.hh
    ${CMAKE_ARRAY_SOURCE_DIR}/cube.hh   ${CMAKE_ARRAY_SOURCE_DIR}/cube.tpp
    ${CMAKE_ARRAY_SOURCE_DIR}/search.tpp
    ${CMAKE_ARRAY_SOURCE_DIR}/header.hh
    ${CMAKE_ARRAY_SOURCE_DIR}/image.hh   ${CMAKE_ARRAY_SOURCE_DIR}/image.tpp
    ${CMAKE_ARRAY_SOURCE_DIR}/param.hh
    ${CMAKE_ARRAY_SOURCE_DIR}/rings.hh
    ${CMAKE_ARRAY_SOURCE_DIR}/stats.hh  ${CMAKE_ARRAY_SOURCE_DIR}/stats.tpp
    ${CMAKE_MAP_SOURCE_DIR}/detection.hh   ${CMAKE_MAP_SOURCE_DIR}/detection.tpp
    ${CMAKE_MAP_SOURCE_DIR}/object2D.hh   ${CMAKE_MAP_SOURCE_DIR}/object2D.tpp
    ${CMAKE_MAP_SOURCE_DIR}/object3D.hh   ${CMAKE_MAP_SOURCE_DIR}/object3D.tpp
    ${CMAKE_MAP_SOURCE_DIR}/objectgrower.hh  ${CMAKE_MAP_SOURCE_DIR}/objectgrower.tpp
    ${CMAKE_MAP_SOURCE_DIR}/scan.hh   ${CMAKE_MAP_SOURCE_DIR}/scan.tpp
    ${CMAKE_MAP_SOURCE_DIR}/voxel.hh    ${CMAKE_MAP_SOURCE_DIR}/voxel.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/ellprof.hh   ${CMAKE_TASKS_SOURCE_DIR}/ellprof.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/galfit.hh    ${CMAKE_TASKS_SOURCE_DIR}/galfit.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/galfit_errors.tpp   ${CMAKE_TASKS_SOURCE_DIR}/galfit_min.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/galfit_out.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/galmod.hh   ${CMAKE_TASKS_SOURCE_DIR}/galmod.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/galwind.hh  ${CMAKE_TASKS_SOURCE_DIR}/galwind.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/moment.hh
    ${CMAKE_TASKS_SOURCE_DIR}/ringmodel.hh
    ${CMAKE_TASKS_SOURCE_DIR}/slitfit.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/smooth3D.hh   ${CMAKE_TASKS_SOURCE_DIR}/smooth3D.tpp
    ${CMAKE_TASKS_SOURCE_DIR}/spacepar.hh   ${CMAKE_TASKS_SOURCE_DIR}/spacepar.tpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/allocator.tpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/conv2D.hh   ${CMAKE_UTILITIES_SOURCE_DIR}/conv2D.tpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/converter.hh
    ${CMAKE_UTILITIES_SOURCE_DIR}/gnuplot.hh
    ${CMAKE_UTILITIES_SOURCE_DIR}/lsqfit.hh   ${CMAKE_UTILITIES_SOURCE_DIR}/lsqfit.tpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/interpolation.tpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/paramguess.hh
    ${CMAKE_UTILITIES_SOURCE_DIR}/progressbar.hh
    ${CMAKE_UTILITIES_SOURCE_DIR}/statistics.tpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/utils.hh
)

IF(BBAROLO_SUPPORT_FFTW3)
  SET(H_FILES
     ${H_FILES}
     ${CMAKE_UTILITIES_SOURCE_DIR}/conv2D.hh
     )
ENDIF()

SET(SRC_FILES
    ${CMAKE_ARRAY_SOURCE_DIR}/header.cpp   ${CMAKE_ARRAY_SOURCE_DIR}/param.cpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/converter.cpp   ${CMAKE_UTILITIES_SOURCE_DIR}/progressbar.cpp
    ${CMAKE_TASKS_SOURCE_DIR}/ringmodel.cpp   ${CMAKE_UTILITIES_SOURCE_DIR}/string.cpp
    ${CMAKE_UTILITIES_SOURCE_DIR}/utils.cpp   ${CMAKE_UTILITIES_SOURCE_DIR}/wcsUtils.cpp
)

IF(BBAROLO_SUPPORT_FFTW3)
  SET(SRC_FILES
     ${SRC_FILES}
     ${CMAKE_UTILITIES_SOURCE_DIR}/conv2D.cpp
     )
ENDIF()

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

SET(LINK_DIRS
   ${CFITSIO_LIBRARY_DIR}
   ${WCSLIB_LIBRARY_DIR}
   )

IF(BBAROLO_SUPPORT_FFTW3)
  SET(LINK_DIRS
     ${LINK_DIRS}
     ${FFTW3_LIBRARY_DIR}
     )
ENDIF()

LINK_DIRECTORIES(${LINK_DIRS})

ADD_LIBRARY(${LIB_NAME} ${LIB_TYPE} ${H_FILES} ${SRC_FILES})

IF(BBAROLO_SUPPORT_FFTW3)
  TARGET_LINK_LIBRARIES(${LIB_NAME} cfitsio wcslib fftw3)
ELSE()
  TARGET_LINK_LIBRARIES(${LIB_NAME} cfitsio wcslib)
ENDIF()


SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})
INSTALL(TARGETS ${LIB_NAME} LIBRARY DESTINATION ${LIB_DESTINATION})
INSTALL(FILES ${H_FILES} DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

ADD_EXECUTABLE(3DBarolo ${CMAKE_SOURCE_DIR}/src/bbarolo.cpp)
TARGET_LINK_LIBRARIES(3DBarolo ${LIB_NAME})
