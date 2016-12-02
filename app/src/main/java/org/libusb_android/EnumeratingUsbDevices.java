package org.libusb_android;

/**
 * Created by jtentor on 26/11/2016.
 */

import android.app.Activity;
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
//import android.hardware.usb.UsbEndpoint;
//import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
//import android.hardware.usb.UsbRequest;

import java.util.HashMap;
import java.util.Iterator;


public class EnumeratingUsbDevices {

    protected Context appContext;
    protected UsbManager usbManager;

    private final String endl = "\n";

    public EnumeratingUsbDevices(Context appContext){
        this.appContext = appContext;
    }

    public String Work(){

        usbManager = (UsbManager) appContext.getSystemService(Context.USB_SERVICE);
        if (usbManager == null){
            return "ERROR : No se puede obtener UsbManager";
        }

        StringBuilder stringBuilder = new StringBuilder();
        HashMap<String, UsbDevice> deviceMap = usbManager.getDeviceList();
        stringBuilder.append("\nDetectados " + deviceMap.size() + " dispositivos USB\n");
        Iterator<UsbDevice> deviceIterator = deviceMap.values().iterator();
        while (deviceIterator.hasNext()) {
            UsbDevice usbDevice = deviceIterator.next();
            stringBuilder.append(endl);
            stringBuilder.append("USB Device ID: " + usbDevice.getDeviceId() + endl);
            stringBuilder.append("Nombre: " + usbDevice.getDeviceName() + endl);
            stringBuilder.append(String.format("Vendedor Id: %1$d (0x%1$4x)", usbDevice.getVendorId()) + endl);
            stringBuilder.append(String.format("Product Id: %1$d (0x%1$4x)", usbDevice.getProductId()) + endl);

            stringBuilder.append("Clase: " + usbDevice.getDeviceClass() + endl);
            stringBuilder.append("Sub Clase: " + usbDevice.getDeviceSubclass() + endl);
            stringBuilder.append("Protocolo: " + usbDevice.getDeviceProtocol() + endl);

            // procesar las interfaces
            // procesar los endpoint por cada interface

        }

        stringBuilder.append(endl);
        return stringBuilder.toString();

    }


}
