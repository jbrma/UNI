@echo off
rem START or STOP Services
rem ----------------------------------
rem Check if argument is STOP or START

if not ""%1"" == ""START"" goto stop

if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\hypersonic\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\server\hsql-sample-database\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\ingres\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\ingres\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\mysql\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\mysql\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\postgresql\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\postgresql\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\openoffice\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\openoffice\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache-tomcat\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache-tomcat\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\resin\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\resin\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\jetty\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\jetty\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\subversion\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\subversion\scripts\ctl.bat START)
rem RUBY_APPLICATION_START
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\lucene\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\lucene\scripts\ctl.bat START)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\third_application\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\third_application\scripts\ctl.bat START)
goto end

:stop
echo "Stopping services ..."
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\third_application\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\third_application\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\lucene\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\lucene\scripts\ctl.bat STOP)
rem RUBY_APPLICATION_STOP
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\subversion\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\subversion\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\jetty\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\jetty\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\hypersonic\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\server\hsql-sample-database\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\resin\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\resin\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache-tomcat\scripts\ctl.bat (start /MIN /B /WAIT C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache-tomcat\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\openoffice\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\openoffice\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\apache\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\ingres\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\ingres\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\mysql\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\mysql\scripts\ctl.bat STOP)
if exist C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\postgresql\scripts\ctl.bat (start /MIN /B C:\Users\jorge\Documents\Uni - 3ro\SW\xamppp\postgresql\scripts\ctl.bat STOP)

:end

