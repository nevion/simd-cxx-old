##############################################################################
# Looks for the SimD library installation and defines:
#
#  SimD_FOUND - system has SimD.
#  SimD_INCLUDE_DIRS - the SimD include directory.
#  SimD_LIBRARIES - Link these to use SimD.
#
# You need to define the SIMD_INSTALL_DIR variable or have the
# environment variable $SIMD_INSTALL_DIR to be set to your SimD
# installation directory.
##############################################################################
find_package(PackageHandleStandardArgs)

# If SIMD_INSTALL_DIR was defined in the environment, use it.
if (NOT SIMD_INSTALL_DIR AND NOT $ENV{SIMD_INSTALL_DIR} STREQUAL "")
  set(SIMD_INSTALL_DIR $ENV{SIMD_INSTALL_DIR})
endif(NOT SIMD_INSTALL_DIR AND NOT $ENV{SIMD_INSTALL_DIR} STREQUAL "")

find_path(SimD_INCLUDE_DIR
    NAMES dds/dds.hpp
    PATHS ${SIMD_INSTALL_DIR}/include
)

set(SimD_INCLUDE_DIRS ${SimD_INCLUDE_DIR} CACHE FILEPATH "SimD include directories")

# Find libraries
find_library(SimD_LIBRARY
    NAMES SimD
    PATHS ${SIMD_INSTALL_DIR}/lib
)

set(SimD_LIBRARIES ${SimD_LIBRARY} CACHE FILEPATH "SimD libraries")

mark_as_advanced(
    SimD_INCLUDE_DIRS
    SimD_LIBRARIES
)

find_package_handle_standard_args(SimD FOUND_VAR SimD_FOUND REQUIRED_VARS SimD_LIBRARIES)
