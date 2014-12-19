//
//  WarningScene.h
//  thiefTD
//
//  Created by  on 14-12-7.
//
//

#ifndef __thiefTD__Setting__
#define __thiefTD__Setting__

#include <iostream>
#include "cocos2d.h"
#include "UIScene.h"
#include "GameManager.h"

USING_NS_CC;

class SettingScene : public Layer
{
public:

	SettingScene();
    CREATE_FUNC(SettingScene);
    static Scene * createScene();
	bool init();
                                                                                  
	void menuBackCallback(Ref* pSender);
	void menuSoundCallback(Ref* pSender);
	void menuEffectCallback(Ref* pSender);
private:
	SettingScene* info;
	std::string fileName;
	GameManager* instance;
};
#endif /* defined(__thiefTD__Setting__) */
