load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_jvm_external",
    sha256 = "f36441aa876c4f6427bfb2d1f2d723b48e9d930b62662bf723ddfb8fc80f0140",
    strip_prefix = "rules_jvm_external-4.1",
    url = "https://github.com/bazelbuild/rules_jvm_external/archive/4.1.zip",
)

http_archive(
    name = "io_bazel_rules_kotlin",
    sha256 = "dc1c76f91228ddaf4f7ca4190b82d61939e95369f61dea715e8be28792072b1b",
    strip_prefix = "rules_kotlin-legacy-1.3.0-rc2",
    type = "zip",
    urls = ["https://github.com/bazelbuild/rules_kotlin/archive/legacy-1.3.0-rc2.zip"],
)

android_sdk_repository(
    name="androidsdk",
    path="/Users/martin/Library/Android/sdk",
    api_level=29,
    build_tools_version="30.0.2",
)

android_ndk_repository(
    name="androidndk",
    path="/Users/martin/Library/Android/sdk/ndk/21.4.7075529",
    api_level=23,
)

load("@io_bazel_rules_kotlin//kotlin:kotlin.bzl", "kt_register_toolchains")
kt_register_toolchains()

load("@io_bazel_rules_kotlin//kotlin:kotlin.bzl", "kotlin_repositories")
kotlin_repositories()
