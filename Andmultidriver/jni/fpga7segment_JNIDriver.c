#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <jni.h>

static int fd = 0;

JNIEXPORT jint JNICALL Java_edu_skku_lhg_andmultidriver_1jnidriver_fpga7segment_1JNIDriver_openDriver
  (JNIEnv * env, jclass class, jstring path){
	jboolean iscopy;
	const char *path_utf = (*env)->GetStringUTFChars(env, path, &iscopy);
	fd = open(path_utf, O_WRONLY);
	(*env)->ReleaseStringUTFChars(env, path, path_utf);
	if (fd < 0)
		return -1;
	else
		return 1;
}

JNIEXPORT void JNICALL Java_edu_skku_lhg_andmultidriver_1jnidriver_fpga7segment_1JNIDriver_closeDriver
  (JNIEnv * env, jclass class){
	if (fd > 0)
		close(fd);
}

JNIEXPORT void JNICALL Java_edu_skku_lhg_andmultidriver_1jnidriver_fpga7segment_1JNIDriver_writeDriver
  (JNIEnv * env, jclass class, jint value){
if (fd>0) {
write(fd, &value, 4);
}

}

JNIEXPORT void JNICALL Java_edu_skku_lhg_andmultidriver_1jnidriver_fpga7segment_1JNIDriver_ioctlDriver
  (JNIEnv * env, jclass class, jint value){
	if (fd>0) {
		ioctl(fd, value, NULL, NULL);
	}
}
