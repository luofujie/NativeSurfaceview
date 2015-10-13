LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_MODULE    := TestSufaceView

LOCAL_SRC_FILES := TestSufaceView.cpp \
	conver.cpp
LOCAL_LDLIBS := -llog -landroid \
#	$(LOCAL_PATH)/lib/libavcodec-56.so \
#	$(LOCAL_PATH)/lib/libavdevice-56.so \
#	$(LOCAL_PATH)/lib/libavfilter-5.so \
#	$(LOCAL_PATH)/lib/libavformat-56.so \
#	$(LOCAL_PATH)/lib/libavutil-54.so \
#	$(LOCAL_PATH)/lib/libswresample-1.so \
#	$(LOCAL_PATH)/lib/libswscale-3.so 
	
include $(BUILD_SHARED_LIBRARY)
