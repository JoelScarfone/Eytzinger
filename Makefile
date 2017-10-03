main: main.cpp eytzinger.hpp
	g++ -o main main.cpp eytzinger.hpp

test: test.cpp eytzinger.hpp
	g++ -o test test.cpp eytzinger.hpp