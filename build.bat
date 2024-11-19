@echo off

:: Check if cmake is available
where premake5 >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: premake5 is not installed or not in PATH.
	pause
    exit /b 1
)

premake5 vs2022

pause