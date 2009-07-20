all: 
	make pub $*
	make sub $*
	make asub

deep:
	make idl $*
	make all $*

idl:
	make -f Makefile.idl $*

pub:
	make -f Makefile.pub $*

sub:
	make -f Makefile.sub $*


asub:
	make -f Makefile.asub

clean:
	make -f Makefile.pub clean $*
	make -f Makefile.sub clean $*
	make -f Makefile.asub clean $*
	$(RM) *~ *.o *.d

real-clean:
	make clean $*
	make -f Makefile.idl clean $*  