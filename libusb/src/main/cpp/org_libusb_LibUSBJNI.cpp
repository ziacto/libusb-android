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

#include "org_libusb_LibUSBJNI.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     org_libusb_LibUSBJNI
 * Method:    usb_jni_demo
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_libusb_LibUSBJNI_usb_1jni_1demo
        (JNIEnv * jniEnv, jobject jobObject, jint demoMode) {

    libusbjni usbjni = libusbjni();
    std::string text = usbjni.EnumerateDevices();

    return jniEnv->NewStringUTF(text.c_str());

}

#ifdef __cplusplus
}
#endif

