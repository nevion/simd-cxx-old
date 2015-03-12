##############################################################################
# OpenSplice_IDLGEN(TARGET target SRC file.idl OUTPUT_PREFIX generated)
#
# Macro to generate OpenSplice DDS sources from a given idl file with the
# data structures.
#
##############################################################################
# Courtersy of Ivan Galvez Junquera <ivgalvez@gmail.com>
# Revamped by Jason Newton <nevion@gmail.com>
##############################################################################


# Macro to create a list with all the generated source files for a given .idl filename
include(CMakeParseArguments)
macro(OpenSplice_IDLGEN)
    CMAKE_PARSE_ARGUMENTS(IDLGEN "" "TARGET;SRC;OUTPUT_PREFIX" "" ${ARGN})
    get_filename_component(IDLGEN_SRC_BASENAME ${IDLGEN_SRC} NAME_WE)
    set(IDLGEN_OUTPUT_SRCS)
    if(NOT IDLGEN_OUTPUT_PREFIX)
        set(IDLGEN_OUTPUT_PREFIX "generated")
    endif()
    set(IDLGEN_OUTPUT_INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR})
    set(IDLGEN_OUTPUT_PATH ${IDLGEN_OUTPUT_INCLUDE_PATH}/${IDLGEN_OUTPUT_PREFIX})
    list(APPEND IDLGEN_OUTPUT_SRCS ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}.cpp ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}.h)
    list(APPEND IDLGEN_OUTPUT_SRCS ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}Dcps.cpp ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}Dcps.h)
    list(APPEND IDLGEN_OUTPUT_SRCS ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}Dcps_impl.cpp ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}Dcps_impl.h)
    list(APPEND IDLGEN_OUTPUT_SRCS ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}SplDcps.cpp ${IDLGEN_OUTPUT_PATH}/${IDLGEN_SRC_BASENAME}SplDcps.h)
    list(APPEND IDLGEN_OUTPUT_SRCS ${IDLGEN_OUTPUT_PATH}/ccpp_${IDLGEN_SRC_BASENAME}.h)
    add_custom_command(
        OUTPUT ${IDLGEN_OUTPUT_SRCS}
        COMMAND ${OpenSplice_IDLGEN_BINARY} ARGS -S -l cpp -d ${IDLGEN_OUTPUT_PATH} ${IDLGEN_SRC}
        DEPENDS ${IDLGEN_SRC}
        COMMENT "OpenSplice based IDLGEN for ${IDLGEN_SRC}"
    )
    add_custom_target(${IDLGEN_TARGET} DEPENDS ${IDLGEN_OUTPUT_SRCS})
endmacro(OpenSplice_IDLGEN)
