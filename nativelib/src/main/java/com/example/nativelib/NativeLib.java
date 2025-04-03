package com.example.nativelib;

public class NativeLib {

    // Used to load the 'nativelib' library on application startup.
    static {
        System.loadLibrary("native-so");
    }

    /**
     * A native method that is implemented by the 'nativelib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}