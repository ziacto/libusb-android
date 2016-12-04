package org.libusb_android;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;



public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        /**
         * Test Enumeration USB Devices
         */
        EnumeratingUsbDevices usbDevices = new EnumeratingUsbDevices(this);

        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI() + "\n" +
                "Wenjiun Enumeration:\n" +
                usbDevices.wenjiunEnumeration());


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
