@echo off

:prompt
set /p CHOICE="Enable the remix mod? This will launch the game afterwards (y/n): "

if /i "%CHOICE%"=="y" goto enable
if /i "%CHOICE%"=="n" goto end

echo Please enter y or n.
goto prompt

:enable
ren "bin\d3d9.dll.off" "d3d9.dll"
ren "bin\winmm.dll.off" "winmm.dll"
ren "portal2_dlc3\pak01_dir.vpk.off" "pak01_dir.vpk"

echo Mod has been enabled.
echo Launching Portal 2...

start "" "%~dp0run-p2-rtx.bat"

:end