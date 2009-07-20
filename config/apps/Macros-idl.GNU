#-*-Makefile-*-

##############################################################################
# IDL Compiler 
include $(SIMD_HOME)/config/lib/MACROS.COMMOM.GNU
IDLC=$(OSPL_HOME)/bin/idlpp
IDLC_FLAGS=-S -l cpp -d gen

TARGET_IDL=