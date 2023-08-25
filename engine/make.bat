
:: "make" on a bat file i guess

:: lets me use !! syntax which is fun
@echo off
setlocal EnableDelayedExpansion

:: list every C file
set cFiles=
for /R %%f in (*.c) do (
    set cFiles=!cFiles! %%f 
)

echo "Files:" %cFiles%

set assembly=engine
set compilerFlags=-g -shared -Wvarargs -Wall -Werror
set includeFlags=-Isrc -I%VULKAN_SDK%/Include
set linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
set defines=-D_DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS

echo "Making %assembly%..."
clang %cFiles% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%