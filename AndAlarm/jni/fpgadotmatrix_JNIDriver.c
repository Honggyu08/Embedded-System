#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <jni.h>

JNIEXPORT void JNICALL Java_edu_skku_lhg_andfpgadotmatrix_1jnidriver_fpgadotmatrix_1JNI_DotMatrixControl
  (JNIEnv * env, jobject obj, jstring str){
	const char *pStr;
		int fd, len;

		pStr = (*env)->GetStringUTFChars(env, str, 0);
		len = (*env)->GetStringLength(env, str);

		fd = open("/dev/lhg_fpgaDotMatrix_driver", O_RDWR | O_SYNC);

		write(fd, pStr, len);
		close(fd);

		(*env)->ReleaseStringUTFChars(env, str, pStr);
}
