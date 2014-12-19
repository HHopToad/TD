//
//  GameManager.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#ifndef __thiefTD__GameManager__
#define __thiefTD__GameManager__

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h"


USING_NS_CC;

class GameManager
{
public:
    
    Vector<EnemyBase*> enemyVector;
    Vector<Sprite*> bulletVector;
	Vector<Sprite*> bulletVector2;
	Vector<Sprite*> bulletVector3;
	Vector<Sprite*> bulletVector21;
	Vector<Sprite*> bulletVector22;
	Vector<Sprite*> bulletVector23;
	Vector<Sprite*> bulletVector31;
	Vector<Sprite*> bulletVector32;
	Vector<Sprite*> bulletVector33;
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;
    
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	//当前波数
	CC_SYNTHESIZE(int, currGroup, CurrGroup);

	//当前第几个怪物数量
	CC_SYNTHESIZE(int, enemyNum, EnemyNum);
	//当前第几个怪物数量
	CC_SYNTHESIZE(int, currEnemy, CurrEnemy);
	//设置音效和背景音乐
	CC_SYNTHESIZE(bool, playEffect, PlayEffect);
	CC_SYNTHESIZE(bool, playSount, PlaySount);


	CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
	CC_SYNTHESIZE(std::string, curBgName, CurBgName);
    CC_SYNTHESIZE(int, lev, Lev);
	CC_SYNTHESIZE(int, tp, Tp);
    bool init();
	void clear();
    
	static GameManager* getInstance();
    
private:
	static GameManager * instance;
};
#endif /* defined(__thiefTD__GameManager__) */
