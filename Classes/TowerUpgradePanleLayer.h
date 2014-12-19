//
//  TowerPanleLayer.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#ifndef __thiefTD__TowerUpgradePanleLayer__
#define __thiefTD__TowerUpgradePanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"
#include "GameManager.h"

USING_NS_CC;

typedef enum
{
    SELL = 0,
    UPGRADE_ONE = 1,
	UPGRADE_TW0,
	UPGRADE_THREE,
	OTHER
} TowerUpgrade;

class TowerUpgradePanleLayer: public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(TowerUpgradePanleLayer);
    
    bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	bool onTouchBegan1(Touch *touch, Event *event);
	void onTouchEnded1(Touch* touch, Event* event);
    //update add by 
	//virtual void update(float dt) override;
    CC_SYNTHESIZE(TowerUpgrade, chooseTowerUpgrade, ChooseTowerUpgrade);
    
private:
    GameManager* instance;
    Sprite* sprite1;
	Sprite* sprite2;
};


#endif /* defined(__thiefTD__TowerPanleLayer__) */
