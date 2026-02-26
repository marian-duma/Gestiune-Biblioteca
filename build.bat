@echo off
REM Add mingw64/bin to the PATH for this script only
set PATH=%~dp0mingw64\bin;%PATH%

REM Call mingw32-make with any arguments passed to the script
mingw32-make %*

REM Pause if run by double-click (optional)
pause