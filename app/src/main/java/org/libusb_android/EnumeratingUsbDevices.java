package org.libusb_android;

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
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
//import android.hardware.usb.UsbRequest;

import java.util.HashMap;
import java.util.Iterator;

import org.helper.Str;

import org.libusb.LibUSBClassCode;


public class EnumeratingUsbDevices {

    protected Context appContext;
    protected UsbManager usbManager;

    private final String endl = "\n";
    private final String tab = "\t";

    public EnumeratingUsbDevices(Context appContext) {
        this.appContext = appContext;
    }

    public String wenjiunEnumeration(){

        usbManager = (UsbManager) appContext.getSystemService(Context.USB_SERVICE);
        if (usbManager == null){
            throw new RuntimeException("Error: Unable to get UsbManager");
        }

        StringBuilder sb = new StringBuilder();
        HashMap<String, UsbDevice> deviceMap = usbManager.getDeviceList();

        sb.append("\nUSB device enumeration\n");

        sb.append(String.format("Detected %1$d USB devices\n", deviceMap.size() ));

        Iterator<UsbDevice> deviceIterator = deviceMap.values().iterator();
        LibUSBClassCode usbClassCode;
        // process devices
        while (deviceIterator.hasNext()) {
            UsbDevice usbDevice = deviceIterator.next();
            sb.append("\n*****************\n");
            sb.append(String.format("USB Device ID.: %1$d (0x%1$04x)\n", usbDevice.getDeviceId() ));
            sb.append(String.format("Name..........: %1$s\n", usbDevice.getDeviceName() ));
            sb.append(String.format("Vendor Id.....: %1$d (0x%1$04x)\n", usbDevice.getVendorId() ));
            sb.append(String.format("Product Id....: %1$d (0x%1$04x)\n", usbDevice.getProductId() ));

            usbClassCode = LibUSBClassCode.getCode(usbDevice.getDeviceClass());
            sb.append(String.format("Class.........: %1$d - (0x%1$02x - %2$s)\n", usbClassCode.getValue(), usbClassCode.name() ));
            sb.append(String.format("Sub Class.....: %1$d\n", usbDevice.getDeviceSubclass() ));
            sb.append(String.format("Protocol......: %1$d\n", usbDevice.getDeviceProtocol() ));

            // process interfaces for each device
            int interfaceCount = usbDevice.getInterfaceCount();
            UsbInterface usbInterface;
            sb.append(String.format("\nDetected %1$d interfaces\n", interfaceCount));
            for(int i = 0; i < interfaceCount; ++i){
                sb.append("\t*****************\n");
                usbInterface = usbDevice.getInterface(i);
                sb.append(String.format("\tUSB Interface ID..: %1$d\n", usbInterface.getId()));
                sb.append(String.format("\tAlternate Settings: %1$d\n", usbInterface.getAlternateSetting()));

                usbClassCode = LibUSBClassCode.getCode(usbInterface.getInterfaceClass());
                sb.append(String.format("\tClass.............: %1$d - (0x%1$02x - %2$s)\n", usbClassCode.getValue(), usbClassCode.name() ));
                sb.append(String.format("\tSub Class.........: %1$d\n", usbInterface.getInterfaceSubclass() ));
                sb.append(String.format("\tProtoco...........: %1$d\n", usbInterface.getInterfaceProtocol() ));

                // process endpoints for each interface
                int endpointCount = usbInterface.getEndpointCount();
                UsbEndpoint usbEndpoint;
                sb.append(String.format("\n\tDetected %1$d endpoints\n", endpointCount ));
                for(int j = 0; j < endpointCount; ++j){
                    usbEndpoint = usbInterface.getEndpoint(j);
                    sb.append("\t\t*****************\n");
                    sb.append(String.format("\t\tEndpoint No.: %1$d\n", usbEndpoint.getEndpointNumber() ));
                    int direction = usbEndpoint.getDirection();
                    sb.append(String.format("\t\tDirection...: 0x%1$02x (%2$s)\n", direction,
                            ((direction == UsbConstants.USB_DIR_IN) ? "device to host" :
                            ((direction == UsbConstants.USB_DIR_OUT) ? "host to device" : "undefined")) ));
                    sb.append(String.format("\t\tAddress.....: 0x%1$02x (%2$s)\n", usbEndpoint.getAddress(),
                            Str.lpad(Integer.toBinaryString(usbEndpoint.getAddress()), 8, "0") ));
                    sb.append(String.format("\t\tAttributes..: 0x%1$02x (%2$s)\n", usbEndpoint.getAttributes(),
                            Str.lpad(Integer.toBinaryString(usbEndpoint.getAttributes()), 8, "0") ));

                    sb.append(String.format("\t\tMax Packet..: %1$d\n", usbEndpoint.getMaxPacketSize() ));
                    sb.append(String.format("\t\tInterval....: %1$d\n", usbEndpoint.getInterval() ));

                    String text;
                    int type = usbEndpoint.getType();
                    switch(type){
                        case UsbConstants.USB_ENDPOINT_XFER_CONTROL:
                            text = "control";
                            break;
                        case UsbConstants.USB_ENDPOINT_XFER_ISOC:
                            text = "isochronous";
                            break;
                        case UsbConstants.USB_ENDPOINT_XFER_BULK:
                            text = "bulk";
                            break;
                        case UsbConstants.USB_ENDPOINT_XFER_INT:
                            text = "interrupt";
                            break;
                        default:
                            text = "unknown";
                            break;
                    }
                    sb.append(String.format("\t\tType........: %1$d (%2$s)\n", type, text ));

                }
                sb.append(endl);

            }




        }

        sb.append(endl);
        return sb.toString();

    }
}
