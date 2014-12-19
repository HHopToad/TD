//
//  MultiDirTower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__MultiDirTower2__
#define __thiefTD__MultiDirTower2__

#include "TowerBase.h"


class MultiDirTower2:public TowerBase
{
public:    
    virtual bool init() ;
    CREATE_FUNC(MultiDirTower2);    
    void shoot(float dt);
    void removeBullet(Node* pSender);
    Sprite* MultiDirTowerBullet();
    void createBullet6(float dt);
private:
    Sprite* tower;
    
};

#endif /* defined(__thiefTD__MultiDirTower__) */
