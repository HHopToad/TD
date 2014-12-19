//
//  ArrowTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "ArrowTower2.h"
#include "GameManager.h"

bool ArrowTower2::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(160);
    setLethality(2);
	setTowerValue(120);
    setRate(2);
	setLevel(0);
	setTowerType(0);

	// add by  


   /* auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);
    
    rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
    rotateArrow->setPosition(0, baseplate->getContentSize().height /4  );
    addChild(rotateArrow);*/

		auto ll = getLevel();

    tower= Sprite::createWithSpriteFrameName("tower1_2.png");
	this->addChild(tower);
    schedule(schedule_selector(ArrowTower2::rotateAndShoot), 0.8f);
	return true;
}


Sprite* ArrowTower2::ArrowTowerBullet()
{
	//add by  
   // Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");

	Sprite* bullet = Sprite::createWithSpriteFrameName("fire1.png");

   // bullet->setPosition(rotateArrow->getPosition());
   // bullet->setRotation(rotateArrow->getRotation());


	//bullet->setPosition(0, tower->getContentSize().height /4 );
   // addChild(bullet);
    //modified by  
	auto position=this->getTowerPos();
	bullet->setPosition(position);
	this->getParent()->addChild(bullet);
	//addChild(bullet);
	auto heat=this->getLethality();
	heat= heat + 10;
	bullet->setTag(heat);
    return bullet;
}

void ArrowTower2::rotateAndShoot(float dt)
{
 //   checkNearestEnemy();
 //   if (nearestEnemy != NULL)
	//{
	//	auto rotateVector = nearestEnemy->sprite->getPosition() - this->getPosition();
	//	auto rotateRadians = rotateVector.getAngle();
	//	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
 //       
	//	auto speed = 0.5 / M_PI;
	//	auto rotateDuration = fabs(rotateRadians * speed);
 //       rotateArrow->runAction( Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
 //                                                CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
 //                                                NULL));
	//}
	//add by  
	checkNearestEnemy();
    if (nearestEnemy != NULL)
	{
	//	auto rotateVector = nearestEnemy->sprite->getPosition() - this->getPosition();
	//	auto rotateRadians = rotateVector.getAngle();
	//	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
        
	//	auto speed = 0.5 / M_PI;
	//	auto rotateDuration = fabs(rotateRadians * speed);
    //    rotateArrow->runAction( Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
    //                                             CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
   //                                              NULL));
		shoot();
	}



}

void ArrowTower2::shoot()
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

		//add by  
		Point offscreenPoint = (currBullet->getPosition() - overshotVector);
		//Point offscreenPoint = (rotateArrow->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ArrowTower2::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void ArrowTower2::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

