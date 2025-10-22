@echo off

REM this is a basic getting started script for cb build system

REM CC environment variable can be defined to use a different compiler
REM by default, uses MINGW GCC

if "%CC%"=="" set "CC=gcc"

REM check if cb executable already exists
REM if it doesn't, build it

if not exist ./cb.exe (
    echo on

    %CC% cb.c -o cb.exe

    echo off
)

REM execute cb with arguments

.\cb.exe %*

