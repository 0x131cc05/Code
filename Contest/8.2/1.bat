@echo off
:loop
gen > B.in
B < B.in > out.out
fuck < B.in > std.out
fc out.out std.out
if not errorlevel 1 goto loop
pause