#include "AppDelegate.h"
#include "LoadingResScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("TD Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    //director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    glview->setDesignResolutionSize(960.0f, 640.0f, ResolutionPolicy::FIXED_HEIGHT);
    std::vector<std::string> searchPath;
    searchPath.push_back("height_864");
    CCFileUtils::getInstance()->setSearchPaths(searchPath);
    director->setContentScaleFactor(864.0f / 640.0f);
    
    // create a scene. it's an autorelease object
    auto scene = LoadingResScene::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
	//add by 
	Director::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    //add by 
	//
	Director::sharedDirector()->resume();

	int sound= UserDefault::getInstance()->getIntegerForKey("sound");
	if ( 1 == sound )
	{
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	}
	//SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
