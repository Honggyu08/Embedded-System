#include <jni.h>
#include <fcntl.h>

int fd = 0;

JNIEXPORT jint JNICALL Java_edu_skku_andbase7segment_1jnidriver_Base7SegmentJNIDriver_openDriver
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

JNIEXPORT void JNICALL Java_edu_skku_andbase7segment_1jnidriver_Base7SegmentJNIDriver_closeDriver
(JNIEnv * env, jobject obj){
	if (fd > 0)
		close(fd);
}

JNIEXPORT void JNICALL Java_edu_skku_andbase7segment_1jnidriver_Base7SegmentJNIDriver_writeDriver
(JNIEnv * env, jobject obj, jint value){
	char input[2]={0};

	if (fd>0) {
		input[0] = value/16;
		input[1] = value%16;
		write(fd, (unsigned char *)input, 2);
	}
}
