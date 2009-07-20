
simd:
	make -C ./src/simd $*

demo:
	make -C ./demo $*

all:
	make -C ./src/simd $*
	make -C ./demo $*

clean:
	make -C ./src/simd clean $*
	make -C ./demo clean $*

