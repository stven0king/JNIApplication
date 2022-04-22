package com.jni.tzx;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.jni.tzx.utils.JNIUitls;

public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(tanzhenxing() +  new JNIUitls().getNumber(3));
        tv.setText(test() + "\n" + new JNIUitls().test());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String tanzhenxing();
    public native String test();

    @Override
    public Intent registerReceiver(BroadcastReceiver receiver, IntentFilter filter) {
        Log.d("tanzhenxing", "111");
        return super.registerReceiver(receiver, filter);
    }

    @Override
    protected void onResume() {
        super.onResume();
        boolean tanzhenxing = Log.isLoggable("tanzhenxing", 1);
        Log.d("tanzhenxing", "111:" + tanzhenxing);

    }
}
