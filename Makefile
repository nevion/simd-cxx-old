
simd:
	make -C ./src/dds $*

demo:
	make -C ./demo $*

all:
	make -C ./src/dds $*
	make -C ./demo $*

clean:
	make -C ./src/dds clean $*

cleanall:
	make -C ./src/dds clean $*
	make -C ./demo clean $*

