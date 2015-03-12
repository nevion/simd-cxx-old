##############################################################################
# Try to find OpenSplice
# Once done this will define:
#
#  OpenSplice_FOUND - system has OpenSplice.
#  OpenSplice_INCLUDE_DIRS - the OpenSplice include directory.
#  OpenSplice_LIBRARIES - Link these to use OpenSplice.
#  OpenSplice_IDLGEN_BINARY - Binary for the IDL compiler.
#
# You need the environment variable $OSPL_HOME to be set to your OpenSplice
# installation directory.
# This script also includes the MacroOpenSplice.cmake script, which is useful
# for generating code from your idl.
#
##############################################################################
# Courtesy of Ivan Galvez Junquera <ivgalvez@gmail.com>
# Revamped by Jason Newton <nevion@gmail.com>
##############################################################################

find_package(PackageHandleStandardArgs)

find_path(OpenSplice_INCLUDE_DIR
    NAMES ccpp_dds_dcps.h
    PATHS $ENV{OSPL_HOME}/include/dcps/C++/SACPP
)

set(OpenSplice_INCLUDE_DIRS
    ${OpenSplice_INCLUDE_DIR}
    $ENV{OSPL_HOME}/include
    $ENV{OSPL_HOME}/include/sys
)
set(OpenSplice_INCLUDE_DIRS "${OpenSplice_INCLUDE_DIRS}" CACHE FILEPATH "OpenSplice include directories")

# Find libraries
find_library(DCPSGAPI_LIBRARY
    NAMES dcpsgapi
    PATHS $ENV{OSPL_HOME}/lib
)

find_library(DCPSSACPP_LIBRARY
    NAMES dcpssacpp
    PATHS $ENV{OSPL_HOME}/lib
)

find_library(DDSDATABASE_LIBRARY
    NAMES ddsdatabase
    PATHS $ENV{OSPL_HOME}/lib
)

find_library(DDSOS_LIBRARY
   NAMES ddsos
   PATHS $ENV{OSPL_HOME}/lib
)

set(OpenSplice_LIBRARIES
    ${DCPSGAPI_LIBRARY}
    ${DCPSSACPP_LIBRARY}
    ${DDSDATABASE_LIBRARY}
    ${DDSOS_LIBRARY}
)
set(OpenSplice_LIBRARIES "${OpenSplice_LIBRARIES}" CACHE FILEPATH "OpenSplice libraries")

# Binary for the IDL compiler
set(OpenSplice_IDLGEN_BINARY $ENV{OSPL_HOME}/bin/idlpp CACHE FILEPATH "OpenSplice idlpp IDL tool")

mark_as_advanced(
    OpenSplice_INCLUDE_DIRS
    OpenSplice_LIBRARIES
    OpenSplice_IDLGEN_BINARY
)

find_package_handle_standard_args(OpenSplice FOUND_VAR OpenSplice_FOUND REQUIRED_VARS OpenSplice_LIBRARIES)


include(OpenSplice)
