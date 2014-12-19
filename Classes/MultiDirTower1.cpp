//
//  MultiDirTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "MultiDirTower1.h"
#include "GameManager.h"
#include <algorithm>

bool MultiDirTower1::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(150);
	setTowerValue(400);
    setLethality(1);
    setRate(3);
	setLevel(0);
	setTowerType(2);
	//add by  
    //tower= Sprite::createWithSpriteFrameName("multiDirTower.png");
	tower= Sprite::createWithSpriteFrameName("tower3_1.png");
    this->addChild(tower);
    
    this->schedule(schedule_selector(MultiDirTower1::createBullet6), 0.8f);
	return true;
}


Sprite* MultiDirTower1::MultiDirTowerBullet()
{
	//add by  
    //Sprite* bullet = Sprite::createWithSpriteFrameName("bullet.png");
	Sprite* bullet = Sprite::createWithSpriteFrameName("fire3.png");
    //bullet->setPosition(0, tower->getContentSize().height /4 );
    //this->addChild(bullet);
    //modified by  
	auto position=this->getTowerPos();
	bullet->setPosition(position);
	this->getParent()->addChild(bullet);
	//addChild(bullet);
	auto heat=this->getLethality();
	heat= heat + 30;
	bullet->setTag(heat);
    return bullet;
}

void MultiDirTower1::createBullet6(float dt)
{
	GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    int dirTotal = 10;
	this->checkNearestEnemy();
	if(nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0 )
    {
		for(int i = 0; i < dirTotal; i++)
		{
			auto currBullet = MultiDirTowerBullet();
			instance->bulletVector.pushBack(currBullet);
            
			auto moveDuration = getRate();
            
			Point shootVector;
			shootVector.x = 1;
			shootVector.y = tan( i * 2 * M_PI / dirTotal );
			Point normalizedShootVector;
			if( i >= dirTotal / 2 )
			{
				normalizedShootVector = shootVector.normalize();
			}else{
				normalizedShootVector = -shootVector.normalize();
			}
			auto farthestDistance = Director::getInstance()->getWinSize().width;
			Point overshotVector = normalizedShootVector * farthestDistance;
			Point offscreenPoint = (currBullet->getPosition() - overshotVector);
            
			currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
												   CallFuncN::create(CC_CALLBACK_1(MultiDirTower1::removeBullet, this)),
												   NULL));
			currBullet = NULL;
		}
	}
}


void MultiDirTower1::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}