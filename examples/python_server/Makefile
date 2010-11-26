all: test

test: server_objects_wrap.cpp
	metil_comp -I/usr/include/python2.6/ -dylib -O3 -g3 -o _server_objects.so -exec "export; python server.py" server_objects_wrap.cpp 


server_objects_wrap.cpp: server_objects.i
	swig -o server_objects_wrap.cpp -python -c++ server_objects.i

clean:
	# rm -f compilations/*
	rm -f _server_objects.so
	rm -f server_objects.py server_objects.pyc
	rm -f server_objects_wrap.cpp
	