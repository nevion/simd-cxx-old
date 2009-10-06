#-*-Makefile-*-
##############################################################################

OBJS    := $(patsubst %.cpp,%.o,$(SRCS)) 
LT_OBJS := $(patsubst %.cpp,%.lo,$(SRCS)) 
DEPS    := $(patsubst %.o,%.d,$(OBJS)) 

##############################################################################

COMPILE_CXX_COMMAND = \
   $(CXX) $(INCLUDE_DIRS) $(CXXFLAGS) -c


LINK_TARGET = \
   $(CXX) $(LD_FLAGS) $(LD_DIRS)  $(LD_LIBS) \
   $(OBJS) -o $(TARGET)

INSTALL_TARGET = \
   $(CP) $(TARGET) $(TARGET_INSTALL_DIR);

UNINSTALL_TARGET = \
   $(RM) $(TARGET_INSTALL_DIR)/$(TARGET)

##############################################################################

all: $(TARGET) $(TARGET_INSTALL_DIR)/$(TARGET)


$(TARGET_INSTALL_DIR)/$(TARGET):
	$(INSTALL_TARGET) 

$(TARGET): $(DEPS) $(OBJS)
	$(LINK_TARGET)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -M $< > $@
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -M $< | sed s/\\.o/.d/ > $@

%.o: %.cpp
	$(COMPILE_CXX_COMMAND) -o $@  $<

clean:
	$(UNINSTALL_TARGET)
	-rm -f $(OBJS) $(LT_OBJS) $(DEPS) $(TARGET)

cleanobj:
	-rm -f $(OBJS) $(LT_OBJS)

realclean: clean
	find -type d -name .libs | xargs $(RM) -Rf
	find -type d -name "*.so" | xargs $(RM) -f

depend: $(DEPS)
	@echo "Depdendencies Updated."

-include $(DEPS)
