.PHONY: test

development:
	mkdir -p build
	g++ src/main.cpp src/**/*.cpp -o build/main -g -std=c++11 -D DEBUG_LOG
	./build/main data/exp.in data/exp.out
	cat data/exp.out

release:
	mkdir -p build
	g++ src/main.cpp src/**/*.cpp -o build/main -std=c++11 -O2

test:
	mkdir -p build
	g++ test/main.cpp src/**/*.cpp -o build/main -std=c++11 
	./build/main
