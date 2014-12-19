//
//  TowerPanleLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#include "TowerUpgradePanleLayer.h"

bool TowerUpgradePanleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	instance=GameManager::getInstance();
	setChooseTowerUpgrade(TowerUpgrade::OTHER);
	// add by 
	//塔类型

	int tp = instance->getTp();
	
	auto sprite = Sprite::createWithSpriteFrameName("towerstatus.png");

	auto ss=sprite->getContentSize();
	sprite1 = Sprite::create("cancel.png");
	sprite1->setAnchorPoint(Point(0.5f,1.0f));
	auto s=sprite1->getContentSize();
	sprite1->setPosition(Point( -3* s.width/4, - ss.height/2));
	this->addChild(sprite1,20);
	//add by 
	//sprite1 = Sprite::createWithSpriteFrameName("tower1.png");
	

	auto price1=Sprite::create("120S.png");
	auto price2=Sprite::create("150S.png");
	auto price3=Sprite::create("400S.png");
	auto ss1= sprite1->getContentSize();
	auto ll=instance->getLev();
	if(ll < 3 )
	{

		if( tp == 0)
		{

			
			price1->setAnchorPoint(Point(0.5f,0.0f));
			price1->setPosition(ss1.width/2,0);
			sprite2 = Sprite::create("build.png");
			sprite2->addChild(price1);
			
		}
		else if (tp == 1 )
		{
			price2->setAnchorPoint(Point(0.5f,0.0f));
			price2->setPosition(ss1.width/2,0);
			sprite2 = Sprite::create("build.png");
			sprite2->addChild(price2);
		}
		else
		{
			price3->setAnchorPoint(Point(0.5f,0.0f));
			price3->setPosition(ss1.width/2,0);
			sprite2 = Sprite::create("build.png");
			sprite2->addChild(price3);
		}	

		//sprite2 = Sprite::create("build.png");
	}
	else
	{sprite2 = Sprite::create("buildno.png");
	}


	//sprite2 = Sprite::create("build.png");
	sprite2->setAnchorPoint( Point(0.5f, 1.0f));
	sprite2->setPosition(Point( 3* sprite2->getContentSize().width /4, - ss.height/2) );
	this->addChild(sprite2,20);

	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TowerUpgradePanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TowerUpgradePanleLayer::onTouchEnded, this);

	auto touchListener1 = EventListenerTouchOneByOne::create();
	touchListener1->setSwallowTouches(true);
	touchListener1->onTouchBegan = CC_CALLBACK_2(TowerUpgradePanleLayer::onTouchBegan1, this);
	touchListener1->onTouchEnded = CC_CALLBACK_2(TowerUpgradePanleLayer::onTouchEnded1, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);

	//等级在3之前才相应升级按钮
	if(ll < 3 )
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	}
	else
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener1, sprite2);
	}

	scheduleUpdate();
	
	return true;
}


bool TowerUpgradePanleLayer::onTouchBegan(Touch *touch, Event *event)
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


void TowerUpgradePanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == sprite1)
	{
		chooseTowerUpgrade = SELL;
	}
	else if(target == sprite2)
	{
		chooseTowerUpgrade = UPGRADE_ONE;
	}

	else{
		chooseTowerUpgrade = OTHER;
	}
}
bool TowerUpgradePanleLayer::onTouchBegan1(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);

	if (rect.containsPoint(locationInNode))
	{
		//target->setOpacity(180);
		return true;
	}
	return false;
}


void TowerUpgradePanleLayer::onTouchEnded1(Touch* touch, Event* event)
{
	
		chooseTowerUpgrade = OTHER;

}
