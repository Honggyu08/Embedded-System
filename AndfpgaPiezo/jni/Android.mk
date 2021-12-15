LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := fpgaPiezo_JNIDriver
LOCAL_SRC_FILES := fpgaPiezo_JNIDriver.c

include $(BUILD_SHARED_LIBRARY)
