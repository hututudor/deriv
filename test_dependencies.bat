@echo off

g++ --version >nul 2>&1 && (
    echo found g++
) || (
    echo missing g++!
)

make --version >nul 2>&1 && (
    echo found make
) || (
    echo missing make!
)

pause >nul
