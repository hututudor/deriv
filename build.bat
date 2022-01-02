@echo off

if not exist build mkdir build
make win

echo done

pause >nul