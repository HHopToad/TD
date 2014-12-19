//
//  SuccessfulScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "SuccessfulScene.h"
#include "LevelInfoScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"  
#include "GameManager.h"

USING_NS_CC;
using namespace CocosDenshion; 

bool SuccessfulScene::init()  
{  
	if ( !Scene::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    GameManager* instance = GameManager::getInstance();
    instance->clear();
	//auto sprite = Sprite::create("winBg.png");
	auto sprite = Sprite::createWithSpriteFrameName("winBg.png");
    sprite->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(sprite, -1);

    // back
	/*Sprite *backItem1 = CCSprite::createWithSpriteFrameName("btnNext.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("btnBack.png");*/
	//add by  
	//Sprite *backItem1 = CCSprite::create("Next.png");
	//Sprite *backItem2 = CCSprite::create("gameBack.png");
	Sprite *nextItem1 = CCSprite::createWithSpriteFrameName("Next.png");
	Sprite *nextItem2 = CCSprite::createWithSpriteFrameName("Next1.png");
	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("gameBack.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("gameBack1.png");

	MenuItemSprite *pPauseItem1 = MenuItemSprite::create(nextItem1, nextItem2, CC_CALLBACK_1(SuccessfulScene::menuNextCallback, this));
    MenuItemSprite *pPauseItem2 = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(SuccessfulScene::menuCloseCallback, this));

    auto menu = Menu::create(pPauseItem1, pPauseItem2, NULL);
	menu->alignItemsHorizontally();

    menu->setPosition(Point(size.width / 2,size.height*4 / 10));  
    this->addChild(menu);  

    return true;  
}  

void SuccessfulScene::menuNextCallback(Ref* pSender)
{  
			int effect= UserDefault::getInstance()->getIntegerForKey("effect");
		if ( 1 == effect )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
		}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
	
	//add by  	,如果是第17关则显示通过庆祝信息
	auto fileName =  UserDefault::getInstance()->getStringForKey("nextLevelFile");
	if( fileName == "levelInfo_18.plist" )
	{

		Scene *scene = Scene::create();
		auto layer = PassScene::create();
		scene->addChild(layer);
		auto sence = TransitionFade::create(0.5, scene);
		Director::getInstance()->replaceScene(sence);
	}
	//add by  
	else 
	{
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0, LevelInfoScene::createScene()));  
	}
}

void SuccessfulScene::menuCloseCallback(Ref* pSender)
{  
			int effect= UserDefault::getInstance()->getIntegerForKey("effect");
		if ( 1 == effect )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
		}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, LevelScene::create()));
}