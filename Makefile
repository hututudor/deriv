all:
	mkdir -p build
	g++ src/main.cpp src/**/*.cpp -o build/main -g -std=c++11
	./build/main data/exp.in data/exp.out
