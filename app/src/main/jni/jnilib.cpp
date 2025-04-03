#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL   //方法的返回值为String类型
//Java是表示这是Java类中的native方法
//下划线（“_”）是分隔符
//com_jni_tzx_utils 是程序中的包名：com_jni_tzx_utils
//JNIUitls表示这个方法所在的类是JNIUitls类
//getNameString表示这个JNI的方法名是getNameString
Java_com_jni_tzx_utils_JNIUitls_getNameString(
    JNIEnv *env, //JNIEnv是一个指向线程-局部数据的指针,而线程-局部数据中包含指向函数表的指针。
                 // 实现原生方法的函数 将JNIEnv接口指针作为它们的第一个参数。
    jclass type  //非static的方法参数类型是jobject instance,而static的方法参数类型是jclass type
    )
{
    return env->NewStringUTF("JNIApplication");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_jni_tzx_utils_JNIUitls_getNumber(
        JNIEnv *env,
        jobject instance,//非static的方法参数类型是jobject instance,而static的方法参数类型是jclass type
        jint num         //Java中native方法的第一个参数
        )
{
    return 0;

}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jni_tzx_utils_JNIUitls_test(JNIEnv *env, jclass type) {
    return env->NewStringUTF("Java_com_jni_tzx_utils_JNIUitls_test");
}
extern "C"
JNIEXPORT jstring JNICALL
//Java_com_jni_tzx_utils_JNIUitls_test(JNIEnv *env, jclass type) {
test(JNIEnv *env, jclass type) {
    return env->NewStringUTF(":test");
}

extern "C"
JNIEXPORT jint JNICALL
//System.loadLibrary方法会调用载入的.so文件的函数列表中查找JNI_OnLoad函数并执行
JNI_OnLoad(JavaVM* vm, void* reserved) {
    static JNINativeMethod methods[] = {
            {"test", "()Ljava/lang/String;", (void *)test}
    };
    JNIEnv *env = NULL;
    jint result = -1;

    // 获取JNI env变量
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        // 失败返回-1
        return result;
    }

    // 获取native方法所在类
    const char* className = "com/jni/tzx/utils/JNIUitls";
//    const char* className = "com/jni/tzx/MainActivity";
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        return result;
    }

    // 动态注册native方法
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return result;
    }

    // 返回成功
    result = JNI_VERSION_1_6;
    return result;
}
