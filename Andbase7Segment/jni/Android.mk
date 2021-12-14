LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Base7SegmentJNIDriver
LOCAL_SRC_FILES := Base7SegmentJNIDriver.c

include $(BUILD_SHARED_LIBRARY)
