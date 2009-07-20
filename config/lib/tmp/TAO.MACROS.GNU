#
# C++ Macros
#
ORB_CXXFLAGS = \
   -D_REENTRANT -DACE_HAS_AIO_CALLS -D_GNU_SOURCE 

ORB_INCLUDE_DIRS = \
   -I$(ACE_HOME) -I$(TAO_ROOT) -I$(TAO_ROOT)/orbsvcs \
   -I$(TAO_HOME)/orbsvcs/orbsvcs

ORB_LD_DIRS = \
   -L$(ACE_HOME)/ace

ORB_LD_LIBS = \
   -lTAO_Svc_Utils -lTAO_Messaging \
   -lTAO_PortableServer -lTAO_IORTable \
   -lTAO -lACE -ldl -lpthread -lrt -lTAO_CosProperty

# -lTAO_IORInterceptor -lTAO_ObjRefTemplate
##############################################################################

#
# IDL
#
IDLC = tao_idl
IDL_FLAGS = -Ge 2 -o $(IDL_OUTPUT_DIR)

COMPILE_IDL_COMMAND = \
   $(IDLC) $(IDL_FLAGS) $(IDL_INCLUDE_DIRS)

##############################################################################
