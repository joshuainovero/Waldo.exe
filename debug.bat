@echo off
title Debug
setlocal enabledelayedexpansion
echo Build started at: %cd% && echo.
echo Creating object files... && echo.
mingw32-make DEBUG
IF %ERRORLEVEL% NEQ 0 ( 
    if exist *.o (
        mingw32-make clean
    )
    echo Compilation error. && pause
    exit 0
) else (
echo. && echo The build was succesfully executed.
echo Cleaning files...
mingw32-make clean
if exist *.o (
    echo Failed to clean the files...
) else ( 
    echo Cleaned .o files.
)

set /p ans=The build was successful. Do you want to run? [y/n]:
if !ans! == y (
    echo Starting app...
    start Build/release/WaldoDebug.exe
) else (
    exit 0
)

)
pause