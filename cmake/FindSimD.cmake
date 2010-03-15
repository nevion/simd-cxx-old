##############################################################################
# Looks for the SimD library installation and defines:
#
#  SimD_FOUND - system has SimD.
#  SimD_INCLUDE_DIRS - the SimD include directory.
#  SimD_LIBRARIES - Link these to use SimD.
#
# You need the environment variable $SIMD_INSTALL_DIR to be set to your SimD
# installation directory.
##############################################################################

FIND_PATH(SimD_INCLUDE_DIR
	NAMES
		dds/dds.hpp
	PATHS
		$ENV{SIMD_INSTALL_DIR}/include
)

IF (SimD_INCLUDE_DIR)
	MESSAGE(STATUS "Found SimD include dir: ${SimD_INCLUDE_DIR}")
ELSE (SimD_INCLUDE_DIR)
  MESSAGE(FATAL_ERROR "Could not find SimD include dir")
ENDIF (SimD_INCLUDE_DIR)

SET(SimD_INCLUDE_DIRS 
	${SimD_INCLUDE_DIR} 
)

# Find libraries
FIND_LIBRARY(SimD_LIBRARY
	NAMES
		SimD
	PATHS
		$ENV{SIMD_INSTALL_DIR}/lib
)

SET(SimD_LIBRARIES
		${SimD_LIBRARY}
)


IF (SimD_INCLUDE_DIRS AND SimD_LIBRARIES)
	SET(SimD_FOUND TRUE)
ENDIF (SimD_INCLUDE_DIRS AND SimD_LIBRARIES)

IF (SimD_FOUND)
	MESSAGE(STATUS "Found SimD C++ libraries: ${SimD_LIBRARIES}")
ELSE (SimD_FOUND)
	IF (SimD_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find SimD")
	ENDIF (SimD_FIND_REQUIRED)
ENDIF (SimD_FOUND)

MARK_AS_ADVANCED(SimD_INCLUDE_DIRS SimD_LIBRARIES)

