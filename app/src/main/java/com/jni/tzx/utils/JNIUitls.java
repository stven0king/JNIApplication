package com.jni.tzx.utils;

public class JNIUitls {
    static {
        System.loadLibrary("jnilib");
    }

    public static native String getNameString();

    public native int getNumber(int num);
}