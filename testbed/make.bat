
:: "make" on a bat file i guess

:: lets me use !! syntax which is fun
@echo off
setlocal EnableDelayedExpansion

:: list every C file
set cFiles=
for /r %%f in (*.c) do (
    set cFiles=!cFiles! %%f
)

set assembly=testbed
set compilerFlags=-g
set includeFlags=-Isrc -I../engine/src
set linkerFlags=-L../bin -lengine.lib
set defines=-D_DEBUG -DKIMPORT

echo "Making %assembly%..."
clang %cFiles% %compilerFlags% -o ../bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%