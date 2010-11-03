all: make_metil_comp

install: all
	./install.sh

make_metil_comp:
	make -C metil_comp

test:
	metil_comp -o tests/main -g3 -Isrc tests/main.cpp

test_gdb:
	metil_comp --exec-using gdb -g3 -Isrc tests/main.cpp

test_valgrind:
	metil_comp --exec-using "valgrind --leak-check=full" -g3 -Isrc tests/main.cpp

metil_gen:
	metil_comp -g3 -Isrc src/Level1/metil_parse.cpp `find src -name "*.cpp" -o -name "*.h"`
# 	metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`

comp:
	metil_comp src/make_compressed_struct.cpp

clean:
	rm -rf tests/compilations 2> /dev/null
	rm -rf unit_tests/compilations 2> /dev/null

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
	