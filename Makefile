all: make_metil_comp

install: all
	./install.sh

make_metil_comp:
	metil_comp/metil_comp -ne -o src/metil_comp -O3 -Isrc src/metil_comp.cpp
#	make -C metil_comp

test: # make_metil_comp
	metil_comp -o tests/main -g3 -Isrc tests/main.cpp

test_gdb:
	src/metil_comp --gdb -g3 -Isrc tests/main.cpp

test_valgrind:
	src/metil_comp --exec-using "valgrind --num-callers=30" -g3 -Isrc tests/main.cpp
	
test_valgrind_full:
	src/metil_comp --exec-using "valgrind --leak-check=full --show-reachable=yes" -g3 -Isrc tests/main.cpp

metil_gen:
	metil_comp -g3 -Isrc src/Level1/metil_parse.cpp `find src -name "*.cpp" -o -name "*.h"`
# 	metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`

comp:
	src/metil_comp src/make_compressed_struct.cpp


tests: clean
	cd unit_tests; python run_unit_test.py

documentation:
	doxygen doc/Doxyfile
	mkdir -p html/images; cp doc/images/* html/images
	sed -e "s/ = html/ = html\/Level1/g; s/= Level1/= /g" doc/Doxyfile > html/Doxyfile_Level1
	doxygen html/Doxyfile_Level1
	mkdir -p html/Level1/images; cp doc/images/* html/Level1/images

archive:
	git archive -o Metil-0.zip --prefix=Metil-0.0.0/ HEAD
# 	git archive -oo -format=tar --prefix=Metil-0.0.0/ HEAD | gzip > Metil-0.0.0.tgz

clean:
	rm -f unit_tests/compilations/* 2> /dev/null
	rm -f tests/compilations/* 2> /dev/null
