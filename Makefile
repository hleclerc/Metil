
all: std
# 	make -C examples/python_server

server:
	metil_comp -g3 -Isrc examples/server/main.cpp

std:
	metil_comp -g3 -Isrc src/main.cpp

gdb:
	metil_comp --exec-using gdb -g3 -Isrc src/main.cpp

valgrind:
	metil_comp --exec-using valgrind -g3 -Isrc src/main.cpp

metil_gen:
	metil_comp -g3 -Isrc src/metil_parse.cpp `find . -name "*.cpp"`
# 	metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`
