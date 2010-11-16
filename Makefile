LOC_MC = ./metil_comp --comp-dir compilations

all: ./metil_comp

install: ./metil_comp
	./install.sh

test: # make_metil_comp
	${LOC_MC} -o tests/main -g3 -Isrc tests/main.cpp

test_gdb:
	${LOC_MC} -o tests/main --gdb -g3 -Isrc tests/main.cpp

test_valgrind:
	${LOC_MC} -o tests/main --exec-using "valgrind --num-callers=30" -g3 tests/main.cpp
	
test_valgrind_full:
	${LOC_MC} -o tests/main --exec-using "valgrind --leak-check=full --show-reachable=yes" -g3 tests/main.cpp

metil_gen:
	${LOC_MC} -g3 src/Level1/metil_parse.cpp `find src -name "*.cpp" -o -name "*.h"`
	#metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`

comp:
	${LOC_MC} src/make_compressed_struct.cpp

make_unit_tests: clean
	cd unit_tests; python run_unit_test.py

documentation:
	doxygen doc/Doxyfile
	mkdir -p html/images; cp doc/images/* html/images
	sed -e "s/ = html/ = html\/Level1/g; s/= Level1/= /g" doc/Doxyfile > html/Doxyfile_Level1
	doxygen html/Doxyfile_Level1
	mkdir -p html/Level1/images; cp doc/images/* html/Level1/images

archive:
	git archive -o Metil-0.zip --prefix=Metil-0.0.0/ HEAD
	#git archive -oo -format=tar --prefix=Metil-0.0.0/ HEAD | gzip > Metil-0.0.0.tgz

clean:
	rm -rf compilations 2> /dev/null

metil_comp_mk:
	${LOC_MC} --static -make metil_comp.mk -o ./metil_comp -O3 src/metil_comp.cpp
	sed -i -e s@`pwd`/@@g metil_comp.mk

include metil_comp.mk
