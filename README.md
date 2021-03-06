![](logo.png)
# EZ Tabletop Library

##### Jump To
 * [FAQ](#faq)
 * [Requirements](#requirements)
 * [Depencies](#dependencies)
 * [Compiling](#compiling)
 * [Using](#using)
 * [License](#license)

## FAQ
#### What is LIBEZTP?
LIBEZTP is a C++ library aimed at create an easy to use library for tabletop game adaptations made in C++.
It has the necessary features to make and manage characters, items, and races in an easy format.
This is mostly because I plan on making some DM tools and one universal library would be pretty slick.

#### Where did the code for LIBEZTP come from?
I tried to make a Server-Client D&D application in mostly headers.
I failed miserably and rebranded it as a D&D framework, but a lot of the code was actually decent.
I'm using this to fix the mistakes I made and make it an actual usable library.

However, a lot of the code that is soon to come will be all fresh!

## Requirements
 * C++17 capable compiler (gcc, clang, msvc)
 * CMake 3.14 or above

## Dependencies
The dependencies are not required to install.
They will be automatically pulled using `FetchContent`, which does require an internet connection to pull.

 * [Nlohmann_json](https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent)
 * [Catch2](https://github.com/catchorg/Catch2)

## Compiling
 1. Clone the git repo
 2. In the cloned repo root directory, type
 
    ```bash
    cmake -E make_directory build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    cmake --install .
    ```
    
    This will create a new directory called `build` that will hold all your build files.
    It will them use cmake to compile the files and create the library file.
    With this done, it will install the library files and headers into their respective spots.
    
 3. If you wish to verify that the files worked, in `build` you may run
    
    ```bash
    ctest --verbose -C Release
    ```
    
    This will very plainly tell you which tests succeeded and failed.
    If any failed, please make an issue request on the GitHub.

## Using
This project provides two ways to easily use this library.
These are to use `find_package` or `FetchContent`.

### `find_package()`
To use `find_package`, all you need to do is to install as described in [compiling](#compiling)!
Then, simply add the following line to your `CMakeLists.txt` and it'll be added to your project without a hitch.

```cmake
find_package(LibEZTP 1.2.1 REQUIRED)

#All the fun stuff with your executable

target_link_libraries(YourExecutable PRIVATE LibEZTP::LibEZTP)
```

### `FetchContent`
Another, possibly easier, way to add LibEZTP to your project is to use `FetchContent`.
This eliminates the need to install the project, and can be done on the fly.

```cmake
include(FetchContent)
FetchContent_Declare(
        eztp
        GIT_REPOSITORY https://github.com/Macr0Nerd/libeztp.git
        GIT_TAG v1.2.1
)

FetchContent_MakeAvailable(eztp)

#All the fun stuff with your executable

target_link_libraries(YourExecutable PRIVATE LibEZTP::LibEZTP)
```

## License
Copyright (C) 2021  [Gabriele Alessandro Ron](https://macr0nerd.github.io)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

***

This class contains the JSON Parser from Niels Lohmann which is licensed under the [MIT License](https://opensource.org/licenses/MIT). Copyright © 2013-2019 [Niels Lohmann](http://nlohmann.me/)

This class contains the Catch2 Testing Library from Catch Org which is licensed under the [Boost License](https://opensource.org/licenses/BSL-1.0). Copyright © 2012-2020 [Catch Org](https://github.com/catchorg)
