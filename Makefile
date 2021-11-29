all:
	g++ src/main.cpp src/**/*.cpp -o build/main -g
	./build/main data/exp.in data/exp.out
