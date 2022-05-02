#include <jni.h>

#include "jni_dep.h"

const char* hello = "Hello JNI";

extern "C" JNIEXPORT jstring JNICALL
Java_io_fzed_helloworldjni_Jni_hello(JNIEnv *env, jclass clazz) {
  return NewStringLatin1(env, hello);
}
