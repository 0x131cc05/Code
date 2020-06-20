@echo off
:loop
gen.exe > in.txt
wen.exe < in.txt > stdout.txt
fuck.exe < in.txt > myout.txt
fc stdout.txt myout.txt
if not errorlevel 1 goto loop
pause
goto loop
