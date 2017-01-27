/**
 * License Public Domain (CC0) 2016 Julio Tentor (jtentor@gmail.com)
 *
 * To the extent possible under law, Julio Tentor has waived all copyright and related
 * or neighboring rights. This work is published from: Jujuy - Argentina.
 *
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 */

#include "libusbjni.h"

#include <bitset>
#include <iomanip>

#include <android/log.h>
#define LOG_TAG "usb_io"
#define printf(fmt,args...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, fmt, ##args)

#define CLASS_AUDIO 0x01
#define SUBCLASS_AUDIOCONTROL 0x01
#define PR_PROTOCOL_UNDEFINED 0x00
#define PROTOCOL_IP_VERSION_02_00 0x20

/**
 * Enumerate USB Devices
 *
 * \returns text with information about USB Devices detected
 */
std::string libusbjni::EnumerateDevices() {

    std::ostringstream out;

    libusb_context *usbContext = NULL;
    libusb_device **usbDevices;
    libusb_config_descriptor *usbConfig;
    libusb_device_descriptor usbDeviceDescriptor;

    int usbDevicesCount;
    int r;

    r = libusb_init(&usbContext);
    if (r < 0) {
        out << "libusb_init() "
        << " [error: " << r << " - " << libusb_strerror((enum libusb_error) r) << "] " << std::endl;
        return out.str();
    }

    usbDevicesCount = r = libusb_get_device_list(usbContext, &usbDevices);
    if (r < 0) {
        out << "libusb_get_devices_list() "
        << " [error: " << r << " - " << libusb_strerror((enum libusb_error) r) << "] " << std::endl;
        return out.str();
    }

    out << std::endl;
    out << "Detected " << usbDevicesCount << " USB Devices " << std::endl;
    out << std::endl;

    for (int i = 0; i < usbDevicesCount; ++i) {
        r = libusb_get_device_descriptor(usbDevices[i], &usbDeviceDescriptor);
        if (r < 0) {
            out << std::endl << "libusb_get_device_descriptor() "
            << " [error: " << r << " - " << libusb_strerror((enum libusb_error) r) << "] " <<
            std::endl;
        }
        else {
            out << "Device [#]..............: " << i << std::endl;

            out << "bcdUSB..................: " << usbDeviceDescriptor.bcdUSB
            << " (0x" << std::hex << std::setw(4) << std::setfill('0')
            << (int) usbDeviceDescriptor.bcdUSB << std::dec << ") "
            << std::endl;

            out << "idVendor................: " << usbDeviceDescriptor.idVendor
            << " (0x" << std::hex << std::setw(4) << std::setfill('0') <<
            usbDeviceDescriptor.idVendor
            << std::dec << ")"
            << std::endl;
            out << "idProduct...............: " << usbDeviceDescriptor.idProduct
            << " (0x" << std::hex << std::setw(4) << std::setfill('0') <<
            usbDeviceDescriptor.idProduct
            << std::dec << ")"
            << std::endl;

            out << "bDeviceClass............: " << (uint) usbDeviceDescriptor.bDeviceClass
            << " (0x" << std::hex << std::setw(2) << std::setfill('0')
            << (int) usbDeviceDescriptor.bDeviceClass << std::dec << ") "
            << libusb_class_text((int) usbDeviceDescriptor.bDeviceClass)
            << std::endl;
            out << "bDeviceSubClass.........: " << (uint) usbDeviceDescriptor.bDeviceSubClass
            << " (0x" << std::hex << std::setw(2) << std::setfill('0')
            << (int) usbDeviceDescriptor.bDeviceSubClass << std::dec << ") "
            << std::endl;
            out << "bDeviceProtocol.........: " << (uint) usbDeviceDescriptor.bDeviceProtocol
            << " (0x" << std::hex << std::setw(2) << std::setfill('0')
            << (int) usbDeviceDescriptor.bDeviceProtocol << std::dec << ") "
            << std::endl;

            out << "bNumConfigurations......: " << (uint) usbDeviceDescriptor.bNumConfigurations <<
            std::endl;

            for (int j = 0; j < usbDeviceDescriptor.bNumConfigurations; ++j) {
                r = libusb_get_config_descriptor(usbDevices[i], j, &usbConfig);
                if (r < 0) {
                    out << std::endl << "libusb_get_config_descriptor() "
                    << " [error: " << r << " - " << libusb_strerror((enum libusb_error) r)
                    << "] " << std::endl;
                }
                else {
                    EnumerateInterfaces(out, usbConfig);
                }
            }
            out << std::endl;
        }
        out << std::endl;
    }


    libusb_free_device_list(usbDevices, 1);
    libusb_exit(usbContext);

    return out.str();
}


