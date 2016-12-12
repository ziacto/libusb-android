/**
 * License Public Domain (CC0) 2016 Julio Tentor (jtentor@gmail.com)
 *
 * To the extent possible under law, Julio Tentor has waived all copyright and related
 * or neighboring rights. This work is published from: Jujuy - Argentina.
 *
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 */

#ifndef LIBUSB_ANDROID_LIBUSBJNI_H
#define LIBUSB_ANDROID_LIBUSBJNI_H

#include <iostream>
#include <sstream>
#include <string>

#include <stdexcept>

#include "libusb/libusb.h"
#include "libusb/libusbi.h"

/**
 *
 */
class libusbjni {

public:
    libusbjni() {};
    ~libusbjni() {};

    std::string EnumerateDevices();


private:
    void EnumerateInterfaces(std::ostringstream &out, const libusb_config_descriptor * usbConfig);
    void EnumerateEndpoints(std::ostringstream  & out, const libusb_interface_descriptor * usbInterfaceDescriptor);

    void HexaDump(std::ostringstream & out, const std::string & indent, const unsigned char *extra, int extra_length);

    const std::string libusb_class_text(const enum libusb_class_code code);
    const std::string libusb_class_text(const int code) {
        try {
            return libusb_class_text((const enum libusb_class_code) code);
        } catch (...) {
            throw std::invalid_argument("Error in libusb_class_code conversion ");
        }
    }

    const std::string libusb_subclass_text(const enum libusb_class_code code, int subcode);
    const std::string libusb_subclass_text(const int code, int subcode) {
        try {
            return libusb_subclass_text((const enum libusb_class_code) code, subcode);
        } catch (...) {
            throw std::invalid_argument("Error in libusb_class_code conversion ");
        }
    }


};


#endif //LIBUSB_ANDROID_LIBUSBJNI_H