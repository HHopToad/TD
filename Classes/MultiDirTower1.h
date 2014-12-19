//
//  MultiDirTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__MultiDirTower1__
#define __thiefTD__MultiDirTower1__

#include "TowerBase.h"


class MultiDirTower1:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(MultiDirTower1);
    
    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* MultiDirTowerBullet();
    void createBullet6(float dt);
private:
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__MultiDirTower__) */
