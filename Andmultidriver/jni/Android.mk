LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JNIDriver
LOCAL_SRC_FILES := fpga7segment_JNIDriver.c fpgaPiezo_JNIDriver.c fpgaTextLCD_JNIDriver.c

include $(BUILD_SHARED_LIBRARY)
