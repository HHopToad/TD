//
//  WarningScene.h
//  thiefTD
//
//  Created by  on 14-12-7.
//
//

#ifndef __thiefTD__Help__
#define __thiefTD__Help__

#include <iostream>
#include "cocos2d.h"

#include "UIScene.h"


USING_NS_CC;

class HelpScene : public Layer
{
public:

	HelpScene();
    CREATE_FUNC(HelpScene);
    static Scene * createScene();
	bool init();
                                                                                  
	void menuBackCallback(Ref* pSender);

private:
	HelpScene* info;
	std::string fileName;
};
#endif /* defined(__thiefTD__LevelInfoScene__) */
