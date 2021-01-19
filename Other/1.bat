:loop
gen > in.in
Luckydays< in.in > out.out
tmp < in.in > std.out
fc out.out std.out 
if not errorlevel 1 goto loop
pause
