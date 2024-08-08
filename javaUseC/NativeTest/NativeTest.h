#pragma once
#ifdef NATIVETEST_EXPORTS
#define NATIVETEST_EXPORTS __declspec(dllexport)
#else 
#define  NATIVETEST_EXPORTS __declspec(dllimport)
#endif // LED_EXPORTS

#include <jni.h>
/* Header for class NativeTest */

#ifndef _Included_NativeTest
#define _Included_NativeTest
#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Class:     NativeTest
	 * Method:    hello
	 * Signature: (Ljava/lang/String;)V
	 */
	JNIEXPORT jstring JNICALL Java_NativeTest_hello
	(JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif