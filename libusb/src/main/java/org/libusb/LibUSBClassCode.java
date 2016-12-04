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
 * From http://www.usb.org/developers/defined_class
 * enums ids from libusb.h
 */
public enum LibUSBClassCode {
    LIBUSB_CLASS_PER_INTERFACE (0x00),
    /** Audio class */
    LIBUSB_CLASS_AUDIO (0x01),
    /** Communications class */
    LIBUSB_CLASS_COMM (0x02),
    /** Human Interface Device class */
    LIBUSB_CLASS_HID (0x03),

    /** Physical */
    LIBUSB_CLASS_PHYSICAL (0x05),
    /** Image class */
//    LIBUSB_CLASS_PTP (0x06), /* legacy name from libusb-0.1 usb.h */
    LIBUSB_CLASS_IMAGE (0x06),
    /** Printer class */
    LIBUSB_CLASS_PRINTER (0x07),
    /** Mass storage class */
    LIBUSB_CLASS_MASS_STORAGE (0x08),
    /** Hub class */
    LIBUSB_CLASS_HUB (0x09),
    /** Data class */
    LIBUSB_CLASS_DATA (0x0a),
    /** Smart Card */
    LIBUSB_CLASS_SMART_CARD (0x0b),

    /** Content Security */
    LIBUSB_CLASS_CONTENT_SECURITY (0x0d),
    /** Video */
    LIBUSB_CLASS_VIDEO (0x0e),
    /** Personal Healthcare */
    LIBUSB_CLASS_PERSONAL_HEALTHCARE (0x0f),

    /** Audio/Video Devices class (standard only) */
    LIBUSB_AUDIO_VIDEO_DEVICES (0x10),
    /** Billboard Device class (standard only) */
    LIBUSB_BILLBOARD_DEVICE (0x11),
    /** USB Type-C Bridge Device class (standard only) */
    LIBUSB_USB_TYPE_C_BRIDGE_DEVICE (0x12),

    /** Diagnostic Device */
    LIBUSB_CLASS_DIAGNOSTIC_DEVICE (0xdc),

    /** Wireless class */
    LIBUSB_CLASS_WIRELESS (0xe0),

    /** Miscellaneous class (standard only) */
    LIBUSB_MISCELLANEOUS (0xef),

    /** Application class */
    LIBUSB_CLASS_APPLICATION (0xfe),
    /** Class is vendor-specific */
    LIBUSB_CLASS_VENDOR_SPEC (0xff);

    public static LibUSBClassCode getCode(int value) {
        switch (value) {
            case 0x00: return LibUSBClassCode.LIBUSB_CLASS_PER_INTERFACE;
            case 0x01: return LibUSBClassCode.LIBUSB_CLASS_AUDIO;
            case 0x02: return LibUSBClassCode.LIBUSB_CLASS_COMM;
            case 0x03: return LibUSBClassCode.LIBUSB_CLASS_HID;

            case 0x05: return LibUSBClassCode.LIBUSB_CLASS_PHYSICAL;
            case 0x06: return LibUSBClassCode.LIBUSB_CLASS_IMAGE;
            case 0x07: return LibUSBClassCode.LIBUSB_CLASS_PRINTER;
            case 0x08: return LibUSBClassCode.LIBUSB_CLASS_MASS_STORAGE;
            case 0x09: return LibUSBClassCode.LIBUSB_CLASS_HUB;
            case 0x0a: return LibUSBClassCode.LIBUSB_CLASS_DATA;
            case 0x0b: return LibUSBClassCode.LIBUSB_CLASS_SMART_CARD;

            case 0x0d: return LibUSBClassCode.LIBUSB_CLASS_CONTENT_SECURITY;
            case 0x0e: return LibUSBClassCode.LIBUSB_CLASS_VIDEO;
            case 0x0f: return LibUSBClassCode.LIBUSB_CLASS_PERSONAL_HEALTHCARE;

            case 0x10: return LibUSBClassCode.LIBUSB_AUDIO_VIDEO_DEVICES;
            case 0x11: return LibUSBClassCode.LIBUSB_BILLBOARD_DEVICE;
            case 0x12: return LibUSBClassCode.LIBUSB_USB_TYPE_C_BRIDGE_DEVICE;

            case 0xdc: return LibUSBClassCode.LIBUSB_CLASS_DIAGNOSTIC_DEVICE;
            case 0xe0: return LibUSBClassCode.LIBUSB_CLASS_WIRELESS;

            case 0xef: return LibUSBClassCode.LIBUSB_MISCELLANEOUS;

            case 0xfe: return LibUSBClassCode.LIBUSB_CLASS_APPLICATION;
            case 0xff: return LibUSBClassCode.LIBUSB_CLASS_VENDOR_SPEC;

            default:
                // TODO: Exception class needed
                throw new RuntimeException(String.format("Error: Converting value %d to LibUSBClassCode", value));
        }
    }

    /**
     * skip continuos ordinal values
     */
    private int value;
    LibUSBClassCode(int value){
        this.value = value;
    }
    public int getValue(){
        return value;
    }
}