/**
 * Enumerate Interfaces in a configuration
 *
 * \param out output stream
 * \param usbConfig libusb configuration descriptor
 */
void libusbjni::EnumerateInterfaces(std::ostringstream &out,
                                    const libusb_config_descriptor *usbConfig) {

    const libusb_interface *usbInterface;
    const libusb_interface_descriptor *usbInterfaceDescriptor;


    out << "bNumInterfaces..........: " << (uint) usbConfig->bNumInterfaces << std::endl;

    int totNumInterfaces = 0;
    for (int i = 0; i < (uint) usbConfig->bNumInterfaces; ++i) {
        totNumInterfaces += (usbConfig->interface[i]).num_altsetting;
    }

    out << "Total No Interfaces (*).: " << totNumInterfaces << std::endl;

    if (usbConfig->extra_length != 0) {
        out << "extra_length (*)........: " << usbConfig->extra_length << std::endl;

        out << "\t" << "Hexdecimal dump of extra data" << std::endl;
        HexaDump(out, "\t", usbConfig->extra, usbConfig->extra_length);
    }

    for (int i = 0; i < (uint) usbConfig->bNumInterfaces; ++i) {
        usbInterface = &(usbConfig->interface[i]);

        out << std::endl;
        out << "\t";
        out << "Interface [#]...........: " << i << std::endl;

        out << "\t";
        out << "num_altsetting..........: " << usbInterface->num_altsetting << std::endl;

        for (int j = 0; j < usbInterface->num_altsetting; ++j) {
            usbInterfaceDescriptor = &(usbInterface->altsetting[j]);

            out << std::endl;

            out << "\t\t";
            out << "bInterfaceNumber........: " << (uint) usbInterfaceDescriptor->bInterfaceNumber
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') <<
            (int) usbInterfaceDescriptor->bInterfaceNumber << std::dec << ")"
            << std::endl;

            out << "\t\t";
            out << "bAlternateSetting.......: " << (uint) usbInterfaceDescriptor->bAlternateSetting
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') <<
            (int) usbInterfaceDescriptor->bAlternateSetting << std::dec << ") "
            << std::endl;

            out << "\t\t";
            out << "bInterfaceClass.........: " << (uint) usbInterfaceDescriptor->bInterfaceClass
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') <<
            (int) usbInterfaceDescriptor->bInterfaceClass << std::dec << ") "
            << libusb_class_text((int) usbInterfaceDescriptor->bInterfaceClass)
            << std::endl;
            out << "\t\t";
            out << "bInterfaceSubClass......: " << (uint) usbInterfaceDescriptor->bInterfaceSubClass
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') <<
            (int) usbInterfaceDescriptor->bInterfaceSubClass << std::dec << ") "
            << libusb_subclass_text((int) usbInterfaceDescriptor->bInterfaceClass,
                                    (int) usbInterfaceDescriptor->bInterfaceSubClass)
            << std::endl;
            out << "\t\t";
            out << "bInterfaceProtocol......: " << (uint) usbInterfaceDescriptor->bInterfaceProtocol
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') <<
            (int) usbInterfaceDescriptor->bInterfaceProtocol << std::dec << ") "
            << std::endl;

            if(usbInterfaceDescriptor->bInterfaceClass == CLASS_AUDIO &&
                    usbInterfaceDescriptor->bInterfaceSubClass == SUBCLASS_AUDIOCONTROL) {
                switch (usbInterfaceDescriptor->bInterfaceProtocol) {
                    case PR_PROTOCOL_UNDEFINED:
                        printf("UACSPEC %s", "UAC1 device");
                        break;
                    case PROTOCOL_IP_VERSION_02_00:
                        printf("UACSPEC %s", "UAC2 device");
                        break;
                    default:
                        break;
                }
            }

            EnumerateEndpoints(out, usbInterfaceDescriptor);
        }
        out << std::endl;

    }

}

