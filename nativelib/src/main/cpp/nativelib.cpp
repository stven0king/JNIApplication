#include <jni.h>
#include <string>
#include "nativelib.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_nativelib_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ native lib";
    return env->NewStringUTF(hello.c_str());
}

int getResult() {
    return 5;
}