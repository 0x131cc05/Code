:loop
gen
1320E < in1.in > out.out
tmp < in1.in > std.out
fc out.out std.out 
if not errorlevel 1 goto loop
pause
