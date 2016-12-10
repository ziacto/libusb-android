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

std::string libusbjni::EnumerateDevices() {

    std::ostringstream  out;

//    out << "Hola desde libusbjni::EnumerateDevices()\n";


    libusb_context * usbContext = NULL;
    libusb_device ** usbDevices;
    int usbDevicesCount;
    int r;

    r = libusb_init(&usbContext);
    if (r < 0){
        out << "libusb_init() "
        << " [error: " << r << " - " << libusb_strerror((enum libusb_error)r) << "] " << std::endl;
        return out.str();
    }

    usbDevicesCount = r = libusb_get_device_list(usbContext, &usbDevices);
    if (r < 0){
        out << "libusb_get_devices_list() "
        << " [error: " << r << " - " << libusb_strerror((enum libusb_error)r) << "] " << std::endl;
        return out.str();
    }

    out << std::endl;
    out << "Detected " << usbDevicesCount << " USB Devices " << std::endl;
    out << std::endl;

    libusb_device_descriptor usbDevice;
    libusb_config_descriptor * usbConfig;
//    const libusb_interface * usbInterface;
//    const libusb_interface_descriptor * usbInterfaceDescriptor;
//    const libusb_endpoint_descriptor * usbEndpointDescriptor;

    for(int idev = 0; idev < usbDevicesCount; ++idev) {
        r = libusb_get_device_descriptor(usbDevices[idev], &usbDevice);
        if (r < 0){
            out << std::endl << "libusb_get_device_descriptor() "
            << " [error: " << r << " - " << libusb_strerror((enum libusb_error)r) << "] " << std::endl;
        }
        else {

            out << "VendorID................: " << usbDevice.idVendor
                << " (0x" << std::hex << std::setw(4) << std::setfill('0') << usbDevice.idVendor << ")" << std::endl;
            out << "ProductID...............: " << usbDevice.idProduct
                << " (0x" << std::hex << std::setw(4) << std::setfill('0') << usbDevice.idProduct << std::dec << ")" << std::endl;

            out << "Device Class............: " << (int)usbDevice.bDeviceClass
                << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbDevice.bDeviceClass << std::dec << ")" << std::endl;
            out << "Sub Class...............: " << (int)usbDevice.bDeviceSubClass
                << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbDevice.bDeviceSubClass << std::dec << ")" << std::endl;
            out << "Protocol................: " << (int)usbDevice.bDeviceProtocol
                << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbDevice.bDeviceProtocol << std::dec << ")" << std::endl;
            out << "Configurations..........: " << (int)usbDevice.bNumConfigurations << std::endl;

            for(int iconf = 0; iconf < usbDevice.bNumConfigurations; ++iconf){
                r = libusb_get_config_descriptor(usbDevices[idev], iconf, &usbConfig);
                if (r < 0){
                    out << std::endl << "libusb_get_config_descriptor() "
                    << " [error: " << r << " - " << libusb_strerror((enum libusb_error)r) << "] " << std::endl;
                }
                else {
                    EnumerateInterfaces(out, usbConfig);
                }
            }
        }
        out << "*************************" << std::endl;
    }

    libusb_free_device_list(usbDevices, 1);
    libusb_exit(usbContext);

    return out.str();
}


