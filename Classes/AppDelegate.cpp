#include "AppDelegate.h"
<<<<<<< HEAD
#include "ResourceManager.h"
#include "IHomeMenuScene.h"
=======
#include "IHomeMenuScene.h"

>>>>>>> 32d363213ca9727bfc70575e9ab53ededc6d4e4f

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		glview->setFrameSize(1280,720);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);
	
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/bgm.mp3",true);
   	
	// set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = IHomeMenu::createScene();
<<<<<<< HEAD
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3");
=======

>>>>>>> 32d363213ca9727bfc70575e9ab53ededc6d4e4f
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
