@echo off

g++ --version >nul 2>&1 && (
    echo found g++
) || (
    echo missing g++!
)

pause >nul
