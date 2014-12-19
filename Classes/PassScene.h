//
//  WarningScene.h
//  thiefTD
//
//  Created by  on 14-11-24.
//
//

#ifndef __thiefTD__Pass__
#define __thiefTD__Pass__

#include <iostream>
#include "cocos2d.h"


USING_NS_CC;

class PassScene : public Layer
{
public:

	PassScene();
    CREATE_FUNC(PassScene);
    static Scene * createScene();
	bool init();
                                                                                  
	void menuBackCallback(Ref* pSender);

private:
	PassScene* info;
	std::string fileName;
};
#endif /* defined(__thiefTD__LevelInfoScene__) */
