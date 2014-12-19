//
//  WarningScene.h
//  thiefTD
//
//  Created by zych on 14-11-24.
//
//

#ifndef __thiefTD__Warning__
#define __thiefTD__Warning__

#include <iostream>
#include "cocos2d.h"


USING_NS_CC;

class WarningScene : public Layer
{
public:

	WarningScene();
    CREATE_FUNC(WarningScene);
    static Scene * createScene();
	bool init();
                                                                                  
	void menuBackCallback(Ref* pSender);

private:
	WarningScene* info;
	std::string fileName;
};
#endif /* defined(__thiefTD__LevelInfoScene__) */
