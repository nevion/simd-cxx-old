#
# C++ Macros
#
CARDAMOM_BIN_HOME = $(CDMW_HOME)

CARDAMOM_INCLUDE_DIRS = \
   -I. \
   -I$(CARDAMOM_BIN_HOME)/include/c++ \
   -I$(CARDAMOM_BIN_HOME)/include/c++/FaultTolerance \
   -I$(CARDAMOM_BIN_HOME)/include/c++/SystemMngt \
   -I$(CARDAMOM_BIN_HOME)/include/c++/Repository \
   -I$(CARDAMOM_BIN_HOME)/include/c++/LifeCycle \
   -I$(CARDAMOM_BIN_HOME)/include/c++/Time \
   -I$(CARDAMOM_BIN_HOME)/include/c++/LifeCycle/idllib/TAO-1.3.1 \
   -I$(XERCES_HOME)/include


#   $(addprefix -I, $(shell find $(CDMW_HOME)/include/c++ -type d)) \

CARDAMOM_LD_DIRS = \
   -L$(CARDAMOM_BIN_HOME)/lib/c++

CARDAMOM_LD_LIBS = \
   -lcdmwcommon \
   -lcdmworbsupport \
   -lcdmwossupport \
   -lcdmwosthreads \
   -lcdmwcommonsvcsfederation \
   -lcdmwclockservice \
   -lcdmwcommonidl

CARDAMOM_CXXFLAGS = \
   -Wno-deprecated \
   -D_REENTRANT -DCDMW_ASSERT_NO_THROW -DCDMW_POSIX -Dlinux -Dtao=4203 \
   -DCDMW_ORB_VDR=4203 -DCDMW_ORB_VER=141 


ifeq ($(trace),1)
   CARDAMOM_CXXFLAGS += -DCARDAMOM_TRACE=1
endif #trace


