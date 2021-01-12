@echo off
:loop
gen > in.in
A < in.in > out.out
fuck < in.in > fuck.out
fc out.out fuck.out
if not errorlevel 1 goto loop
pause