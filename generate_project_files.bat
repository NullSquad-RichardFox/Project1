@echo off

pushd %~dp0\
call Programs\Premake\premake5.exe --file=Project1.lua vs2026
popd
PAUSE