/**
 * Enumerate Endpoints in one pair interface - alternate setting
 *
 * \param out output stream
 * \param usbConfig libusb interface descriptor
 */
void libusbjni::EnumerateEndpoints(std::ostringstream &out,
                                   const libusb_interface_descriptor *usbInterfaceDescriptor) {

    const libusb_endpoint_descriptor *usbEndpointDescriptor;
    unsigned int ui8;

    out << "\t\t";
    out << "No of Endpoints.........: " << (uint) usbInterfaceDescriptor->bNumEndpoints <<
    std::endl;
    for (int i = 0; i < (int) usbInterfaceDescriptor->bNumEndpoints; ++i) {
        usbEndpointDescriptor = &(usbInterfaceDescriptor->endpoint[i]);

        out << "\t\t\t";
        out << "Endpoint type (5) ......: " << (uint) usbEndpointDescriptor->bDescriptorType
        << " (0x" << std::hex << std::setw(2) << std::setfill('0')
        << (int) usbEndpointDescriptor->bDescriptorType << ")" << std::dec
        << std::endl;

        out << "\t\t\t";
        out << "Endpoint #..............: " <<
        ((uint) usbEndpointDescriptor->bEndpointAddress & 0x03) <<
        std::endl;

        ui8 = ((uint) usbEndpointDescriptor->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK);
        out << "\t\t\t";
        out << "Endpoint Direction......: " << ui8
        << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ") "
        << (IS_EPIN(usbEndpointDescriptor->bEndpointAddress) ? " device to host "
                                                             : " host to device ") << std::endl;

//        ui8 = ((uint) usbEndpointDescriptor->bEndpointAddress & LIBUSB_ENDPOINT_ADDRESS_MASK);
        ui8 = ((uint) usbEndpointDescriptor->bEndpointAddress);
        out << "\t\t\t";
        out << "bEndpointAddress........: " << ui8
        << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ")"
        << " (" << std::bitset<8>(ui8) << "b)" << std::endl;


        ui8 = ((uint) usbEndpointDescriptor->bmAttributes);
        out << "\t\t\t";
        out << "bmAttributes............: " << ui8
        << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ")"
        << " (" << std::bitset<8>(ui8) << "b)" << std::endl;

        ui8 = ((uint) usbEndpointDescriptor->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK);
        out << "\t\t\t";
        out << "Transfer Type...........: " << ui8
        << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ")"
        << " (" << std::bitset<8>(ui8) << "b) -";
        switch (ui8) {
            case LIBUSB_TRANSFER_TYPE_CONTROL:
                out << " Control ";
                break;
            case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
                out << " Isochronous ";
                break;
            case LIBUSB_TRANSFER_TYPE_BULK:
                out << " Bulk ";
                break;
            case LIBUSB_TRANSFER_TYPE_INTERRUPT:
                out << " Interrupt ";
                break;
            case LIBUSB_TRANSFER_TYPE_BULK_STREAM:
                out << " Stream ";
                break;
        }
        out << std::endl;

        out << "\t\t\t";
        out << "wMaxPacketSize..........: " << usbEndpointDescriptor->wMaxPacketSize << std::endl;

        out << "\t\t\t";
        out << "bInterval...............: " << (uint) usbEndpointDescriptor->bInterval << std::endl;

        if (usbInterfaceDescriptor->bInterfaceClass & LIBUSB_CLASS_AUDIO) {
            out << "\t\t\t";
            out << "bRefresh (synch rate)...: " << (uint) usbEndpointDescriptor->bRefresh
            << " (0x" << std::hex << std::setw(2) << std::setfill('0')
            << (uint) usbEndpointDescriptor->bRefresh << std::dec << ")"
            << std::endl;
            out << "\t\t\t";
            out << "bSynchAddress...........: " << (uint) usbEndpointDescriptor->bSynchAddress
            << " (0x" << std::hex << std::setw(2) << std::setfill('0')
            << (uint) usbEndpointDescriptor->bSynchAddress << std::dec << ")"
            << std::endl;
        }

        out << "\t\t\t";
        out << "extra_length (*)........: " << usbEndpointDescriptor->extra_length << std::endl;

        if (usbEndpointDescriptor->extra_length != 0) {
            out << "\t\t\t\t" << "Hexdecimal dump of extra data" << std::endl;
            HexaDump(out, "\t\t\t\t", usbEndpointDescriptor->extra,
                     usbEndpointDescriptor->extra_length);

//            if (usbInterfaceDescriptor->bInterfaceClass & LIBUSB_CLASS_AUDIO) {
//                if (usbEndpointDescriptor->extra[1] == 0x25) {
//                    out << "\t\t\t\t" << "Audio Class Type: CS_ENDPOINT" << std::endl;
//                }
//                if (usbEndpointDescriptor->extra[2] == 0x01) {
//                    out << "\t\t\t\t" << "Audio Class SubType: HEADER" << std::endl;
//                }
//            }
        }

        out << std::endl;
    }

}

