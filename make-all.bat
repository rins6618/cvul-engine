@echo off

echo "Making all assemblies..."

pushd engine
call make.bat
popd
if %ERRORLEVEL% neq 0 (echo Error:%ERRORLEVEL% && exit)

pushd testbed
call make.bat
popd
if %ERRORLEVEL% neq 0 (echo Error:%ERRORLEVEL% && exit)

echo "Both assemblies made without error."