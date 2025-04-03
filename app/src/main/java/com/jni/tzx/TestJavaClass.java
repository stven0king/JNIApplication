package com.jni.tzx;

import android.util.Log;

/**
 * Created by Tanzhenxing
 * Date: 2023/12/5 19:48
 * Description:
 */
public class TestJavaClass {
    private String mString = "Hello JNI, this is normal string !";

    private static int mStaticInt = 0;

    private void myMethod() {
        Log.i("tanzhenxing33:JNI", "this is java myMethod");
    }

    private static void myStaticMethod() {
        Log.d("tanzhenxing33:JNI", "this is Java myStaticMethod");
    }


    //执行这个方法会抛出异常
    private static int exceptionMethod() {
        return 20 / 0;
    }


    public static String getContent(TestJavaClass testJavaClass) {
        return testJavaClass.mString + " === " + mStaticInt;
    }
}
