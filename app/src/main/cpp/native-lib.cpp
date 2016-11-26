#include <jni.h>
#include <string>

extern "C"
jstring
Java_org_libusb_1android_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++\n\nThis is native-lib.cpp in main/cpp from libUSB-Android demo application";
    return env->NewStringUTF(hello.c_str());
}
