//
//  Thief.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "Thief.h"


bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setRunSpeed(75);
	setVaule(30);


	


	sprite = Sprite::createWithSpriteFrameName("lq.png");
	this->addChild(sprite);
	auto frameCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(5);
    char str[100] = {0};
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "lq%02d.png",i);
        auto frame = frameCache->getSpriteFrameByName(str);	
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	AnimationCache::getInstance()->addAnimation(animation, "runright1");
	AnimationCache::getInstance()->addAnimation(animation, "runleft1");




	Vector<SpriteFrame*> animFrames1(5);
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "lqd%02d.png",i);
        auto frame1 = frameCache->getSpriteFrameByName(str);	
        animFrames1.pushBack(frame1);
    }
	auto animationExplode = Animation::createWithSpriteFrames(animFrames1, 0.2f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode1");


	createAndSetHpBar();
	schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);




	scheduler1 = new Scheduler();  
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(scheduler1, 0, false);  
	CCActionManager* actionManager1 = new CCActionManager();  
    scheduler1->scheduleUpdateForTarget(actionManager1, 0, false);  
	sprite->setActionManager(actionManager1); 

	scheduleUpdate();


	return true;
}

void Thief::update(float dt)
{
	auto scale=scheduler1->getTimeScale();
	if( scale != 1 && slow == true )
	{
		unschedule(SEL_SCHEDULE(&Thief::removeSpeed));
		setSlow(false);
		scheduleOnce(SEL_SCHEDULE(&Thief::removeSpeed),1.0f);
	}
	else
		return;
}
void Thief::removeSpeed(float dt)
{
	scheduler1->setTimeScale(1);
	sprite->setColor(ccc3(255,255,255));
}

Thief* Thief::createThief(Vector<Node*> points, int hp)
{
	Thief *pRet = new Thief();
	if (pRet && pRet->init())
	{
		pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
		pRet->runFllowPoint();

		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void Thief::changeDirection(float dt)
{
	auto curr = currPoint();
	if( curr == NULL )
	{
		return;
	}


	
	if(curr->getPositionX() > sprite->getPosition().x )
	{
	    sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright1"))) ;
	}else{
	    sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft1"))  );
	}
}
void Thief::enemyExpload()
{
	hpBgSprite->setVisible(false);
	sprite->stopAllActions();
	unschedule(schedule_selector(Thief::changeDirection));
	sprite->setAnchorPoint(Point(0.5f, 0.25f));
	sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1"))
		,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
		, NULL));
	
}


bool Pirate::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setRunSpeed(50);
	setVaule(30);


	sprite = Sprite::createWithSpriteFrameName("kg.png");
	
	this->addChild(sprite);
	auto frameCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(5);
    char str[100] = {0};
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "kg%02d.png",i);
        auto frame = frameCache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);

	
	AnimationCache::getInstance()->addAnimation(animation, "runright2");
	AnimationCache::getInstance()->addAnimation(animation, "runleft2");




	Vector<SpriteFrame*> animFrames1(5);
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "kgd%02d.png",i);
        auto frame1 = frameCache->getSpriteFrameByName(str);
        animFrames1.pushBack(frame1);
    }
    auto animationExplode = Animation::createWithSpriteFrames(animFrames1, 0.2f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode2");


	


	createAndSetHpBar();
	schedule(schedule_selector(Pirate::changeDirection), 0.4f);


	
	scheduler1 = new CCScheduler();  
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(scheduler1, 0, false);  
	CCActionManager* actionManager1 = new CCActionManager();  
    scheduler1->scheduleUpdateForTarget(actionManager1, 0, false);  
	sprite->setActionManager(actionManager1); 
	scheduleUpdate();
	return true;
}

void Pirate::update(float dt)
{
	auto scale=scheduler1->getTimeScale();
	if( scale != 1 && slow == true )
	{
		unschedule(SEL_SCHEDULE(&Thief::removeSpeed));
		setSlow(false);
		scheduleOnce(SEL_SCHEDULE(&Thief::removeSpeed),1.0f);
	}
	else
		return;
}
void Pirate::removeSpeed(float dt)
{
	scheduler1->setTimeScale(1);
	sprite->setColor(ccc3(255,255,255));
}
Pirate* Pirate::createPirate(Vector<Node*> points, int hp)
{
	Pirate *pRet = new Pirate();
	if (pRet && pRet->init())
	{
		pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
		pRet->runFllowPoint();

		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
void Pirate::changeDirection(float dt)
{
	auto curr = currPoint();
	if( curr == NULL )
	{
		return;
	}
	if(curr->getPositionX() > sprite->getPosition().x )
	{
		sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright2"))) ;
	}else{
		sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft2"))  );
	}
}
void Pirate::enemyExpload()
{
	hpBgSprite->setVisible(false);
	sprite->stopAllActions();
	unschedule(schedule_selector(Pirate::changeDirection));
	sprite->setAnchorPoint(Point(0.5f, 0.25f));
	sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode2"))
		,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
		, NULL));

	
}


bool Bandit::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setRunSpeed(25);
	setVaule(30);
	
	
	sprite = Sprite::createWithSpriteFrameName("nt.png");
	this->addChild(sprite);
	auto frameCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames(5);
    char str[100] = {0};
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "nt%02d.png",i);
        auto frame = frameCache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);


	AnimationCache::getInstance()->addAnimation(animation, "runright3");
	AnimationCache::getInstance()->addAnimation(animation, "runleft3");


	Vector<SpriteFrame*> animFrames1(5);
	for(int i = 1; i < 5; i++)
    {
        sprintf(str, "ntd%02d.png",i);
        auto frame1 = frameCache->getSpriteFrameByName(str);
        animFrames1.pushBack(frame1);
    }
    auto animationExplode = Animation::createWithSpriteFrames(animFrames1, 0.2f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode3");

	
	createAndSetHpBar();
	schedule(schedule_selector(Bandit::changeDirection), 0.4f);



	scheduler1 = new CCScheduler();  
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(scheduler1, 0, false);  
	CCActionManager* actionManager1 = new CCActionManager();  
    scheduler1->scheduleUpdateForTarget(actionManager1, 0, false);  
	sprite->setActionManager(actionManager1); 
	scheduleUpdate();
	return true;
}
void Bandit::update(float dt)
{
	auto scale=scheduler1->getTimeScale();
	if( scale != 1 && slow == true )
	{
		unschedule(SEL_SCHEDULE(&Thief::removeSpeed));
		setSlow(false);
		scheduleOnce(SEL_SCHEDULE(&Thief::removeSpeed),1.0f);
	}
	else
		return;
}
void Bandit::removeSpeed(float dt)
{
	scheduler1->setTimeScale(1);
	sprite->setColor(ccc3(255,255,255));
}

Bandit* Bandit::createBandit(Vector<Node*> points, int hp)
{
	Bandit *pRet = new Bandit();
	if (pRet && pRet->init())
	{
		pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
		pRet->runFllowPoint();

		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
void Bandit::changeDirection(float dt)
{
	auto curr = currPoint();
	if( curr == NULL )
	{
		return;
	}
	if(curr->getPositionX() > sprite->getPosition().x )
	{
		sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright3"))) ;
	}else{
		sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft3"))  );
	}
}
void Bandit::enemyExpload()
{
	hpBgSprite->setVisible(false);
	sprite->stopAllActions();
	unschedule(schedule_selector(Bandit::changeDirection));
	sprite->setAnchorPoint(Point(0.5f, 0.25f));
	sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode3"))
	,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
		, NULL));

}

