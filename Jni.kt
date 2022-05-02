package io.fzed.helloworldjni

class Jni {
  init {
    System.loadLibrary("hello_world")
  }

  external fun hello(instance: SomeClass)
}
