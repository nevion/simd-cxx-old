##############################################################################
# Try to find BOOST
# Once done this will define:
#
#  BOOST_FOUND - system has BOOST.
#  BOOST_INCLUDE_DIRS - the BOOST include directory.
#  BOOST_LIBRARIES - Link these to use BOOST.
#  BOOST_IDLGEN_BINARY - Binary for the IDL compiler.
#
# You need the environment variable $OSPL_HOME to be set to your BOOST
# installation directory.
# This script also includes the MacroBOOST.cmake script, which is useful
# for generating code from your idl.
#
##############################################################################
# Courtesy of Ivan Galvez Junquera <ivgalvez@gmail.com>
##############################################################################
FIND_PATH(BOOST_INCLUDE_DIR
	NAMES
		boost/shared_ptr.hpp
	PATHS
		$ENV{BOOST_INCLUDE}
)

IF (BOOST_INCLUDE_DIR)
	MESSAGE(STATUS "Found Boost include dir: ${BOOST_INCLUDE_DIR}")
ELSE (BOOST_INCLUDE_DIR)
  MESSAGE(FATAL_ERROR "Could not find Boost include dir")
ENDIF (BOOST_INCLUDE_DIR)

SET(BOOST_INCLUDE_DIRS 
	${BOOST_INCLUDE_DIR} 
)

# Find libraries
FIND_LIBRARY(BOOST_THREAD_LIBRARY
	NAMES
		boost_thread
	PATHS
		$ENV{BOOST_LIB}
)

IF (BOOST_THREAD_LIBRARY)
	MESSAGE(STATUS "Found Boost thread library: ${BOOST_THREAD_LIBRARY}")
ELSE (BOOST_THREAD_LIBRARY)
  MESSAGE(FATAL_ERROR "Could not find Boost thread library")
ENDIF (BOOST_THREAD_LIBRARY)

FIND_LIBRARY(BOOST_SYSTEM_LIBRARY
	NAMES
		boost_system
	PATHS
		$ENV{BOOST_LIB}
)

IF (BOOST_SYSTEM_LIBRARY)
	MESSAGE(STATUS "Found Boost System library: ${BOOST_SYSTEM_LIBRARY}")
ELSE (BOOST_SYSTEM_LIBRARY)
  MESSAGE(FATAL_ERROR "Could not find Boost System library")
ENDIF (BOOST_SYSTEM_LIBRARY)

FIND_LIBRARY(BOOST_SIGNALS_LIBRARY
	NAMES
		boost_signals
	PATHS
		$ENV{BOOST_LIB}
)

IF (BOOST_SIGNALS_LIBRARY)
	MESSAGE(STATUS "Found Boost signales library: ${BOOST_SIGNALS_LIBRARY}")
ELSE (BOOST_SIGNALS_LIBRARY)
  MESSAGE(FATAL_ERROR "Could not find Boost signals library")
ENDIF (BOOST_SIGNALS_LIBRARY)

FIND_LIBRARY(BOOST_POPTIONS_LIBRARY
	NAMES
		boost_program_options
	PATHS
		$ENV{BOOST_LIB}
)

SET(BOOST_LIBRARIES
			${BOOST_THREAD_LIBRARY}
			${BOOST_SIGNALS_LIBRARY}
			${BOOST_POPTIONS_LIBRARY}
			${BOOST_SYSTEM_LIBRARY}
)


IF (BOOST_INCLUDE_DIRS AND BOOST_LIBRARIES)
	SET(BOOST_FOUND TRUE)
ENDIF (BOOST_INCLUDE_DIRS AND BOOST_LIBRARIES)

IF (BOOST_FOUND)
	MESSAGE(STATUS "Found BOOST C++ libraries: ${BOOST_LIBRARIES}")
ELSE (BOOST_FOUND)
#	IF (BOOST_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find BOOST")
#	ENDIF (BOOST_FIND_REQUIRED)
ENDIF (BOOST_FOUND)

MARK_AS_ADVANCED(BOOST_INCLUDE_DIRS BOOST_LIBRARIES)

