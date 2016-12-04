# Sets the minimum version of CMake required to build

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as STATIC or SHARED
# Provides the relative paths to its source code.

add_library( # Sets the name of the library.
             helper

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.

           )

# Provides a relative path to header file(s)

include_directories( # Specifies a path to header file(s).
                   )

# Searches for a specified prebuilt library, stores the path as a variable

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log
            )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       helper

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                     )
