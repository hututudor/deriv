CLI_SRC = src/main_cli.cpp src/**/*.cpp
GUI_SRC = src/main_gui.cpp src/**/**/*.cpp 
TEST_SRC = test/main.cpp src/**/*.cpp

.PHONY: test development

development:
	mkdir -p build
	g++ $(CLI_SRC) -o build/cli -g -std=c++11 -D DEBUG_LOG
	g++ $(GUI_SRC) -o build/gui -g -std=c++11 -D DEBUG_LOG -lSDL2
	./build/gui data/exp.in

release:
	mkdir -p build
	g++ $(CLI_SRC) -o build/cli -std=c++11 -O2
	g++ $(GUI_SRC) -o build/gui -std=c++11 -O2

test:
	mkdir -p build
	g++ $(TEST_SRC) -o build/test -std=c++11 
	./build/main

valgrind: development
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./build/cli data/exp.in data/exp.out
