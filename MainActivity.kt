package io.fzed.helloworldjni

import android.app.Activity
import android.os.Bundle
import android.util.Log

class MainActivity : Activity() {

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    val jni = Jni()
    Log.v("Bazel", "Hello, Android")
    Log.v("Bazel", "JNI says: " + jni.hello())
  }
}
