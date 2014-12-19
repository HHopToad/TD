//
//  LoadingResScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-6-8.
//
//
#include "LoadingResScene.h"
#include "UIScene.h"

#include "SimpleAudioEngine.h"  
using namespace CocosDenshion;  


LoadingResScene::LoadingResScene()
:numberOfLoadedRes(0)
,totalOfLoadedRes(15)
,progressBar(NULL)
{
}

Scene* LoadingResScene::createScene()
{
    Scene *scene = Scene::create(); 
    LoadingResScene *layer = LoadingResScene::create();
    scene->addChild(layer);

    return scene;
}

bool LoadingResScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    progressBar = addProgress();
	loadResources();
    schedule(schedule_selector(LoadingResScene::logic));

	return true;
}

void LoadingResScene::transitionScene()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, UIScene::createScene()));
}

ProgressTimer * LoadingResScene::addProgress()
{
	Size size = Director::getInstance()->getWinSize();	
	auto Loadbg = Sprite::create("Loadbg.png");
	Loadbg->setAnchorPoint(Point(0,0));
	auto progressBarBg = Sprite::create("Loading.png");
	progressBarBg->setPosition(Point(size.width / 2,  size.height / 9 ));  
	addChild(Loadbg);
	addChild(progressBarBg);

	progressBar = ProgressTimer::create(Sprite::create("Loading-BarFill.png"));
	progressBar->setType(ProgressTimer::Type::BAR);
	progressBar->setMidpoint(Point(0, 0.5f));
	progressBar->setBarChangeRate(Point(1, 0));
	progressBar->setPercentage(0);
	progressBar->setAnchorPoint(Point(0.5f, 0.5f));
    progressBar->setPosition(Point(progressBarBg->getContentSize().width / 2,  progressBarBg->getContentSize().height /2 ));  
	progressBarBg->addChild(progressBar);
    return progressBar;
}

void LoadingResScene::loadResources()
{
	//2014-11-22 modiby by hoptoad for new resources
	//music 10 
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str() );
    numberOfLoadedRes++;
	SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.mp3").c_str() );
    numberOfLoadedRes++;
	SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.wav" ).c_str());
    numberOfLoadedRes++;
	SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead1.mp3").c_str() );
    numberOfLoadedRes++;
	SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/enemy0_down.mp3").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/MainTheme.mp3").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/Orgrimmar.mp3").c_str() );
    numberOfLoadedRes++;
	SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/use_bomb.wav").c_str() );
    numberOfLoadedRes++;		
	   
  
	//add by 
	Director::getInstance()->getTextureCache()->addImageAsync("playbg.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	
	
	Director::getInstance()->getTextureCache()->addImageAsync("hero.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");



	 numberOfLoadedRes++;
	 Director::getInstance()->getTextureCache()->addImageAsync("pics.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pics.plist");
	 numberOfLoadedRes++;

}

void LoadingResScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    numberOfLoadedRes++;
}

void LoadingResScene::logic(float dt)
{
    float percent = (float)numberOfLoadedRes / (float)totalOfLoadedRes * 100;
    
    progressBar->setPercentage(percent);
    
    if (numberOfLoadedRes == totalOfLoadedRes)
    {
        transitionScene();

		


        SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/MainTheme.mp3").c_str(), true);
       SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.05f);
		//add by  根据设置进行音乐播放
		int sound= UserDefault::getInstance()->getIntegerForKey("sound");
		int effect= UserDefault::getInstance()->getIntegerForKey("effect");		
		if ( 0 == sound )
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

		}
		if ( 0 == effect )
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}
		
    }
}