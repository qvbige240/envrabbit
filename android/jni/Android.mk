LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

MASK_ROOT := $(LOCAL_PATH)/../../Classes
FILE_LIST += $(wildcard $(MASK_ROOT)/*.cpp)

LOCAL_SRC_FILES := helloworld/main.cpp
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
                   
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../..) \
$(call import-add-path, $(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/prebuilt) \
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d-1.0.1-x-0.13.0-beta) \
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d-1.0.1-x-0.13.0-beta/cocos2dx/platform/third_party/android/prebuilt) \
$(call import-add-path, $(LOCAL_PATH)/../../../../cocos2d-1.0.1-x-0.13.0-beta/workspace) \
$(call import-add-path, $(LOCAL_PATH)/../../../../cocos2d-1.0.1-x-0.13.0-beta/workspace/cocos2dx/platform/third_party/android/prebuilt) \
$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx)
