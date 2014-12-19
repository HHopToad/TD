//
//  ArrowTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "ArrowTower1.h"
#include "GameManager.h"

bool ArrowTower1::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(140);
    setLethality(1);
	setTowerValue(120);
    setRate(2);
	setLevel(0);
	setTowerType(0);



	auto ll = getLevel();

    tower= Sprite::createWithSpriteFrameName("tower1_1.png");

	this->addChild(tower);
    schedule(schedule_selector(ArrowTower1::rotateAndShoot), 0.8f);
	return true;
}


Sprite* ArrowTower1::ArrowTowerBullet()
{
	
	Sprite* bullet = Sprite::createWithSpriteFrameName("fire1.png");

  
	auto position=this->getTowerPos();
	bullet->setPosition(position);
	this->getParent()->addChild(bullet);

	auto heat=this->getLethality();
	heat= heat + 10;
	bullet->setTag(heat);
    return bullet;
}

void ArrowTower1::rotateAndShoot(float dt)
{
 
	checkNearestEnemy();
    if (nearestEnemy != NULL)
	{
		shoot();
	}



}

void ArrowTower1::shoot()
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = ArrowTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;


		Point offscreenPoint = (currBullet->getPosition() - overshotVector);
		//Point offscreenPoint = (rotateArrow->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ArrowTower1::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void ArrowTower1::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

