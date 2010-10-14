all: std

test: wrap
	python test.py

wrap: server_objects_wrap.cpp
	metil_comp -I../../src -I/usr/include/python2.6/ -dylib -O3 -g3 -o _server_objects.so server_objects_wrap.cpp

server_objects_wrap.cpp: server_objects.i
	swig -o server_objects_wrap.cpp -python -c++ server_objects.i

std: wrap
	metil_comp -I../../src -g3 main.cpp

