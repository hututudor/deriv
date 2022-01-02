CLI_SRC = src/main_cli.cpp src/**/*.cpp
GUI_SRC = src/main_gui.cpp src/**/**/*.cpp src/**/*.cpp
TEST_SRC = test/main.cpp src/**/*.cpp

WIN_CLI_SRC = src/main_cli.cpp src/ast/ast.cpp src/deriv/derivaLG.cpp src/deriv/derivaX.cpp src/ast/simplify.cpp src/deriv/derivaLN.cpp src/deriv/global.cpp src/deriv/derivaArccos.cpp src/deriv/derivaMultiplication.cpp src/utils/ast_node_array.cpp src/deriv/derivaArccotan.cpp src/deriv/derivaNumber.cpp src/utils/io.cpp src/deriv/derivaArcsin.cpp src/deriv/derivaPow.cpp src/utils/string.cpp src/deriv/derivaArctan.cpp src/deriv/derivaSin.cpp src/utils/token_array.cpp src/deriv/derivaCos.cpp src/deriv/derivaSqrt.cpp src/utils/utils.cpp src/deriv/derivaCotan.cpp src/deriv/derivaSumORDiff.cpp src/deriv/derivaDIV.cpp src/deriv/derivaTan.cpp
WIN_GUI_SRC = src/main_gui.cpp src/gui/arrays/box_array.cpp src/gui/components/box.cpp src/gui/scenes/about_scene.cpp src/gui/arrays/button_array.cpp src/gui/components/button.cpp src/gui/scenes/ast_scene.cpp src/gui/arrays/circle_array.cpp src/gui/components/circle.cpp src/gui/scenes/deriv_ast_scene.cpp src/gui/arrays/input_array.cpp src/gui/components/input.cpp src/gui/scenes/input_scene.cpp src/gui/arrays/line_array.cpp src/gui/components/line.cpp src/gui/scenes/sidebar.cpp src/gui/arrays/node_array.cpp src/gui/components/node.cpp src/gui/utils/events.cpp src/gui/arrays/text_array.cpp src/gui/components/text.cpp src/gui/utils/scene.cpp src/gui/ast/ast_gui_utils.cpp src/gui/i18n/i18n.cpp src/gui/ast/ast_scene_utils.cpp src/gui/i18n/translations.cpp src/ast/ast.cpp src/deriv/derivaLG.cpp src/deriv/derivaX.cpp src/ast/simplify.cpp src/deriv/derivaLN.cpp src/deriv/global.cpp src/deriv/derivaArccos.cpp src/deriv/derivaMultiplication.cpp src/utils/ast_node_array.cpp src/deriv/derivaArccotan.cpp src/deriv/derivaNumber.cpp src/utils/io.cpp src/deriv/derivaArcsin.cpp src/deriv/derivaPow.cpp src/utils/string.cpp src/deriv/derivaArctan.cpp src/deriv/derivaSin.cpp src/utils/token_array.cpp src/deriv/derivaCos.cpp src/deriv/derivaSqrt.cpp src/utils/utils.cpp src/deriv/derivaCotan.cpp src/deriv/derivaSumORDiff.cpp src/deriv/derivaDIV.cpp src/deriv/derivaTan.cpp
WIN_TEST_SRC = test/main.cpp src/ast/ast.cpp src/deriv/derivaLG.cpp src/deriv/derivaX.cpp src/ast/simplify.cpp src/deriv/derivaLN.cpp src/deriv/global.cpp src/deriv/derivaArccos.cpp src/deriv/derivaMultiplication.cpp src/utils/ast_node_array.cpp src/deriv/derivaArccotan.cpp src/deriv/derivaNumber.cpp src/utils/io.cpp src/deriv/derivaArcsin.cpp src/deriv/derivaPow.cpp src/utils/string.cpp src/deriv/derivaArctan.cpp src/deriv/derivaSin.cpp src/utils/token_array.cpp src/deriv/derivaCos.cpp src/deriv/derivaSqrt.cpp src/utils/utils.cpp src/deriv/derivaCotan.cpp src/deriv/derivaSumORDiff.cpp src/deriv/derivaDIV.cpp src/deriv/derivaTan.cpp

.PHONY: test development

development:
	mkdir -p build
	g++ $(CLI_SRC) -o build/cli -g -std=c++11
	g++ $(GUI_SRC) -o build/gui -g -std=c++11 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -I/opt/homebrew/include -L/opt/homebrew/lib
	./build/gui data/exp.in

win:
	g++ $(WIN_CLI_SRC) -o build/cli -g -std=c++11
	g++ $(WIN_GUI_SRC) -o build/gui -g -std=c++11 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -Isdl/include -Lsdl/libs
	xcopy sdl\dll build /E

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

test_win:
	g++ $(WIN_TEST_SRC) -o build/test -std=c++11 
	./build/test

valgrind: development
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./build/cli data/exp.in data/exp.out