void libusbjni::EnumerateInterfaces(std::ostringstream  & out, const libusb_config_descriptor * usbConfig) {

    const libusb_interface * usbInterface;
    const libusb_interface_descriptor * usbInterfaceDescriptor;

    out << "Interfaces supported....: " << (int)usbConfig->bNumInterfaces << std::endl;
    for(int i = 0; i < (int)usbConfig->bNumInterfaces; ++i) {
        usbInterface = &(usbConfig->interface[i]);

        out << " ";
        out << "Alt. Settings...........: " << (int)usbInterface->num_altsetting << std::endl;

        for(int j = 0; j < usbInterface->num_altsetting; ++j) {
            usbInterfaceDescriptor = &(usbInterface->altsetting[j]);

            out << "  ";
            out << "Interface No............: " << (int)usbInterfaceDescriptor->bInterfaceNumber
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbInterfaceDescriptor->bInterfaceNumber << std::dec << ")" << std::endl;

            out << "  ";
            out << "Alternate Setting No....: " << (int)usbInterfaceDescriptor->bAlternateSetting
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbInterfaceDescriptor->bAlternateSetting << std::dec << ")" << std::endl;

            out << "  ";
            out << "Interface Class.........: " << (int)usbInterfaceDescriptor->bInterfaceClass
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbInterfaceDescriptor->bInterfaceClass << std::dec << ")" << std::endl;
            out << "  ";
            out << "Sub Class...............: " << (int)usbInterfaceDescriptor->bInterfaceSubClass
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbInterfaceDescriptor->bInterfaceSubClass << std::dec << ")" << std::endl;
            out << "  ";
            out << "Protocol................: " << (int)usbInterfaceDescriptor->bInterfaceProtocol
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbInterfaceDescriptor->bInterfaceProtocol << std::dec << ")" << std::endl;

            EnumerateEndpoints(out, usbInterfaceDescriptor);
        }

    }

}


void libusbjni::EnumerateEndpoints(std::ostringstream & out, const libusb_interface_descriptor * usbInterfaceDescriptor) {

    const libusb_endpoint_descriptor * usbEndpointDescriptor;
    unsigned int ui8;

    out << "  ";
    out << "No of Endpoints.........: " << (int)usbInterfaceDescriptor->bNumEndpoints << std::endl;
    for(int i = 0; i < (int)usbInterfaceDescriptor->bNumEndpoints; ++i) {
        usbEndpointDescriptor = &(usbInterfaceDescriptor->endpoint[i]);

        out << "   ";
        out << "Endpoint type (5) ......: " << (int)usbEndpointDescriptor->bDescriptorType
        << " (0x" << std::hex << std::setw(2) << std::setfill('0') << (int)usbEndpointDescriptor->bDescriptorType << ")" << std::dec << std::endl;

        out << "   ";
        out << "Endpoint #..............: " << i << " - bEndpointAddress: "  << (usbEndpointDescriptor->bEndpointAddress & 0x03) << std::endl;

        ui8 = ((uint)usbEndpointDescriptor->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK);

        out << "   ";
        out << "Endpoint Direction......: " << ui8
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ") "
            << (IS_EPIN(usbEndpointDescriptor->bEndpointAddress) ? " device to host " : " host to device ") << std::endl;

        ui8 = ((uint)usbEndpointDescriptor->bEndpointAddress & LIBUSB_ENDPOINT_ADDRESS_MASK);

        out << "   ";
        out << "Endpoint Address........: " << ui8
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ")"
            << " (" << std::bitset<8>(ui8) << "b)" << std::endl;

        ui8 = ((uint)usbEndpointDescriptor->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK);
        out << "   ";
        out << "Transfer Type...........: " << ui8
            << " (0x" << std::hex << std::setw(2) << std::setfill('0') << ui8 << std::dec << ")"
            << " (" << std::bitset<8>(ui8) << "b) -";
        switch(ui8){
            case LIBUSB_TRANSFER_TYPE_CONTROL:
                out << " Control endpoint ";
                break;
            case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
                out << " Isochronous endpoint ";
                break;
            case LIBUSB_TRANSFER_TYPE_BULK:
                out << " Bulk endpoint ";
                break;
            case LIBUSB_TRANSFER_TYPE_INTERRUPT:
                out << " Interrupt endpoint ";
                break;
            case LIBUSB_TRANSFER_TYPE_BULK_STREAM:
                out << " Stream endpoint ";
                break;
        }
        out << std::endl;

        out << "   ";
        out << "Max Packet Size.........: " << usbEndpointDescriptor->wMaxPacketSize << std::endl;

//        out << "\t\t\t";
//        out << "Interval................: " << (int)usbEndpointDescriptor->bInterval << std::endl;

    }

}
