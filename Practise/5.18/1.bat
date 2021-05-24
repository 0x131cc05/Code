:loop
gen > in.in
b < in.in > std.out
tb < in.in > out.out
fc std.out out.out
if not errorlevel 1 goto loop
pause