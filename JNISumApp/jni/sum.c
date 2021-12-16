#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_example_jnisumapp_MainActivity_sum
   (JNIEnv * env, jobject obj, jint a, jint b){

	return a + b;

}
