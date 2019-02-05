# NostraBase
A library that provides platform detection, versioning and other basic utilities.

GitHub: https://github.com/NostraTeam/NostraBase

To clone the repository to your local machine, use the command
```
git clone https://github.com/NostraTeam/NostraBase.git
```
Alternatively, it is possible to download the repository as a ZIP archive from GitHub using the link above.

## Requirements
### Usage Requirements
<!--The usage requirements-->

### Build Requirements
<!--The build requirements-->

To also build the documentation of the project, Doxygen (http://www.doxygen.nl/) is required.

## Build and install from source
<!--The build process may needs some alteration, but optimally, it will stay the same-->
First of all, the following steps assume that the current working directory of the shell is the root directory of the 
project (the one that the file __CMakeLists.txt__ is in). It is also assumed that the command __cmake__ is in the PATH
variable.

The single steps in the build and installation process are:
1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build . --target install```

These commands will build and install the project. They work with SH, BASH, cmd.exe and the powershell. If the project
should not be installed, the fourth command needs to be changed to `cmake --build .`.

It is also possible to pass various options to the third command. These have the syntax
```-D<variable name>=<value>```
The following list describes some of the most commonly used variables.

- CMAKE_INSTALL_PREFIX: The value is the path to the directory that the library should later be installed in. The
  default value varies from system to system.
- BUILD_TESTING: The value is either ON or OFF. It determines weather the tests should be build or not. The default 
  value is ON.
- NOSTRA_BUILD_EXAMPLES: The value is either ON or OFF. It determines weather the examples should be build or not. The 
  default value is ON.
- NBA_BUILD_DOC: The value is either ON or OFF. It determines weather the documentation will be build 
  or not. The default value is ON.

## Installation from installer
<!--This needs to be altered as soon as an installer is provided.-->
Currently, no installer is provided.

## Changelog
### Version 1.0.0.0
#### Additions
* None
#### Removals
* None
#### Deprecations
* None
#### Improvements
* None
#### Fixes
* None
#### Known Issues
* None
