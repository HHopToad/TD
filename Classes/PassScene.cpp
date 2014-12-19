//
//  LevelInfoScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-21.
//  Modified by  on 14-12-12
//
#include "PassScene.h"

#include "PlayLayer.h"
#include "LevelScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 

#define STAR_NUMBER (3)

PassScene::PassScene()
:info(NULL)
,fileName("")
{
}

Scene* PassScene::createScene()
{
    Scene *scene = Scene::create(); 
    PassScene *layer = PassScene::create();
    scene->addChild(layer);
    return scene;
}

bool PassScene::init()
{
	if (!Layer::init())
	{
		return false;
	}   


	Size size1 = Director::getInstance()->getWinSize();

	

	//auto spritePanel = Sprite::create("start_level.png");
	auto spritePanel = Sprite::createWithSpriteFrameName("start_level.png");
    spritePanel->setPosition(Point(size1.width/2 , size1.height/2 ));
	Size size=spritePanel->getContentSize();
    this->addChild(spritePanel, -1);


    Sprite *start = CCSprite::createWithSpriteFrameName("gameBack.png");
	Sprite *start1 = CCSprite::createWithSpriteFrameName("gameBack1.png");
	//Sprite *start = CCSprite::create("gameStart.png");
    MenuItemSprite *startItem = MenuItemSprite::create(start, start1, CC_CALLBACK_1(PassScene::menuBackCallback, this));
    auto menu = Menu::create(startItem, NULL);  
	menu->setPosition(Point(size.width / 2, size.height / 3));   
	spritePanel->addChild(menu); 



	Sprite* spritewd = Sprite::create("pass.png");
    spritewd->setPosition(Point(size.width/2 , size.height*2/3 ));	
    spritePanel->addChild(spritewd);



    
   
	return true;
}


void PassScene::menuBackCallback(Ref* pSender)
{
	
			int effect= UserDefault::getInstance()->getIntegerForKey("effect");
		if ( 1 == effect )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
		}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.0f, LevelScene::create()));
}