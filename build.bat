@echo off

if not exist build mkdir build

echo compiling cli...
g++ src/main_cli.cpp src/ast/ast.cpp src/deriv/derivaLG.cpp src/deriv/derivaX.cpp src/ast/simplify.cpp src/deriv/derivaLN.cpp src/deriv/global.cpp src/deriv/derivaArccos.cpp src/deriv/derivaMultiplication.cpp src/utils/ast_node_array.cpp src/deriv/derivaArccotan.cpp src/deriv/derivaNumber.cpp src/utils/io.cpp src/deriv/derivaArcsin.cpp src/deriv/derivaPow.cpp src/utils/string.cpp src/deriv/derivaArctan.cpp src/deriv/derivaSin.cpp src/utils/token_array.cpp src/deriv/derivaCos.cpp src/deriv/derivaSqrt.cpp src/utils/utils.cpp src/deriv/derivaCotan.cpp src/deriv/derivaSumORDiff.cpp src/deriv/derivaDIV.cpp src/deriv/derivaTan.cpp -o build/cli -g -std=c++11

echo compiling gui...
g++ src/main_gui.cpp src/gui/arrays/box_array.cpp src/gui/components/box.cpp src/gui/scenes/about_scene.cpp src/gui/arrays/button_array.cpp src/gui/components/button.cpp src/gui/scenes/ast_scene.cpp src/gui/arrays/circle_array.cpp src/gui/components/circle.cpp src/gui/scenes/deriv_ast_scene.cpp src/gui/arrays/input_array.cpp src/gui/components/input.cpp src/gui/scenes/input_scene.cpp src/gui/arrays/line_array.cpp src/gui/components/line.cpp src/gui/scenes/sidebar.cpp src/gui/arrays/node_array.cpp src/gui/components/node.cpp src/gui/utils/events.cpp src/gui/arrays/text_array.cpp src/gui/components/text.cpp src/gui/utils/scene.cpp src/gui/ast/ast_gui_utils.cpp src/gui/i18n/i18n.cpp src/gui/ast/ast_scene_utils.cpp src/gui/i18n/translations.cpp src/ast/ast.cpp src/deriv/derivaLG.cpp src/deriv/derivaX.cpp src/ast/simplify.cpp src/deriv/derivaLN.cpp src/deriv/global.cpp src/deriv/derivaArccos.cpp src/deriv/derivaMultiplication.cpp src/utils/ast_node_array.cpp src/deriv/derivaArccotan.cpp src/deriv/derivaNumber.cpp src/utils/io.cpp src/deriv/derivaArcsin.cpp src/deriv/derivaPow.cpp src/utils/string.cpp src/deriv/derivaArctan.cpp src/deriv/derivaSin.cpp src/utils/token_array.cpp src/deriv/derivaCos.cpp src/deriv/derivaSqrt.cpp src/utils/utils.cpp src/deriv/derivaCotan.cpp src/deriv/derivaSumORDiff.cpp src/deriv/derivaDIV.cpp src/deriv/derivaTan.cpp -o build/gui -g -std=c++11 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -Isdl/include -Lsdl/libs

echo copying sdl...
xcopy sdl\dll build /E /Y /s >nul

echo done

pause >nul