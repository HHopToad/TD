//
//  UIScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__UIScene__
#define __thiefTD__UIScene__

#include <iostream>
#include "cocos2d.h"



class UIScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  

    void menuStartCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);

	void menuHelpCallback(Ref* pSender);
	void menuSettingCallback(Ref* pSender);
	//add for umeng
	//void shareCallback(int platform, int stCode, string* errorMsg);

    CREATE_FUNC(UIScene);
	cocos2d::RepeatForever* MyPathFun(float controlX, float controlY, float w);
};

#endif /* defined(__thiefTD__UIScene__) */
