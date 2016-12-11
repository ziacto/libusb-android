package org.libusb_android;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.view.View;
import android.view.View.OnClickListener;


import org.libusb.LibUSBJNI;

public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView textView = (TextView) findViewById(R.id.sample_text);
        Button buttonGet = (Button)findViewById(R.id.buttonGet);


        buttonGet.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {

                /**
                 * Test Enumeration USB Devices in cpp
                 */
                LibUSBJNI usbJNI = new LibUSBJNI();
                textView.setText("cpp Enumeration:\n" + usbJNI.Demo() );


            }
        });

        /**
         * Test Enumeration USB Devices in java
         */
//        EnumeratingUsbDevices usbDevices = new EnumeratingUsbDevices(this);
//        textView.setText("Wenjiun Enumeration:\n" + usbDevices.wenjiunEnumeration());

        /**
         * Test native method
         */
//      textView.setText( stringFromJNI() );


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
