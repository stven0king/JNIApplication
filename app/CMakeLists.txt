# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)
#设置生成的so动态库最后输出的路径
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

project("native-lib")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

get_filename_component(NATIVE_SO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/main/libs/${ANDROID_ABI}/libnative-so.so" ABSOLUTE)
#依赖的add库
add_library(native-so SHARED IMPORTED)
set_target_properties(native-so PROPERTIES IMPORTED_LOCATION ${NATIVE_SO_PATH})
message(WARNING "tanzhenxing native so path is:" ${NATIVE_SO_PATH})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
#导入系统库
find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
#添加库
add_library( # Sets the name of the library.
        ${CMAKE_PROJECT_NAME}
        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/jni/native-lib.cpp
        )
#添加库
add_library(jnilib SHARED src/main/jni/jnilib.cpp)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#set(
#        third-party-libs
#        native-so
#)
#链接目标库
target_link_libraries( # Specifies the target library.
                        ${CMAKE_PROJECT_NAME}
                       # Links the target library to the log library
                       # included in the NDK.
                       #add库需要链接
                        native-so
                        ${log-lib} )
#链接目标库
target_link_libraries(jnilib ${log-lib})
#优化包体积
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os -Wall -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -Wall -s")