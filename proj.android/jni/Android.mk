LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp
LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ArrowTower.cpp \
                   ../../Classes/AttackTower.cpp \
                   ../../Classes/EnemyBase.cpp \
                   ../../Classes/FailedScene.cpp \
                   ../../Classes/GameManager.cpp \
                   ../../Classes/GroupEnemy.cpp \
                   ../../Classes/LevelInfoScene.cpp \
                   ../../Classes/LevelLayer.cpp \
                   ../../Classes/LevelScene.cpp \
                   ../../Classes/LevelSelectPage.cpp \
                   ../../Classes/LoadingResScene.cpp \
                   ../../Classes/LoadLevelInfo.cpp \
                   ../../Classes/MultiDirTower.cpp \
                   ../../Classes/PlayLayer.cpp \
                   ../../Classes/SuccessfulScene.cpp \
                   ../../Classes/Thief.cpp \
                   ../../Classes/TowerBase.cpp \
                   ../../Classes/TowerPanleLayer.cpp \
                   ../../Classes/UIScene.cpp \
				   ../../Classes/ArrowTower1.cpp \
				   ../../Classes/ArrowTower2.cpp \
				   ../../Classes/ArrowTower3.cpp \
				   ../../Classes/AttackTower1.cpp \
				   ../../Classes/AttackTower2.cpp \
				   ../../Classes/AttackTower3.cpp \
				   ../../Classes/HelpScene.cpp \
				   ../../Classes/MultiDirTower1.cpp \
				   ../../Classes/MultiDirTower2.cpp \
				   ../../Classes/MultiDirTower3.cpp \
				   ../../Classes/PassScene.cpp \
				   ../../Classes/SettingScene.cpp \
				   ../../Classes/TowerUpgradePanleLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
 $(LOCAL_PATH)/../../cocos2d/extensions \
 $(LOCAL_PATH)/../../cocos2d/external \
 $(LOCAL_PATH)/../../cocos2d/cocos \
 $(LOCAL_PATH)/../../cocos2d/cocos/2d \
 $(LOCAL_PATH)/../../cocos2d/cocos/2d/render \
 $(LOCAL_PATH)/../../cocos2d/cocos/2d/gui \
 $(LOCAL_PATH)/../../cocos2d/cocos/gui \
 $(LOCAL_PATH)/../../cocos2d/cocos/2d/base \
 $(LOCAL_PATH)/../../cocos2d/cocos/2d/physics \
 $(LOCAL_PATH)/../../cocos2d/cocos/math \
 $(LOCAL_PATH)/../../cocos2d/cocos/base \
 $(LOCAL_PATH)/../../cocos2d/cocos/audio/include \
 $(LOCAL_PATH)/../../cocos2d/cocos/editor-support \
 $(LOCAL_PATH)/../../cocos2d/cocos/network \
 $(LOCAL_PATH)/../../cocos2d/cocos/ui \
 $(LOCAL_PATH)/../../cocos2d/cocos/physics \
 $(LOCAL_PATH)/../../cocos2d/cocos/storage \
 $(LOCAL_PATH)/../../cocos2d/chipmunk/include/chipmunk \
 $(LOCAL_PATH)/../../cocos2d


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)

        $(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
        $(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
        $(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

        LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
        LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
        LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
        LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
        LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

        $(call import-module,editor-support/cocosbuilder)
        $(call import-module,editor-support/spine)
        $(call import-module,editor-support/cocostudio)
        $(call import-module,network)
        $(call import-module,extensions)
