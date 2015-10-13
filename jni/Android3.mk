LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE :=avcodec
LOCAL_SRC_FILES :=$(LOCAL_PATH)/lib/libavcodec-56.so
include$(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE :=avdevice
LOCAL_SRC_FILES :=$(LOCAL_PATH)/lib/libavdevice-56.so
include$(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE :=avfilter
LOCAL_SRC_FILES :=$(LOCAL_PATH)/lib/libavfilter-5.so
include$(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE :=avformat
LOCAL_SRC_FILES :=$(LOCAL_PATH)/lib/libavformat-56.so
include$(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE :=  avutil
LOCAL_SRC_FILES :=$(LOCAL_PATH)/lib/llibavutil-54.so
include$(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE :=  swscale
LOCAL_SRC_FILES :=$(LOCAL_PATH)/lib/libswscale-3.so
include$(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := TestSufaceView.cpp \
	conver.cpp
LOCAL_MODULE := FFMPEG
LOCAL_LDLIBS := -llog -landroid 

LOCAL_SHARED_LIBRARIES:= avcodec avdevice avfilter avformat avutil
include $(BUILD_SHARED_LIBRARY)