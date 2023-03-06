@echo off
rem START or STOP Services
rem ----------------------------------
rem Check if argument is STOP or START

if not ""%1"" == ""START"" goto stop


"C:\Users\jorge\Documents\Uni\SW\xampp\mysql\bin\mysqld" --defaults-file="C:\Users\jorge\Documents\Uni\SW\xampp\mysql\bin\my.ini" --standalone
if errorlevel 1 goto error
goto finish

:stop
cmd.exe /C start "" /MIN call "C:\Users\jorge\Documents\Uni\SW\xampp\killprocess.bat" "mysqld.exe"

if not exist "C:\Users\jorge\Documents\Uni\SW\xampp\mysql\data\%computername%.pid" goto finish
echo Delete %computername%.pid ...
del "C:\Users\jorge\Documents\Uni\SW\xampp\mysql\data\%computername%.pid"
goto finish


:error
echo MySQL could not be started

:finish
exit
