#
# C++ Compiler
#
CXX = g++
GCC = gcc

##############################################################################
#
# cp/rm
#
CP = cp
RM = rm -f
##############################################################################
#
# Library Macros
#
include $(SIMD_HOME)/config/lib/LIBRARY.MACROS.GNU

CXXFLAGS = \
   $(SIMD_CXXFLAGS) 


INCLUDE_DIRS = \
   $(SIMD_INCLUDE_DIRS) 

LD_DIRS = \
   $(SIMD_LD_DIRS) 

LD_LIBS = \
   $(SIMD_LD_LIBS) 

LD_FLAGS =

##############################################################################

ifeq ($(profile),1)
   CXXFLAGS += -pg
endif #trace

ifeq ($(debug),0)
   CXXFLAGS +=
else
  CXXFLAGS += -g
endif # debug

ifeq (,$(optimize))
   CXXFLAGS += -O2
else
   CXXFLAGS += -O$(optimize)
endif # optimize

