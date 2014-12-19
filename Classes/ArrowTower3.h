//
//  ArrowTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#ifndef __thiefTD__ArrowTower3__
#define __thiefTD__ArrowTower3__

#include "TowerBase.h"


class ArrowTower3:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ArrowTower3);

    void rotateAndShoot(float dt);
    void shoot();
    void removeBullet(Node* pSender);
    Sprite* ArrowTowerBullet();
    
private:
   // Sprite* rotateArrow;
	Sprite* tower;
    
};

#endif /* defined(__thiefTD__ArrowTower__) */
