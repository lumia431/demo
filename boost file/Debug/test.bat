@echo off 
:loop
timeout /T 1 /NOBREAK
tasklist /nh | find /i "Project1.exe"
if ERRORLEVEL 1 (Project1.exe) else (echo "exist")
goto loop