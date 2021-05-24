:loop
ta > in.in
fa < in.in > std.out
A < in.in > out.out
fc out.out std.out
if not errorlevel 1 goto loop
pause