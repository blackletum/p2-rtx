@echo off

:prompt
set /p CHOICE="Disable the remix mod and restore Portal 2 settings? This will launch the game once (required) (y/n): "

if /i "%CHOICE%"=="y" goto disable
if /i "%CHOICE%"=="n" goto end

echo Please enter y or n.
goto prompt

:disable
ren "bin\d3d9.dll" "d3d9.dll.off"
ren "bin\winmm.dll" "winmm.dll.off"
ren "portal2_dlc3\pak01_dir.vpk" "pak01_dir.vpk.off"

echo Mod has been disabled.
echo Launching Portal 2...

start "" "portal2.exe" ^
    -insecure -steam ^
    +r_portal_stencil_depth 2 ^
    +r_dopixelvisibility 1 ^
    +mat_fullbright 0 ^
    +mat_softwareskin 0 ^
    +mat_fastnobump 0 ^
    +mat_normalmaps 1 ^
    +cl_tlucfastpath 1 ^
    +cl_modelfastpath 1 ^
    +cl_brushfastpath 1 ^
    +r_dopixelvisibility 1 ^
    +mat_queue_mode 1

:end