/**
 * Generates an hexadecimal dump for the extra_length bytes in extra buffer
 *
 * \param out output stream
 * \param extra bytes buffer
 * \param extra_length number of bytes in extra byte buffer
 */
void libusbjni::HexaDump(std::ostringstream &out, const std::string &indent,
                         const unsigned char *extra, int extra_length) {

    for (int i = 0; i < extra_length; ++i) {
        if (!(i % 0x10)) {
            if (i > 0) {
                out << std::endl;
            }
            out << indent;
        }
        out << std::hex << std::setw(2) << std::setfill('0') << (uint) extra[i] << std::dec << " ";
    }
    out << std::endl;
}

/**
 * Returns text asociated to specif class code
 *
 * \param enum libusb_class_code value
 * \returns text asociated to libusb_class_code
 * \ref enum libusb_class_code
 */
const std::string libusbjni::libusb_class_text(const enum libusb_class_code code) {
    switch (code) {
        case LIBUSB_CLASS_PER_INTERFACE:
            return "LIBUSB_CLASS_PER_INTERFACE";
        case LIBUSB_CLASS_AUDIO:
            return "LIBUSB_CLASS_AUDIO";
        case LIBUSB_CLASS_COMM:
            return "LIBUSB_CLASS_COMM";
        case LIBUSB_CLASS_HID:
            return "LIBUSB_CLASS_HID";
        case LIBUSB_CLASS_PHYSICAL:
            return "LIBUSB_CLASS_PHYSICAL";
        case LIBUSB_CLASS_PRINTER:
            return "LIBUSB_CLASS_PRINTER";
        case LIBUSB_CLASS_IMAGE:
            return "LIBUSB_CLASS_IMAGE";
        case LIBUSB_CLASS_MASS_STORAGE:
            return "LIBUSB_CLASS_MASS_STORAGE";
        case LIBUSB_CLASS_HUB:
            return "LIBUSB_CLASS_HUB";
        case LIBUSB_CLASS_DATA:
            return "LIBUSB_CLASS_DATA";
        case LIBUSB_CLASS_SMART_CARD:
            return "LIBUSB_CLASS_SMART_CARD";
        case LIBUSB_CLASS_CONTENT_SECURITY:
            return "LIBUSB_CLASS_CONTENT_SECURITY";
        case LIBUSB_CLASS_VIDEO:
            return "LIBUSB_CLASS_VIDEO";
        case LIBUSB_CLASS_PERSONAL_HEALTHCARE:
            return "LIBUSB_CLASS_PERSONAL_HEALTHCARE";
        case LIBUSB_CLASS_DIAGNOSTIC_DEVICE:
            return "LIBUSB_CLASS_DIAGNOSTIC_DEVICE";
        case LIBUSB_CLASS_WIRELESS:
            return "LIBUSB_CLASS_WIRELESS";
        case LIBUSB_CLASS_APPLICATION:
            return "LIBUSB_CLASS_APPLICATION";
        case LIBUSB_CLASS_VENDOR_SPEC:
            return "LIBUSB_CLASS_VENDOR_SPEC";
    }
    return "";
}

