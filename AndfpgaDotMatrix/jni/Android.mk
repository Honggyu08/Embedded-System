LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := fpgadotmatrix_JNI
LOCAL_SRC_FILES := fpgadotmatrix_JNI.c

include $(BUILD_SHARED_LIBRARY)
