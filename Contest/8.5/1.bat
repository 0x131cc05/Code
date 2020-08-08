@echo off
:loop
gen > in.in
B < in.in > out.out
game < in.in > zjk.out
fc out.out zjk.out
if not errorlevel 1 goto loop
pause