#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jni_tzx_utils_JNIUitls_getNameString(JNIEnv *env, jobject) {

    // TODO
    return env->NewStringUTF("JNIApplication");

}extern "C"
JNIEXPORT jint JNICALL
Java_com_jni_tzx_utils_JNIUitls_getNumber(JNIEnv *env, jobject instance) {

    return 0;

}