#include <jni.h>
#include <fcntl.h>

int fd = 0;

JNIEXPORT jint JNICALL Java_edu_skku_sm5baseled_1jnidriver_BaseLed_1JNIDriver_openDriver
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

JNIEXPORT void JNICALL Java_edu_skku_sm5baseled_1jnidriver_BaseLed_1JNIDriver_closeDriver
  (JNIEnv * env, jclass class){
	if (fd > 0)
		close(fd);
}


JNIEXPORT void JNICALL Java_edu_skku_sm5baseled_1jnidriver_BaseLed_1JNIDriver_writeDriver
  (JNIEnv * env, jclass class, jbyteArray arr, jint count){
	unsigned char value = 0;
	unsigned char temp;
	int i;
	jbyte * chars = (*env)->GetByteArrayElements(env, arr, 0);

	if (fd>0) {
		for(i=0; i<8; i++) {
			if (*(chars+i) != 0) {
				temp = 0x01;
				temp = (unsigned char)(temp<<i);
				value = (unsigned char) (value | temp);
			}
		}
		write(fd, (unsigned char *)&value, 1);
	}

	(*env)->ReleaseByteArrayElements(env, arr, chars, 0);

}

/* 원래 코드
JNIEXPORT void JNICALL Java_edu_skku_sm5baseled_1jnidriver_BaseLed_1JNIDriver_writeDriver
  (JNIEnv * env, jclass class, jbyteArray arr, jint count){
	jbyte * chars = (*env)->GetByteArrayElements(env, arr, 0);
	if (fd>0)
		write(fd, (unsigned char *)chars, count);
	(*env)->ReleaseByteArrayElements(env, arr, chars, 0);
} */
