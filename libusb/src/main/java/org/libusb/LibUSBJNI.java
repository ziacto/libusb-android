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

import android.content.Context;

/**
 * USB Host APIs android.hardware.usb package
 */

//import android.hardware.usb.UsbAccessory;
//import android.hardware.usb.UsbConfiguration;
import android.content.Context;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
//import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
//import android.hardware.usb.UsbRequest;

import java.util.HashMap;
import java.util.Iterator;

/**
 * To generate all glue headers needed by Android JNI - Java Native Interface
 *
 * Open command console
 * Change to [project home folder]\libusb\main folder
 * Execute "C:\Program Files\Android\Android Studio\jre\bin\javah.exe" -d ../cpp org.libusb.LibUSBJNI
 *
 */


public class LibUSBJNI {
    /**
     * Java Native Interface function references
     */
    native String libusb_jni_demo(int fh);

    /**
     * Native Library reference
     */
    static {
        System.loadLibrary("usb-1-0");
    }


    private UsbManager usbManager;

    public String devicesEnumeration(Context appContext) {

        usbManager = (UsbManager) appContext.getSystemService(Context.USB_SERVICE);
        if (usbManager == null) {
            // TODO: Exception class needed
            throw new RuntimeException("Error: Unable to get UsbManager");
        }

        HashMap<String, UsbDevice> deviceMap = usbManager.getDeviceList();
        Iterator<UsbDevice> deviceIterator = deviceMap.values().iterator();

        UsbDevice usbDevice;
        UsbInterface usbInterface;
        LibUSBClassCode usbClassCode;

        while (deviceIterator.hasNext()) {
            usbDevice = deviceIterator.next();
            int interfaceCount = usbDevice.getInterfaceCount();
            for (int i = 0; i < interfaceCount; ++i) {
                usbInterface = usbDevice.getInterface(i);
                usbClassCode = LibUSBClassCode.getCode(usbInterface.getInterfaceClass());


            }

        }

        return "";
    }

}
