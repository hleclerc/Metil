all:
	metil_comp -Isrc src/main.cpp

metil_gen:
	metil_comp -Isrc src/metil_parse.cpp `find . -name "*.cpp"`
