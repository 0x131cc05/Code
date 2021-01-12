@echo off
:loop
rand > cave.in
brute < cave.in > cave.ans
cave < cave.in > cave.out
fc cave.out cave.ans
if not errorlevel 1 goto loop
pause