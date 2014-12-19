//
//  LevelInfoScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-21.
//
//
#include "SettingScene.h"

#include "PlayLayer.h"
#include "LevelScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 

#define STAR_NUMBER (3)

SettingScene::SettingScene()
	:info(NULL)
	,fileName("")
{
}

Scene* SettingScene::createScene()
{
	Scene *scene = Scene::create(); 
	SettingScene *layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}   

	instance = GameManager::getInstance();
	Size size1 = Director::getInstance()->getWinSize();



	//auto spritePanel = Sprite::create("start_level.png");
	auto spritePanel = Sprite::createWithSpriteFrameName("start_level.png");
	spritePanel->setPosition(Point(size1.width/2 , size1.height/2 ));
	Size size=spritePanel->getContentSize();
	this->addChild(spritePanel, -1);


	Sprite *start = CCSprite::createWithSpriteFrameName("gameBack.png");
	Sprite *start1 = CCSprite::createWithSpriteFrameName("gameBack1.png");
	//Sprite *start = CCSprite::create("gameStart.png");
	MenuItemSprite *startItem = MenuItemSprite::create(start, start1, CC_CALLBACK_1(SettingScene::menuBackCallback, this));
	auto menu = Menu::create(startItem, NULL);  
	menu->setPosition(Point(size.width / 2, size.height / 3));   
	spritePanel->addChild(menu); 


	//音效
	int i = UserDefault::getInstance()->getIntegerForKey("effect");
	MenuItemToggle* item1;
	if ( 0 == i)
	{
		 item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(SettingScene::menuEffectCallback, this),
			MenuItemFont::create( "Button: Off" ),
			MenuItemFont::create( "Button:  On"),
			nullptr );
	}
	else
	{
		 item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(SettingScene::menuEffectCallback, this),
			MenuItemFont::create( "Button: On" ),
			MenuItemFont::create( "Button: Off"),
			nullptr );
	}
	//背景音乐
	int x = UserDefault::getInstance()->getIntegerForKey("sound");
	MenuItemToggle* item2;
	if ( 0 == x)
	{

		item2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuSoundCallback, this),
			MenuItemFont::create( "Music: Off" ),
			MenuItemFont::create( "Music:  On" ),
			nullptr );
	}
	else
	{
		item2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuSoundCallback, this),
			MenuItemFont::create( "Music:  On" ),
			MenuItemFont::create( "Music: Off" ),
			nullptr );

	}
	//增加菜单
	Menu* menu1 = Menu::create(item1, item2, nullptr );    
	menu1->alignItemsVertically();
	menu1->setPosition(Point(size.width / 2, size.height* 2/ 3));
	spritePanel->addChild( menu1 );



	//Label *money ;
	//money = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", "NOT SUPPORT NOW");
	//money->setPosition(Point(size.width / 2, size.height*2 / 3));   
	//spritePanel->addChild(money);



	return true;
}


void SettingScene::menuBackCallback(Ref* pSender)
{
		int effect= UserDefault::getInstance()->getIntegerForKey("effect");
		if ( 1 == effect )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
		}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	//Director::getInstance()->replaceScene(TransitionFadeBL::create(0.0f, LevelScene::create()));

	Scene *scene = Scene::create();
	auto layer = UIScene::create();
	scene->addChild(layer);
	auto sence = TransitionFade::create(0.5, scene);
	Director::getInstance()->replaceScene(sence);

}

//add by  

void SettingScene::menuEffectCallback(Ref* pSender)
{
		int effect= UserDefault::getInstance()->getIntegerForKey("effect");
		if ( 1 == effect )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
		}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	//Director::getInstance()->replaceScene(TransitionFadeBL::create(0.0f, LevelScene::create()));

	//bool i = instance->getPlayEffect();
	int i= UserDefault::getInstance()->getIntegerForKey("effect");
	if( i == 0  )
	{ 
		UserDefault::getInstance()->setIntegerForKey("effect",1);
		//SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey("effect",0);
		//SimpleAudioEngine::getInstance()->stopBackgroundMusic();		
	}




}

void SettingScene::menuSoundCallback(Ref* pSender)
{
	
			int effect= UserDefault::getInstance()->getIntegerForKey("effect");
		if ( 1 == effect )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	
		}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	//Director::getInstance()->replaceScene(TransitionFadeBL::create(0.0f, LevelScene::create()));

	int i= UserDefault::getInstance()->getIntegerForKey("sound");
	if( i == 0  )
	{
		UserDefault::getInstance()->setIntegerForKey("sound",1);
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey("sound",0);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}

}