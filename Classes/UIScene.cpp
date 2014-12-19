//
//  UIScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "UIScene.h"
#include "LevelScene.h"
#include "HelpScene.h"
#include "SettingScene.h"


#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 



USING_NS_CC;

Scene* UIScene::createScene()
{
	auto scene = Scene::create();
	auto layer = UIScene::create();

	scene->addChild(layer);
	return scene;
}

bool UIScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Size size = CCDirector::getInstance()->getWinSize();  

	//	auto sprite = Sprite::createWithSpriteFrameName("playbg.png");
	Sprite* sprite =Sprite::create("playbg.png");  
	sprite->setPosition(Point(size.width / 2,size.height / 2));  
	addChild(sprite, -1);

	auto titleSprite = Sprite::createWithSpriteFrameName("GameName.png");
	titleSprite->setPosition(Point(size.width / 2,size.height / 2));
	this->addChild(titleSprite);


	auto startItem = MenuItemImage::create(
		"start.png",  
		"start1.png",  
		CC_CALLBACK_1(UIScene::menuStartCallback, this));	
	startItem->setPosition(Point((size.width -  startItem->getContentSize().width)/ 4, size.height / 6));

	startItem->setAnchorPoint(Point(0, 0));


	auto settingItem = MenuItemImage::create(
		"setting.png",  
		"setting1.png",  
		CC_CALLBACK_1(UIScene::menuSettingCallback, this));
	settingItem->setPosition(Point((size.width -  startItem->getContentSize().width)*2/ 4, size.height / 6));

	settingItem->setAnchorPoint(Point(0, 0));

	auto infoItem = MenuItemImage::create(
		"info.png",  
		"info1.png",  
		CC_CALLBACK_1(UIScene::menuHelpCallback, this));
	infoItem->setPosition(Point((size.width -  startItem->getContentSize().width)*3/ 4, size.height / 6));





	infoItem->setAnchorPoint(Point(0, 0));
	//	settingItem->setTag(INFOICON_NUMBER);
	auto menu = Menu::create(startItem, settingItem,infoItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1); 



	return true;
}


RepeatForever* UIScene::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(-controlX, 0);
	bezier1.controlPoint_2 = Point(-controlX, controlY);
	bezier1.endPosition = Point(0, controlY);
	auto bezierBy1 = BezierBy::create(0.6f, bezier1);

	auto move1 = MoveBy::create(0.7f, Point(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	auto bezierBy2 = BezierBy::create(0.6f, bezier2);
	auto move2 = MoveBy::create(0.7f, Point(-w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}

void UIScene::menuStartCallback(Ref* pSender)
{

	int sound= UserDefault::getInstance()->getIntegerForKey("sound");

	if ( 0 == sound )
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	}else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/Orgrimmar.mp3").c_str(), true);

	}
	int effect= UserDefault::getInstance()->getIntegerForKey("effect");
	if ( 1 == effect )
	{
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);

	}



	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
}

void UIScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void UIScene::menuSettingCallback(Ref* pSender)
{
	int effect= UserDefault::getInstance()->getIntegerForKey("effect");
	if ( 1 == effect )
	{
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);

	}

	Scene *scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	auto sence = TransitionFade::create(0.5, scene);
	Director::getInstance()->replaceScene(sence);

}

void UIScene::menuHelpCallback(Ref* pSender)
{
	int effect= UserDefault::getInstance()->getIntegerForKey("effect");
	if ( 1 == effect )
	{
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);

	}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/Orgrimmar.mp3").c_str(), true);
	//Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, HelpScene::create()));

	Scene *scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	auto sence = TransitionFade::create(0.5, scene);
	Director::getInstance()->replaceScene(sence);

}