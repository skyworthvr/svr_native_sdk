
LOCAL_PATH:= $(call my-dir)



include $(CLEAR_VARS)
LOCAL_MODULE := libxrapi
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../../../../libs/Release/$(TARGET_ARCH_ABI)/libxrapi.so
include $(PREBUILT_SHARED_LIBRARY)

#--------------------------------------------------------
# libvrcubeworld.so
#--------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE			:= vrcubeworld
LOCAL_CFLAGS			:= -Werror -Wno-c++11-narrowing
LOCAL_SRC_FILES			:= VrCubeWorld_NativeActivity.cpp
LOCAL_LDLIBS			:= -llog -landroid -lGLESv3 -lEGL

LOCAL_STATIC_LIBRARIES	:= android_native_app_glue
LOCAL_C_INCLUDES        := $(LOCAL_PATH)/include
LOCAL_SHARED_LIBRARIES	:= libxrapi
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
