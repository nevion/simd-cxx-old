all: 
	make pub $*
	make sub $*

deep:
	make idl $*
	make all $*

idl:
	make -f Makefile.idl $*

pub:
	make -f Makefile.pub $*

sub:
	make -f Makefile.sub $*



clean:
	make -f Makefile.pub clean $*
	make -f Makefile.sub clean $*
	$(RM) *~

real-clean:
	make clean $*
	make -f Makefile.idl clean $* 