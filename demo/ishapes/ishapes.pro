#-*-Makefile-*-

CONFIG += qt debug
FORMS=iShapesForm.ui

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
moc_ShapesDialog.cpp \
moc_ShapesWidget.cpp \
gen/ishape.cpp \
gen/ishapeDcps.cpp  \
gen/ishapeDcps_impl.cpp \
gen/ishapeSplDcps.cpp


TARGET=ishapes

INCLUDEPATH+=${SIMD_HOME}/src ${OSPL_HOME}/include $(BOOST_INCLUDE) \
             $(OSPL_HOME)/include/dcps/C++/SACPP \
             $(OSPL_HOME)/include \
             $(OSPL_HOME)/include/sys 

LIBS += -L${OSPL_HOME}/lib -L${BOOST_LIB} -L${SIMD_HOME}/lib\
        -lddsdatabase -ldcpsgapi -ldcpssacpp -lddsos \
        -lboost_program_options  -lsimd 

