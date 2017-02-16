/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jconsole_Console */

#ifndef _Included_jconsole_Console
#define _Included_jconsole_Console
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jconsole_Console
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jconsole_Console_initialize
  (JNIEnv *, jclass);

/*
 * Class:     jconsole_Console
 * Method:    shutdown
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jconsole_Console_shutdown
  (JNIEnv *, jclass);

/*
 * Class:     jconsole_Console
 * Method:    clear
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jconsole_Console_clear
  (JNIEnv *, jclass);

/*
 * Class:     jconsole_Console
 * Method:    print
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_jconsole_Console_print
  (JNIEnv *, jclass, jstring);

/*
 * Class:     jconsole_Console
 * Method:    showCursor
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_jconsole_Console_showCursor
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     jconsole_Console
 * Method:    moveCursor
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_jconsole_Console_moveCursor
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jconsole_Console
 * Method:    readCharacter
 * Signature: ()C
 */
JNIEXPORT jchar JNICALL Java_jconsole_Console_readCharacter
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif