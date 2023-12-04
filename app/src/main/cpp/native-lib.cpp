#include <jni.h>
#include <string>
#include <android/log.h>
#define TAG "tanzhenxing22-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

//作用：避免编绎器按照C++的方式去编绎C函数
extern "C"
//用来表示该函数是否可导出（即：方法的可见性）
JNIEXPORT jstring
//用来表示函数的调用规范（如：__stdcall）
JNICALL
//Java_com_jni_tzx_MainActivity_stringFromJNI(
stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
//    std::string hello = "Hello from C++ dynamic\n";
//    return env->NewStringUTF(hello.c_str());
    return env->NewStringUTF("Hello from C++ dynamic\n");
}


extern "C"
JNIEXPORT jstring JNICALL
//Java_com_jni_tzx_MainActivity_test(JNIEnv *env, jobject thiz) {
test(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("Java_com_jni_tzx_MainActivity_test");
}


extern "C"
JNIEXPORT jboolean JNICALL
isLoggable(JNIEnv *env, jclass clazz, jstring tag, jint level) {
    LOGD("call isLoggable");
    return false;
}

extern "C"
JNIEXPORT jint JNICALL
//System.loadLibrary方法会调用载入的.so文件的函数列表中查找JNI_OnLoad函数并执行
JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnLoad");
    static JNINativeMethod methods[] = {
            {"tanzhenxing", "()Ljava/lang/String;", (void *)stringFromJNI},
            {"test", "()Ljava/lang/String;", (void *)test}
    };
    static JNINativeMethod methodsLog[] = {
            {"isLoggable", "(Ljava/lang/String;I)Z", (void *)isLoggable}
    };
    JNIEnv *env = NULL;
    jint result = -1;

    // 获取JNI env变量
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        // 失败返回-1
        return result;
    }

    // 获取native方法所在类
    const char* className = "com/jni/tzx/MainActivity";
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        return result;
    }

    const char* classNameLog = "android/util/Log";
    jclass clazzLog = env->FindClass(classNameLog);
    if (clazzLog == NULL) {
        return result;
    }

    // 动态注册native方法
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return result;
    }
    if (env->RegisterNatives(clazzLog, methodsLog, sizeof(methodsLog) / sizeof(methodsLog[0])) < 0) {
        return result;
    }
    // 返回成功
    result = JNI_VERSION_1_6;
    return result;
}

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_jni_tzx_MainActivity_sumAndAverage(JNIEnv *env, jobject thiz, jintArray numbers) {
    jboolean isCopy;
    jint * inArray = env->GetIntArrayElements(numbers, &isCopy);
    if (JNI_TRUE == isCopy) {
        LOGD("C 层的数组是 java 层数组的一份拷贝");
    } else {
        LOGD("C 层的数组指向 java 层的数组");
    }
    if (nullptr == inArray) return nullptr;
    jsize length = env->GetArrayLength(numbers);
    jint sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += inArray[i];
    }
    jdouble average = (jdouble)sum / length;
    env->ReleaseIntArrayElements(numbers, inArray, 0);
    jdouble outArray[] = {(jdouble)sum, average};
    jdoubleArray  outJNIArray = env->NewDoubleArray(2);
    if (NULL == outJNIArray) return NULL;
    env->SetDoubleArrayRegion(outJNIArray, 0, 2, outArray);
    return outJNIArray;
}