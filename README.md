# JNIApplication
ndk

[Android之NDK开发初体验](http://dandanlove.com/2017/03/24/android-ndk-init/)

- JNIUitls.java

```
public class JNIUitls {
    static {
        System.loadLibrary("jnilib");
    }

    public static native String getNameString();

    public native int getNumber(int num);
}
```

- jnilib.cpp

```
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
```