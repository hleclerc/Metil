LOC_MC = ./metil_comp --comp-dir compilations -Isrc
PRG = tests/test.cpp
INSTALL = `pwd`

all: make_metil_comp

make_metil_comp:
	export D="#define INSTALL_DIR \"${INSTALL}\""; grep "$$D" src/Metil/Level1/InstallDir.h || echo "$$D" > src/Metil/Level1/InstallDir.h
	make -j8 metil_comp

install: ./metil_comp
	./install.sh

test:
	${LOC_MC} -o tests/main -g3 -O3 ${PRG}

test_gdb:
	${LOC_MC} -o tests/main --gdb -g3 tests/main.cpp

test_valgrind:
	${LOC_MC} -o tests/main --exec-using "valgrind --db-attach=yes --num-callers=30" -g3 tests/main.cpp
	
test_valgrind_full:
	${LOC_MC} -o tests/main --exec-using "valgrind --leak-check=full --show-reachable=yes" -g3 tests/main.cpp

metil_gen:
	${LOC_MC} -g3 src/Metil/Level1/metil_parse.cpp `find src -name "*.cpp" -o -name "*.h"`
	#metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`

make_unit_tests:
	make clean
	make -j8 metil_comp
	cd unit_tests; python run_unit_test.py
	mkdir -p html; cp unit_tests/report.html html

documentation:
	doxygen doc/Doxyfile
	mkdir -p html/images; cp doc/images/* html/images
	sed -e "s/ = html/ = html\/Level1/g; s/= Level1/= /g" doc/Doxyfile > html/Doxyfile_Level1
	doxygen html/Doxyfile_Level1
	mkdir -p html/Level1/images; cp doc/images/* html/Level1/images

pull_and_push_if_valid:
	git pull
	make make_unit_tests
	make documentation
	git push production

archive:
	git archive -o Metil-0.zip --prefix=Metil-0.0.0/ HEAD

clean:
	rm -rf compilations 2> /dev/null

metil_comp_mk:
	${LOC_MC} --static -make metil_comp.mk -o ./metil_comp -g3 -O3 src/metil_comp.cpp
# 	sed -i -e s@`pwd`/@@g metil_comp.mk

c: 
	make metil_comp_mk
	make clean

include metil_comp.mk
