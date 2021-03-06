CLI_SRC = src/main_cli.cpp src/**/*.cpp
GUI_SRC = src/main_gui.cpp src/**/**/*.cpp src/**/*.cpp
TEST_SRC = test/main.cpp src/**/*.cpp

.PHONY: test development

development:
	mkdir -p build
	g++ $(CLI_SRC) -o build/cli -g -std=c++11
	g++ $(GUI_SRC) -o build/gui -g -std=c++11 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -I/opt/homebrew/include -L/opt/homebrew/lib
	./build/gui data/exp.in

cmd:
	mkdir -p build
	g++ $(CLI_SRC) -o build/cli -g -std=c++11 -D DEBUG_LOG
	./build/cli data/exp.in data/exp.out

release:
	mkdir -p build
	g++ $(CLI_SRC) -o build/cli -std=c++11 -O2
	g++ $(GUI_SRC) -o build/gui -std=c++11 -O2 -lSDL2main -lSDL2 -lSDL2_ttf

test:
	mkdir -p build
	g++ $(TEST_SRC) -o build/test -std=c++11 
	./build/test

valgrind: development
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./build/cli data/exp.in data/exp.out
