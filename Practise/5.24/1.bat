:loop
gen > in.in
std < in.in > std.out
shenxian < in.in > out.out
fc std.out out.out
if not errorlevel 1 goto loop
pause