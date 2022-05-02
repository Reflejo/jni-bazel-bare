load("@io_bazel_rules_kotlin//kotlin:kotlin.bzl", "kt_android_library")

android_binary(
    name = "hello_world",
    custom_package = "io.fzed.helloworldjni",
    manifest = "AndroidManifest.xml",
    deps = [
        "hello_world_kt_lib",
    ],
)

kt_android_library(
    name = "hello_world_kt_lib",
    srcs = [
        "MainActivity.kt",
        "Jni.kt",
    ],
    custom_package = "io.fzed.helloworldjni",
    manifest = "AndroidManifest.xml",
    resource_files = glob(["res/**"]),
    deps = [
        ":jni_lib",
    ],
)

java_library(
  name = "jni_lib",
  runtime_deps = [
    ":jni",
  ],
)

cc_library(
    name = "jni",
    srcs = ["jni.cc"],
    copts = ["-std=c++17"],
    linkopts = [
        "-lm",
        "-llog",
        "-ldl",
        "-Wl,--build-id=sha1",
    ],
    alwayslink = True,
)
