all: make_metil_comp

install: all
	sudo ln -s `pwd`/metil_comp/metil_comp /usr/bin/

make_metil_comp:
	make -C metil_comp

test:
	metil_comp -g3 -Isrc src/main.cpp

test_gdb:
	metil_comp --exec-using gdb -g3 -Isrc src/main.cpp

test_valgrind:
	metil_comp --exec-using valgrind -g3 -Isrc src/main.cpp

metil_gen:
	metil_comp -g3 -Isrc src/metil_parse.cpp `find . -name "*.cpp"`
# 	metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`

comp:
	metil_comp src/make_compressed_struct.cpp
