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
    void EnumerateInterfaces(std::ostringstream  & out, const libusb_config_descriptor * usbConfig);
    void EnumerateEndpoints(std::ostringstream  & out, const libusb_interface_descriptor * usbInterfaceDescriptor);


};


#endif //LIBUSB_ANDROID_LIBUSBJNI_H