//
//  AttackTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__AttackTowerTower3__
#define __thiefTD__AttackTowerTower3__

#include "TowerBase.h"

class AttackTower3:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(AttackTower3);

    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* AttackTowerBullet();
    
private:
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__AttackTower__) */
