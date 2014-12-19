//
//  TowerPanleLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#include "TowerPanleLayer.h"

bool TowerPanleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setChooseTowerType(TowerType::ANOTHER);
	// add by 
	auto sprite = Sprite::createWithSpriteFrameName("towerstatus.png");
	//auto sprite = Sprite::create("towerstatus.png");
	sprite->setPosition(Point(0, 0));
	this->addChild(sprite);
	//add by 
	sprite1 = Sprite::createWithSpriteFrameName("tower1.png");
	//sprite1 = Sprite::create("tower1.png");
	sprite1->setAnchorPoint( Point(0.5f, 0));
	sprite1->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height/2));
	this->addChild(sprite1);

	// sprite2 = Sprite::createWithSpriteFrameName("AttackTower1.png");
	sprite2 = Sprite::createWithSpriteFrameName("tower2.png");
	sprite2->setAnchorPoint( Point(0.5f, 0));
	sprite2->setPosition(Point(0, sprite->getContentSize().height/2));
	this->addChild(sprite2);

	//sprite3 = Sprite::createWithSpriteFrameName("MultiDirTower1.png");
	sprite3 = Sprite::createWithSpriteFrameName("tower3.png");
	sprite3->setAnchorPoint( Point(0.5f, 0));
	sprite3->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height/2));
	this->addChild(sprite3);








	//add by  
	instance = GameManager::getInstance();
	price1=CCSprite::create("120.png");
	price2=CCSprite::create("150.png");
	price3=CCSprite::create("400.png");
	priceno1=CCSprite::create("120no.png");
	priceno2=CCSprite::create("150no.png");
	priceno3=CCSprite::create("400no.png");
	auto s= sprite1->getContentSize();
	price1->setAnchorPoint(Point(0.5f,0.0f));
	price1->setPosition(s.width/2,0);
	price2->setAnchorPoint(Point(0.5f,0.0f));
	price2->setPosition(s.width/2,0);
	price3->setAnchorPoint(Point(0.5f,0.0f));
	price3->setPosition(s.width/2,0);
	priceno1->setAnchorPoint(Point(0.5f,0.0f));
	priceno1->setPosition(s.width/2,0);
	priceno2->setAnchorPoint(Point(0.5f,0.0f));
	priceno2->setPosition(s.width/2,0);
	priceno3->setAnchorPoint(Point(0.5f,0.0f));
	priceno3->setPosition(s.width/2,0);
	//*********************************************/
	int money=instance->getMoney();
	if( money >= 400 )
	{			
		sprite1->addChild(price1);
		sprite2->addChild(price2);
		sprite3->addChild(price3);
	}
	else if (money  >= 150 )
	{

		sprite1->addChild(price1);
		sprite2->addChild(price2);
		sprite3->addChild(priceno3);
	}
	else if (money >= 120)
	{

		sprite1->addChild(price1);
		sprite2->addChild(priceno2);
		sprite3->addChild(priceno3);
	}
	else
	{

		sprite1->addChild(priceno1);
		sprite2->addChild(priceno2);
		sprite3->addChild(priceno3);
	}


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);
	scheduleUpdate();
	
	return true;
}


bool TowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);

	if (rect.containsPoint(locationInNode))
	{
		target->setOpacity(180);
		return true;
	}
	return false;
}


void TowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == sprite1)
	{
		chooseTowerType = ARROW_TOWER;
	}
	else if(target == sprite2)
	{
		chooseTowerType = ATTACK_TOWER;
	}
	else if(target == sprite3)
	{
		chooseTowerType = MULTIDIR_TOWER;
	}
	else{
		chooseTowerType = ANOTHER;
	}
}

//add by  
void TowerPanleLayer::update(float dt)
{








}