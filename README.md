# JConsole

A library that provides platform-independent access to lowlevel console functions using native access to Curses on Linux and OS-X, and the Windows API on Windows.

## Usage

Prebuild binaries are available in the lib directory. The platform's corresponding native library must either be placed in the same folder as the .jar or its directory has to be added to the java.library.path environment variable.

## Build

Building the project requires a CMake installation and a Curses library on Unix and OS-X systems. To build the project use the commands:

```
mkdir build
cd build
cmake ..
make
```

## Test

To perform a simple test of the library follow the steps outlined above to build the library and execute the following command afterwards:

```
make jconsole-run
```
