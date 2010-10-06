all:
	metil_comp -g3 -Isrc src/main.cpp
	
valgrind:
	metil_comp --exec-using "valgrind --leak-check=full" -g3 -Isrc src/main.cpp

metil_gen:
	metil_comp -g3 -Isrc src/metil_parse.cpp --no-h `find . -name "*.cpp"`
# 	metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`

metil_gen_h:
	metil_comp -g3 -Isrc src/metil_parse.cpp `find . -name "*.cpp"`
# 	metil_comp -g3 --valgrind -Isrc src/metil_parse.cpp `find . -name "*.cpp"`
