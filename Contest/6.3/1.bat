:loop
gen > in.in
A < in.in > out.out
wkr < in.in > std.out
fc out.out std.out
if not errorlevel 1 goto loop
pause