LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/hellocpp/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)


LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
