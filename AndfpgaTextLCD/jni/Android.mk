LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := fpgaTextLCD_JNIDriver
LOCAL_SRC_FILES := fpgaTextLCD_JNIDriver.c

include $(BUILD_SHARED_LIBRARY)
