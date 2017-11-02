main: main.cpp eytzinger.hpp
	g++ -o main main.cpp eytzinger.hpp -std=gnu++11

test: test.cpp eytzinger.hpp
	g++ -o test test.cpp eytzinger.hpp -std=gnu++11

benchmark: benchmark.cpp eytzinger.hpp
	g++ -o benchmark benchmark.cpp eytzinger.hpp -std=gnu++11

clean:
	rm -f main test benchmark