:loop
gen > in.in
fuck < in.in > std.out
InverseRMQ < in.in > out.out
fc std.out out.out
if not errorlevel 1 goto loop
pause