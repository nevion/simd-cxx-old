#-*-Makefile-*-

CONFIG += qt debug
FORMS=iShapesForm.ui readerQosForm.ui writerQosForm.ui
HEADERS = ShapesDialog.hpp WriterQosDialog.hpp ShapesWidget.hpp ReaderQosDialog.hpp
RESOURCES=ishapes.qrc

SOURCES+=BouncingShapeDynamics.cpp \
Circle.cpp \
DDSShapeDynamics.cpp \
Shape.cpp \
ShapeDynamics.cpp \
ShapesDialog.cpp \
ShapesWidget.cpp \
Square.cpp \
Triangle.cpp \
main.cpp \
WriterQosDialog.cpp \
ReaderQosDialog.cpp \
gen/ishape.cpp \
gen/ishapeDcps.cpp  \
gen/ishapeDcps_impl.cpp \
gen/ishapeSplDcps.cpp

#moc_ShapesDialog.cpp \
#moc_ShapesWidget.cpp \
#moc_WriterQosDialog.cpp\

TARGET=ishapes

INCLUDEPATH+=${SIMD_INSTALL_DIR}/include ${OSPL_HOME}/include $(BOOST_INCLUDE) \
             $(OSPL_HOME)/include/dcps/C++/SACPP \
             $(OSPL_HOME)/include \
             $(OSPL_HOME)/include/sys 

LIBS += -L${OSPL_HOME}/lib -L${BOOST_LIB} -L${SIMD_INSTALL_DIR}/lib\
        -lddsdatabase -ldcpsgapi -ldcpssacpp -lddsos \
        -lboost_program_options  -lSimD 