/**
 * Returns text asociated to specif subclass code
 *
 * \param enum libusb_class_code value
 * \param subclass vale
 * \returns text asociated to subclass code
 * \ref enum libusb_class_code specific subclass codes
 */
const std::string libusbjni::libusb_subclass_text(const enum libusb_class_code code, int subcode) {
    switch (code) {
//        case LIBUSB_CLASS_PER_INTERFACE:            return "LIBUSB_CLASS_PER_INTERFACE";

        case LIBUSB_CLASS_AUDIO:
            switch (subcode) {
                case 0x00:
                    return "SUBCLASS_UNDEFINED";
                case 0x01:
                    return "AUDIOCONTROL";
                case 0x02:
                    return "AUDIOSTREAMING";
                case 0x03:
                    return "MIDISTREAMING";
            }
            return "SUBCLASS_UNDEFINED";

//        case LIBUSB_CLASS_COMM:                     return "LIBUSB_CLASS_COMM";
//        case LIBUSB_CLASS_HID:                      return "LIBUSB_CLASS_HID";
//        case LIBUSB_CLASS_PHYSICAL:                 return "LIBUSB_CLASS_PHYSICAL";
//        case LIBUSB_CLASS_PRINTER:                  return "LIBUSB_CLASS_PRINTER";
//        case LIBUSB_CLASS_IMAGE:                    return "LIBUSB_CLASS_IMAGE";
//        case LIBUSB_CLASS_MASS_STORAGE:             return "LIBUSB_CLASS_MASS_STORAGE";
//        case LIBUSB_CLASS_HUB:                      return "LIBUSB_CLASS_HUB";
//        case LIBUSB_CLASS_DATA:                     return "LIBUSB_CLASS_DATA";
//        case LIBUSB_CLASS_SMART_CARD:               return "LIBUSB_CLASS_SMART_CARD";
//        case LIBUSB_CLASS_CONTENT_SECURITY:         return "LIBUSB_CLASS_CONTENT_SECURITY";
//        case LIBUSB_CLASS_VIDEO:                    return "LIBUSB_CLASS_VIDEO";
//        case LIBUSB_CLASS_PERSONAL_HEALTHCARE:      return "LIBUSB_CLASS_PERSONAL_HEALTHCARE";
//        case LIBUSB_CLASS_DIAGNOSTIC_DEVICE:        return "LIBUSB_CLASS_DIAGNOSTIC_DEVICE";
//        case LIBUSB_CLASS_WIRELESS:                 return "LIBUSB_CLASS_WIRELESS";
//        case LIBUSB_CLASS_APPLICATION:              return "LIBUSB_CLASS_APPLICATION";
//        case LIBUSB_CLASS_VENDOR_SPEC:              return "LIBUSB_CLASS_VENDOR_SPEC";
    }
    return "SUBCLASS_UNDEFINED";
}
