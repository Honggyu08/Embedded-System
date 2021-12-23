#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <jni.h>

static int fd;

JNIEXPORT void JNICALL Java_edu_skku_lhg_andalarm_1jnidriver_fpgaPiezo_1JNIDriver_open
  (JNIEnv * env, jobject obj){
	fd = open("/dev/lhg_fpgaPiezo_driver", O_WRONLY);
	assert(fd != -1);
}

JNIEXPORT void JNICALL Java_edu_skku_lhg_andalarm_1jnidriver_fpgaPiezo_1JNIDriver_write
  (JNIEnv * env, jobject obj, jchar data){
	write(fd, &data, 1);
}

JNIEXPORT void JNICALL Java_edu_skku_lhg_andalarm_1jnidriver_fpgaPiezo_1JNIDriver_close
  (JNIEnv * env, jobject obj){
	close(fd);
}
