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

set(OpenSplice_LIBS dcpsgapi dcpssacpp ddsdatabase ddsos ddskernel)
set(OpenSplice_LIBRARIES)
foreach(lib ${OpenSplice_LIBS})
    find_library(OpenSplice_${lib}_LIBRARY
        NAMES ${lib}
        PATHS $ENV{OSPL_HOME}/lib
    )
    list(APPEND OpenSplice_LIBRARIES ${OpenSplice_${lib}_LIBRARY})
endforeach()

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
