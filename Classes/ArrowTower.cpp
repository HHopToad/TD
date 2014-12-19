//
//  ArrowTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "ArrowTower.h"
#include "GameManager.h"

bool ArrowTower::init()
{
	if (!TowerBase::init())
	{
		return false;
	}

	setScope(120);
	setLethality(1);
	setTowerValue(120);
	setRate(3);
	setLevel(0);
	setTowerType(0);



	auto ll = getLevel();
	if( ll == 0 )
	{
		tower= Sprite::createWithSpriteFrameName("tower1.png");
	}
	else if ( ll == 1)
	{
		tower= Sprite::createWithSpriteFrameName("tower2.png");
	}
	else 
	{
		tower= Sprite::createWithSpriteFrameName("tower3.png");
	}
	this->addChild(tower);
	schedule(schedule_selector(ArrowTower::rotateAndShoot), 0.8f);
	return true;
}


Sprite* ArrowTower::ArrowTowerBullet()
{

	Sprite* bullet = Sprite::createWithSpriteFrameName("fire1.png");


	auto position=this->getTowerPos();
	bullet->setPosition(position);
	auto heat=this->getLethality();
	heat= heat + 10;
	bullet->setTag(heat);
	this->getParent()->addChild(bullet);


	return bullet;
}

void ArrowTower::rotateAndShoot(float dt)
{

	checkNearestEnemy();
	if (nearestEnemy != NULL)
	{

		shoot();
	}



}

void ArrowTower::shoot()
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
			CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
			NULL));
		currBullet = NULL;
	}
}

void ArrowTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	Sprite *sprite = (Sprite *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}

