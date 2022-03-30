package com.jni.tzx.utils;

public class JNIUitls {
    static {
        System.loadLibrary("jnilib");
    }

    //测试native被注释，但so不做修改依旧可以运行
//    public static native String getNameString();

    public native int getNumber(int num);
}