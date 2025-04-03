#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include "nativelib.h"

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
    int result = getResult();
    std::string hello = std::to_string(result) + " Hello from C++ dynamic\n";
    return env->NewStringUTF(hello.c_str());
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
    const char* char_in = env->GetStringUTFChars(tag, nullptr);
    LOGD("call isLoggable %s %d", char_in, level);
    if (level % 2 == 0) {
        return false;
    } else {
        return true;
    }
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

extern "C" JNIEXPORT jdoubleArray JNICALL
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
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_jni_tzx_MainActivity_operateStringArray(JNIEnv *env, jobject thiz, jobjectArray array) {
    jsize  size = env->GetArrayLength(array);
    for (int i = 0; i < size; ++i) {
        jstring string_in = (jstring)env->GetObjectArrayElement(array, i);
        const char* char_in = env->GetStringUTFChars(string_in, nullptr);
        LOGD("%s", char_in);
    }

    jclass clazz = env->FindClass("java/lang/String");
    jobjectArray  objectArray_out;
    int len_out = getResult();
    objectArray_out = env->NewObjectArray(len_out, clazz, NULL);
    const char* char_out[] = {"hello,", "world~!", " JNI", " is", " fun"};
    jstring temp_string;
    for (int i = 0; i < len_out; ++i) {
        temp_string = env->NewStringUTF(char_out[i]);
        env->SetObjectArrayElement(objectArray_out, i, temp_string);
    }
    return objectArray_out;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_accessJavaFiled(JNIEnv *env, jobject thiz, jobject test_java_class) {
    jclass clazz;
    jfieldID mString_fieldID;
    clazz = env->GetObjectClass(test_java_class);
    if (clazz == NULL) {
        return;
    }
    mString_fieldID = env->GetFieldID(clazz, "mString", "Ljava/lang/String;");
    if (mString_fieldID == NULL) {
        return;
    }

    jstring j_string = (jstring)(env->GetObjectField(test_java_class, mString_fieldID));
    const char* buf = env->GetStringUTFChars(j_string, NULL);
    LOGD("mString=%s", buf);

    const char *buf_out = "Hello Java, I am JNI!";
    jstring tmp = env->NewStringUTF(buf_out);
    env->SetObjectField(test_java_class, mString_fieldID, tmp);

    //jfieldID 不是 JNI 引用类型，不用 DeleteLocalRef
    // jfieldID 是一个指针类型，其内存的分配与回收由 JVM 负责，不需要我们去 free
    //free(mString_fieldID);

    //通知虚拟机 jstring 在 jvm 中对应的内存已经不使用了，可以清除了。
    env->ReleaseStringChars(j_string, reinterpret_cast<const jchar *>(buf));
    env->DeleteLocalRef(j_string);
    env->DeleteLocalRef(clazz);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_accessStaticField(JNIEnv *env, jobject thiz,
                                                jobject test_java_class) {
    jclass clazz;
    jfieldID mStaticIntFiledID;
    clazz = env->GetObjectClass(test_java_class);
    if (clazz == NULL) {
        return;
    }
    mStaticIntFiledID = env->GetStaticFieldID(clazz, "mStaticInt", "I");
    jint mInt = env->GetStaticIntField(clazz, mStaticIntFiledID);
    LOGD("mInt=%d", mInt);
    env->SetStaticIntField(clazz, mStaticIntFiledID, 10086);
    env->DeleteLocalRef(clazz);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_accessJavaMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/jni/tzx/TestJavaClass");
    if (clazz == NULL) {
        return;
    }
    jmethodID java_construct_method_id = env->GetMethodID(clazz, "<init>", "()V");
    if (java_construct_method_id == NULL) {
        return;
    }
    jobject object_test = env->NewObject(clazz, java_construct_method_id);
    if (object_test == NULL) {
        return;
    }
    jmethodID java_method_id = env->GetMethodID(clazz, "myMethod", "()V");
    if (java_method_id == NULL) {
        return;
    }
    env->CallVoidMethod(object_test, java_method_id);

    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(object_test);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_accessStaticMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/jni/tzx/TestJavaClass");
    if (clazz == NULL) {
        return;
    }
    jmethodID static_method_id = env->GetStaticMethodID(clazz, "myStaticMethod", "()V");
    if (static_method_id == NULL) {
        return;
    }
    env->CallStaticVoidMethod(clazz, static_method_id);
    env->DeleteLocalRef(clazz);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_exceptionTest(JNIEnv *env, jobject thiz) {
    //查找的类不存在，返回 NULL；
    jclass clazz = env->FindClass("com/jni/tzx/xxx");
    if (clazz == NULL) {
        return; //return 后，jvm 会向 java 层抛出 ClassNotFoundException
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_exceptionTestMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/jni/tzx/TestJavaClass");
    if (clazz == NULL) {
        return;
    }

    //调用 java 层会抛出异常的方法
    jmethodID static_method_id = env->GetStaticMethodID(clazz, "exceptionMethod", "()I");

    if (NULL == static_method_id) {
        return;
    }

    //直接调用，发生 ArithmeticException 异常，传回 Java 层
    env->CallStaticIntMethod(clazz, static_method_id);
    jthrowable mThrowable;
    if (env->ExceptionCheck()) {
        //获取到异常对象
        mThrowable = env->ExceptionOccurred();
        //这里就可以根据实际情况处理异常了
        //.......
        //打印异常信息堆栈
        env->ExceptionDescribe();
        //清除异常信息
        //如果，异常还需要 Java 层处理，可以不调用 ExceptionClear，让异常传递给 Java 层
        env->ExceptionClear();
        //如果调用了 ExceptionClear 后，异常还需要 Java 层处理，我们可以抛出一个新的异常给 Java 层
        jclass clazz_exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(clazz_exception, "JNI抛出的异常！");
    }

    env->DeleteLocalRef(clazz);
}
//定义用于缓存的全局变量
static jmethodID java_construct_method_id2 = NULL;
static jmethodID java_method_id2 = NULL;
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_initIDs(JNIEnv *env, jclass clazz) {
    jclass clazz2 = env->FindClass("com/jni/tzx/TestJavaClass");

    if (clazz == NULL) {
        return;
    }

    //实现缓存的目的，下次调用不用再获取 methodid 了
    if (java_construct_method_id2 == NULL) {
        LOGD("Java_com_jni_tzx_MainActivity_initIDs:global:java_construct_method_id2 == NULL");
        //构造函数 id
        java_construct_method_id2 = env->GetMethodID(clazz2, "<init>", "()V");
        if (java_construct_method_id2 == NULL) {
            return;
        }
    }

    if (java_method_id2 == NULL) {
        java_method_id2 = env->GetMethodID(clazz2, "myMethod", "()V");
        if (java_method_id2 == NULL) {
            return;
        }
    }

    //调用构造函数，创建一个对象
    jobject object_test = env->NewObject(clazz2, java_construct_method_id2);
    if (object_test == NULL) {
        return;
    }
    //调用 myMethod 方法
    env->CallVoidMethod(object_test, java_method_id2);

    env->DeleteLocalRef(clazz2);
    env->DeleteLocalRef(object_test);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_cacheTest(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/jni/tzx/TestJavaClass");
    if (clazz == NULL) {
        return;
    }

    static jmethodID java_construct_method_id = NULL;
    static jmethodID java_method_id = NULL;

    //实现缓存的目的，下次调用不用再获取 methodid 了
    if (java_construct_method_id == NULL) {
        LOGD("Java_com_jni_tzx_MainActivity_cacheTest:local:java_construct_method_id == NULL");
        //构造函数 id
        java_construct_method_id = env->GetMethodID(clazz, "<init>", "()V");
        if (java_construct_method_id == NULL) {
            return;
        }
    }

    //调用构造函数，创建一个对象
    jobject object_test = env->NewObject(clazz, java_construct_method_id);
    if (object_test == NULL) {
        return;
    }
    //相同的手法，缓存 methodid
    if (java_method_id == NULL) {
        java_method_id = env->GetMethodID(clazz, "myMethod", "()V");
        if (java_method_id == NULL) {
            return;
        }
    }

    //调用 myMethod 方法
    env->CallVoidMethod(object_test, java_method_id);

    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(object_test);
}
static int count = 0;
JavaVM  *gJavaVM = NULL;//全局 JavaVM变量
jobject gJavaObj = NULL;//全局 Jobject变量
jmethodID nativeCallback = NULL;//全局的方法ID

//这里通过标志位来确定 两个线程的工作都完成了再执行 DeleteGlobalRef
//当然也可以通过加锁实现
bool main_finished = false;
bool background_finished = false;

static void *native_thread_exec(void *arg) {
    LOGD("nativeThreadExec");
    LOGD("The pthread is : %ld\n", pthread_self());
    JNIEnv *env;
    gJavaVM->AttachCurrentThread(&env, NULL);
    for (int i = 0; i < 5; ++i) {
        usleep(2);
        env->CallVoidMethod(gJavaObj, nativeCallback, count++);
    }
    background_finished = true;
    if (main_finished && background_finished) {
        LOGD("全局引用在子线程销毁");
        env->DeleteGlobalRef(gJavaObj);
    }
    gJavaVM->DetachCurrentThread();
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jni_tzx_MainActivity_threadTest(JNIEnv *env, jobject thiz) {
    gJavaObj = env->NewGlobalRef(thiz);
    jclass clazz = env->GetObjectClass(thiz);
    nativeCallback = env->GetMethodID(clazz, "javaCallback", "(I)V");
    env->GetJavaVM(&gJavaVM);
    pthread_t id;
    if (pthread_create(&id, NULL, native_thread_exec, NULL) != 0) {
        return;
    }
    for (int i = 0; i < 5; ++i) {
        usleep(20);
        env->CallVoidMethod(gJavaObj, nativeCallback, count++);
    }
    main_finished = true;
    if (main_finished && background_finished && !env->IsSameObject(gJavaObj, NULL)) {
        LOGD("全局引用在主线程销毁");
        env->DeleteLocalRef(gJavaObj);
    }
}