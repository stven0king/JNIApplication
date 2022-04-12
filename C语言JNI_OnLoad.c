#include <stdio.h>
#include <stdlib.h>

#include <jni.h> //jni的主要头文件

static void JNICALL func2 //函数名字可以随便取，不过参数一定要和javah生成的函数的参数一致，包括返回值
    (JNIEnv *env, jobject jobj)
{
  printf("--- func2 called in version 2\n");
}

static const JNINativeMethod gMethods[] = {
    //定义批量注册的数组，是注册的关键部分
    {"func2", "()V", (void *)func2} // func2是在java中声明的native函数名，"()V"是函数的签名，可以通过javah获取。
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) //这是JNI_OnLoad的声明，必须按照这样的方式声明
{
  JNIEnv *env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
  jint result = -1;

  if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
    return -1;

  jclass clazz;
  static const char *const kClassName = "mj/jnitest/MyObject";

  clazz = (*env)->FindClass(env, kClassName); //这里可以找到要注册的类，前提是这个类已经加载到java虚拟机中。 这里说明，动态库和有native方法的类之间，没有任何对应关系。

  if (clazz == NULL)
  {
    printf("cannot get class:%s\n", kClassName);
    return -1;
  }

  if ((*env)->RegisterNatives(env, clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK) //这里就是关键了，把本地函数和一个java类方法关联起来。不管之前是否关联过，一律把之前的替换掉！
  {
    printf("register native method failed!\n");
    return -1;
  }

  return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}