#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>

#define  LOG_TAG    "fz debug"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static JavaVM* static_jvm = nullptr;
static thread_local JNIEnv* local_env = nullptr;

template <class... Args>
bool callBoolJniMethod(JNIEnv* env, void* context, const char* name, const char* signature,
                       Args&&... args) {
    jobject j_context = static_cast<jobject>(context);
    jclass j_context_class = env->GetObjectClass(j_context);
    jmethodID jmid_method = env->GetMethodID(j_context_class, name, signature);
    bool result = env->CallBooleanMethod(j_context, jmid_method, args...);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        LOGE("jni function should not throw exception, not handled");
    }

    env->DeleteLocalRef(j_context_class);

    return result;
}

jbyteArray createJByteArray(JNIEnv* env, const uint8_t* data, int32_t size) {
    jbyteArray j_data = env->NewByteArray(size);
    jbyte* critical_data = env->GetByteArrayElements(j_data, nullptr);
    memcpy(critical_data, data, size);
    env->ReleaseByteArrayElements(j_data, critical_data, 0);
    return j_data;
}

JNIEnv* get_env() {
    if (local_env) {
        return local_env;
    }

    jint result = static_jvm->GetEnv(reinterpret_cast<void**>(&local_env), JNI_VERSION_1_6);
    if (result == JNI_EDETACHED) {
        JavaVMAttachArgs args = {JNI_VERSION_1_6, "EnvoyMain", NULL};
        result = static_jvm->AttachCurrentThread(&local_env, &args);
    }

    return local_env;
}

static void test(jobject context) {
    const uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x02, 0x0a, 0x00};
    int32_t size = 7;

    JNIEnv* env = get_env();
    jbyteArray byte_array = createJByteArray(env, data, size);

    bool status = callBoolJniMethod(env, context, "sendData", "(I[B)Z", 0, byte_array);
    LOGE("Array memory ended up at %p %d", reinterpret_cast<void*>(byte_array), status);
    env->DeleteLocalRef(byte_array);
}

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = nullptr;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    static_jvm = vm;
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT void JNICALL
Java_io_fzed_helloworldjni_Jni_hello(JNIEnv *env, jclass clazz, jobject j_stuff_class) {
  jobject context = env->NewGlobalRef(j_stuff_class);
  test(context);
}
