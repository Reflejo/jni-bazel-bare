package io.fzed.helloworldjni

import android.app.Activity
import android.os.Bundle
import android.util.Log

class SomeClass {
  fun sendData(streamId: Int, dataToSend: ByteArray): Boolean {
    Log.e("Bazel", "Stream ID: $streamId data: $dataToSend")
    return true
  }
}

class MainActivity : Activity() {

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    val jni = Jni()
    var someClass = SomeClass()

    Log.v("Bazel", "JNI says: " + jni.hello(someClass))
  }
}
