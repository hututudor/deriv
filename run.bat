@echo off

if not exist build\gui.exe (
  echo no build found!
  pause >nul
) else start build\gui.exe
