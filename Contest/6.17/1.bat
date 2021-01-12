@echo off
:loop
test1.exe >13.txt
C.exe <13.txt>out1.txt
dak-2.exe <13.txt>out2.txt
fc out1.txt out2.txt
if not errorlevel 1 goto loop
pause
goto loop
