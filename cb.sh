#!/usr/bin/env bash

# this is a basic getting started script for cb build system

# CC environment variable can be defined to use a different compiler
# by default, uses GCC

: "${CC:=gcc}"

# check if cb executable already exists
# if it doesn't, build it

if [ ! -f "./cb" ]; then
    set -x
    "$CC" cb.c -o cb
    { set +x; } 2>/dev/null
fi

# execute cb with arguments

./cb "$@"

