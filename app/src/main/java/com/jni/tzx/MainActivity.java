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
        tv = (TextView) findViewById(R.id.sample_text1);
        tv.setText(test() + "\n" + new JNIUitls().test());
        tv = (TextView) findViewById(R.id.sample_text2);
        int[] ints = new int[2];
        ints[0] = 1;
        ints[1] = 3;
        double[] doubles = sumAndAverage(ints);
        tv.setText(String.format("sum=%s, average=%s", doubles[0], doubles[1]));
        String[] strs = new String[2];
        strs[0] = "git ";
        strs[1] = " hub";
        String[] strings = operateStringArray(strs);
        StringBuffer stringBuffer = new StringBuffer();
        for (String s : strings) {
            stringBuffer.append(s);
        }
        tv = (TextView) findViewById(R.id.sample_text3);
        tv.setText(stringBuffer);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String tanzhenxing();
    public native String test();
    public native double[] sumAndAverage(int[] numbers);
    public native String[] operateStringArray(String[] array);

    @Override
    protected void onResume() {
        super.onResume();
        boolean tanzhenxing = Log.isLoggable("tanzhenxing", 1);
        Log.d("tanzhenxing33", "MainActivity:onResume:" + tanzhenxing);

    }
}
