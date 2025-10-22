cb - C Build System
===================
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Header only library for writing a build system in C.

## Table of Contents
- [Usage](#usage)
    - [POSIX](#usage-posix)
    - [Windows](#usage-windows)
- [Limitations](#limitations)
    - [Windows](#limitations-windows)
    - [MacOS](#limitations-macos)
- [Todo](./TODO.md#TODO)
- [Credits](#credits)

## Usage

### Usage - POSIX

- copy `cb.h` and `cb.sh` into your project's root directory.
- create a source file in the root directory, usually `cb.c`
- write your build system.
```c
#include "cb.h"

int main( int argc, char** argv ) {
    // cb.h can be used as a build system but it could also be
    // included in your project's source code.

    // for usage in a build system, make sure to initialize
    // the auto-rebuilding step by calling the following macro function
    CB_BUILD_INIT();

    return 0;
}

// include again with CB_IMPL defined ONCE to define implementation.
#define CB_IMPL
#include "cb.h"
```
- run `cb.sh` to automatically compile build system and run it.
    - arguments are passed down to build system.
    - define `CC` environment variable to use a different compiler, like so:
```bash
CC=clang ./cb.sh
```

### Usage - Windows

- copy `cb.h` and `cb.bat` into your project's root directory.
    - currently, MINGW gcc is required! MSVC is not yet supported!
- create a source file in the root directory, usually `cb.c`
- write your build system, see [POSIX](#usage-posix) for an example.
- run `cb.bat` to automatically compile build system and run it.
    - arguments are passed down to build system.
    - define `CC` environment variable to use a different compiler, like so:
```batch
CC=clang .\cb.bat
```

## Limitations

### Limitations - Windows

Windows currently requires MINGW GCC or MINGW clang.

This can be obtained by installing [MSYS64](https://www.msys2.org/).

### Limitations - MacOS

There is currently no tested support for MacOS but
it should work as the library only requires POSIX standard functions.

## Credits

- [nob.h](https://github.com/tsoding/nob.h) for inspiration.
- [cbuild.h](https://github.com/smushy64/cbuild) for my past attempt to create a C build system.

