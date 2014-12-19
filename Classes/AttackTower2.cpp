//
//  AttackTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "AttackTower2.h"
#include "GameManager.h"

bool AttackTower2::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(120);
	setTowerValue(150);
    setLethality(6);
    setRate(2);
	setLevel(0);
	setTowerType(1);
	//add by  
    //tower= Sprite::createWithSpriteFrameName("attackTower.png");
	tower= Sprite::createWithSpriteFrameName("tower2_2.png");
    this->addChild(tower);
    
    schedule(schedule_selector(AttackTower2::shoot), 0.8f);
	return true;
}


Sprite* AttackTower2::AttackTowerBullet()
{
	// add by  
    //Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    Sprite* bullet = Sprite::createWithSpriteFrameName("fire2.png");
	//bullet->setPosition(0, tower->getContentSize().height /4 );
    //this->addChild(bullet);
    //modified by  
	auto position=this->getTowerPos();
	bullet->setPosition(position);
	this->getParent()->addChild(bullet);
	//addChild(bullet);
	auto heat=this->getLethality();
	heat= heat + 20;
	bullet->setTag(heat);
    return bullet;
}

void AttackTower2::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    checkNearestEnemy();
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = AttackTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (currBullet->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(AttackTower2::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void AttackTower2::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}