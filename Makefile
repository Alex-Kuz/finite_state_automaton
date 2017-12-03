Compiler := g++-7
CVersion := -std=c++17
Flags    := $(CVersion) -Wall


SrcDir := fs_machine
AxLibDir := fs_machine/ax_libs

TestsDir := tests


test_all: bitvector_test matrix_test
	

bitvector_test: 
	$(Compiler) $(Flags) $(TestsDir)/bitvector.cpp -o bitvector.test.bin
	./bitvector.test.bin

matrix_test:
	$(Compiler) $(Flags) $(TestsDir)/matrix.cpp -o matrix.test.bin
	./matrix.test.bin

base_fsm_test:
	$(Compiler) $(Flags) $(TestsDir)/base_fsm.cpp -o base_fsm.test.bin
	./base_fsm.test.bin



clear: 
	rm -rf *.o *.bin *.out