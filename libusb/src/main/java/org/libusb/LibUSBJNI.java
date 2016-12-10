/**
 * License Public Domain (CC0) 2016 Julio Tentor (jtentor@gmail.com)
 *
 * To the extent possible under law, Julio Tentor has waived all copyright and related
 * or neighboring rights. This work is published from: Jujuy - Argentina.
 *
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 */

package org.libusb;

/**
 * To generate all glue headers needed by Android JNI - Java Native Interface
 *
 * - Build the project
 * - Open a command console
 * - Change to [project home folder]\libusb\src\main\java folder
 * - Execute "C:\Program Files\Android\Android Studio\jre\bin\javah.exe" -d ../cpp org.libusb.LibUSBJNI
 *
 */
public class LibUSBJNI {
    /**
     * Native Library reference
     */
    static {
        System.loadLibrary("libusb-1-0-21");
    }
    /**
     * Java Native Interface function references
     */
    native String usb_jni_demo(int demoMode);

    /**
     * Show jni integration
     * @return string with demo information
     */
    public String Demo() {

        return usb_jni_demo(1);
    }

}
