cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ../../cmake)
project (hello)
find_package(OpenSplice REQUIRED)
include (osmacros)
find_package (Boost REQUIRED thread program_options system)
find_package (SimD REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${OpenSplice_INCLUDE_DIRS}
  ${SimD_INCLUDE_DIRS}
)


set (idls hello.idl)

set(OpenSplice_DATAMODEL)
foreach(idl ${idls})
    OpenSplice_IDLGEN(TARGET ${idl} SRC ${idl} OUTPUT_PREFIX gen)
    list(APPEND OpenSplice_DATAMODEL ${IDLGEN_OUTPUT_SRCS})
    set(OpenSplice_DATAMODEL ${IDLGEN_OUTPUT_SRCS})
endforeach(idl)

set (PUB_SOURCES
 hello-pub.cpp
)
set (SUB_SOURCES
 hello-sub.cpp
)

set (PUB_EXE hello-pub)
set (SUB_EXE hello-sub)
set (DATAMODEL datamodel)

add_executable (${PUB_EXE} ${PUB_SOURCES})
add_executable (${SUB_EXE} ${SUB_SOURCES})
add_library (${DATAMODEL} STATIC ${OpenSplice_DATAMODEL})
add_dependencies(${DATAMODEL} ${idls}) 
#add_library (${DATAMODEL} SHARED ${OpenSplice_DATAMODEL})

add_definitions (
 ${OpenSplice_DEFINITIONS}
 ${DEFINITIONS}
)

# Linkar contra librerias deseadas.
target_link_libraries (
  ${DATAMODEL} 
  ${OpenSplice_LIBRARIES}
  ${Boost_LIBRARIES}
  ${SimD_LIBRARIES}
)

target_link_libraries (${PUB_EXE}
 ${OpenSplice_LIBRARIES}
 ${Boost_LIBRARIES}
 ${DATAMODEL} 
)

target_link_libraries (${SUB_EXE}
 ${OpenSplice_LIBRARIES}
 ${Boost_LIBRARIES}
 ${DATAMODEL}
)
