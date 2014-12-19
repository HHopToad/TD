//
//  AttackTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__AttackTowerTower2__
#define __thiefTD__AttackTowerTower2__

#include "TowerBase.h"

class AttackTower2:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(AttackTower2);

    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* AttackTowerBullet();
    
private:
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__AttackTower__) */
