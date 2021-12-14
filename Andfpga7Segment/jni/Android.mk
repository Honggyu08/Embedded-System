LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := fpga7segment_JNIDriver
LOCAL_SRC_FILES := fpga7segment_JNIDriver.c

include $(BUILD_SHARED_LIBRARY)
