//
//  TowerBase.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#ifndef __thiefTD__TowerBase__
#define __thiefTD__TowerBase__

#include <iostream>
#include "cocos2d.h"

#include "EnemyBase.h"


USING_NS_CC;

class TowerBase: public Sprite
{
public:
    TowerBase();
    
    virtual bool init();
    CREATE_FUNC(TowerBase);
    
    void checkNearestEnemy();
	CC_SYNTHESIZE(Point, towerPos, TowerPos);
	CC_SYNTHESIZE(int, towerType, TowerType);
    CC_SYNTHESIZE(int, level, Level);
	CC_SYNTHESIZE(int, rate, Rate);//塔攻击速度
    CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线范围
    CC_SYNTHESIZE(int, lethality, Lethality);   // 杀伤力
    CC_SYNTHESIZE(int, towerValue, TowerValue);  //塔价格
	//CC_SYNTHESIZE(Point, towerPos, TowerPos);
	//塔类型按从左到右排列0,1,2,3,4,5
	//
    
protected:
    EnemyBase* nearestEnemy;    // 塔子视野内最近的敌人

	//Point position;//塔的位置 ，用于解决升级子弹打不中塔的问题
};


#endif /* defined(__thiefTD__TowerBase__) */
