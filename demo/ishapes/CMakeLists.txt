cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ../../cmake)
project (ishapes)
include (MacroOpenSplice)
include (osmacros)
find_package (OpenSplice REQUIRED)
find_package (Boost REQUIRED COMPONENTS thread program_options system)
find_package (SimD REQUIRED)

find_package (Qt4 REQUIRED COMPONENTS QtCore QtGui)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${OpenSplice_INCLUDE_DIRS}
  ${SimD_INCLUDE_DIRS}
)

set (ISHAPES_EXE ishapes)
set (DATAMODEL datamodel)

include(
${QT_USE_FILE}
)

 
set (idls ishape.idl ishapeiop.idl)


foreach(idl ${idls})
	OpenSplice_IDLGEN (${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1.cpp" VARS_1 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1.h" VARS_2 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps.cpp" VARS_3 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps.h" VARS_4 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps_impl.cpp" VARS_5 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps_impl.h" VARS_6 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1SplDcps.cpp" VARS_7 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1SplDcps.h" VARS_8 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/ccpp_\\1.h" VARS_9 ${idl})
	set(OpenSplice_DATAMODEL ${OpenSplice_DATAMODEL} ${VARS_1} ${VARS_2} ${VARS_3} ${VARS_4} ${VARS_5} ${VARS_6} ${VARS_7} ${VARS_8} ${VARS_9})
endforeach(idl)

set (QT_MOC_HEADERS
  ReaderQosDialog.hpp
  ShapesDialog.hpp
  ShapesWidget.hpp
  WriterQosDialog.hpp
  FilterDialog.hpp
)
if (APPLE)
  set (QT_UI_SOURCES
          macos/iShapesForm.ui
          macos/readerQosForm.ui
          macos/writerQosForm.ui
          macos/filterForm.ui)
else (APPLE)
  set (QT_UI_SOURCES
          iShapesForm.ui
          readerQosForm.ui
          writerQosForm.ui
          filterForm.ui)
endif (APPLE)

set (ISHAPE_RCS ./ishape.qrc)
QT4_ADD_RESOURCES (ISHAPE_RC_SRCS ${ISHAPE_RCS})
QT4_WRAP_CPP(QT_MOC_SOURCES ${QT_MOC_HEADERS})
QT4_WRAP_UI(QT_UI_HEADERS ${QT_UI_SOURCES})

set (ISHAPES_SOURCES
 ${QT_MOC_SOURCES}
 ${QT_UI_SOURCES}
 BouncingShapeDynamics.cpp
 Circle.cpp
 DDSShapeDynamics.cpp
 main.cpp
 ReaderQosDialog.cpp
 Shape.cpp
 ShapeDynamics.cpp
 ShapesDialog.cpp
 ShapesWidget.cpp
 Square.cpp
 Triangle.cpp
 WriterQosDialog.cpp
 FilterDialog.cpp
)


add_executable (${ISHAPES_EXE} ${ISHAPES_SOURCES} ${ISHAPE_RC_SRCS})
#add_library (${DATAMODEL} SHARED ${OpenSplice_DATAMODEL} )
add_library (${DATAMODEL} STATIC ${OpenSplice_DATAMODEL} )

add_definitions (
 ${OpenSplice_DEFINITIONS}
 ${DEFINITIONS}
)

target_link_libraries (
  ${DATAMODEL} 
  ${OpenSplice_LIBRARIES}
  ${Boost_LIBRARIES}
  ${SimD_LIBRARIES}
)

target_link_libraries (${ISHAPES_EXE}
 ${OpenSplice_LIBRARIES}
 ${Boost_LIBRARIES}
 ${DATAMODEL}
 ${QT_LIBRARIES}
)
