main: main.cpp eytzinger.hpp
	g++ -o main main.cpp eytzinger.hpp -std=gnu++11

test: test.cpp eytzinger.hpp
	g++ -o test test.cpp eytzinger.hpp

clean:
	rm main test