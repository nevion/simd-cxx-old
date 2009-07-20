#-*-Makefile-*-

include $(SIMD_HOME)/config/lib/MACROS.COMMOM.GNU

LD_DIRS += \
   -L$(SIMD_HOME)/lib


LD_LIBS += -lrt -ldl -lsimd

TARGET_INSTALL_DIR = $(SIMD_HOME)/bin
