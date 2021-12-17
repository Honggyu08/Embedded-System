LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := BaseLed_JNIDriver
LOCAL_SRC_FILES := BaseLed_JNIDriver.c

include $(BUILD_SHARED_LIBRARY)
