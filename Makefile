LOC_MC = metil_comp --comp-dir compilations -Isrc
PRG = tests/test_HttpSessionServer.cpp
INSTALL = `pwd`

all: metil_comp

inst_dir:
	export D="#define INSTALL_DIR \"${INSTALL}\""; grep "$$D" src/Metil/Level1/InstallDir.h || echo "$$D" > src/Metil/Level1/InstallDir.h

metil_comp: inst_dir
	${MAKE} -j8 -f metil_comp.mk
	
metil_comp_win: inst_dir
	${MAKE} -j8 -f metil_comp_win.mk

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

unit_tests:
#	make clean
#	make -j8 metil_comp
	cd unit_tests; python run_unit_test.py ../
	
	#mkdir -p .log; cp -r unit_tests/.log/* .log

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

push_production_if_valid :
	git push production master

archive:
	git archive -o Metil-0.zip --prefix=Metil-0.0.0/ HEAD

.PHONY: unit_tests




clean:
	rm -rf compilations 2> /dev/null



metil_comp_mk:
	${LOC_MC} --static -make metil_comp.mk -o ./metil_comp -g3 -O3 src/metil_comp.cpp
	${LOC_MC} -DWIN32 --static -make metil_comp_win.mk -o ./metil_comp.exe -O3 src/metil_comp.cpp
	sed -i -e s@`pwd`/@@g metil_comp.mk
	sed -i -e s@`pwd`/@@g metil_comp_win.mk

c: 
	make metil_comp_mk
	make clean
