cpp:
	g++ main.cpp cpplib_interface.cpp -o cpplib

build:
	g++ -shared -fpic cpplib_interface.cpp -o libCppLibrary.so

c:
	gcc main.c -L. -lCppLibrary -o ctest

clean:
	rm cpplib
	rm ctest
	rm libCppLibrary.so
