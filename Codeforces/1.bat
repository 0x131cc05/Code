:loop
gen 
1470E < in.in > out.out
fuck < in.in > std.out
fc out.out std.out
if not errorlevel 1 goto loop
pause