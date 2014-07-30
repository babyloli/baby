#include "IHomeMenuScene.h"
#include "ISubUIScene.h"
#include "GameScene.h"

const int UI_BUTTON_PLAYGAME = 6;
const int UI_BUTTON_SETUP = 7;
const int UI_BUTTON_QUIT = 8; 


Scene* IHomeMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IHomeMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IHomeMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto bgImage = Sprite::create("UI/bg.png");
	bgImage->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(bgImage, -5);

	auto menuUI = GUIReader::getInstance()->widgetFromJsonFile("UI/start_1/start_1.ExportJson");
	this->addChild(menuUI);

	auto playGameButton = static_cast<Button*>(Helper::seekWidgetByTag(menuUI,UI_BUTTON_PLAYGAME));
	auto setupButton = static_cast<Button*>(Helper::seekWidgetByTag(menuUI,UI_BUTTON_SETUP));
	auto quitButton = static_cast<Button*>(Helper::seekWidgetByTag(menuUI,UI_BUTTON_QUIT));

	playGameButton->addTouchEventListener(this,toucheventselector(IHomeMenu::onTouchButton));
	setupButton->addTouchEventListener(this,toucheventselector(IHomeMenu::onTouchButton));
	quitButton->addTouchEventListener(this,toucheventselector(IHomeMenu::onTouchButton));
	
	///////////////////////////////////////////////////////////////////////////////////////
	// add an oryzae animation as a sprite of background
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("UI/sprite/hpSprite.plist");
	auto _bgSprite = SpriteBatchNode::create("UI/sprite/hpSprite.png");
	this->addChild(_bgSprite,-4);

	auto bgOryzae = Sprite::createWithSpriteFrameName("hpsprite1.png");
	Size winSize = Director::sharedDirector()->getWinSize();
	bgOryzae->setPosition(Vec2(200,350));
	_bgSprite->addChild(bgOryzae);

	Vector<SpriteFrame*> oryzaeFrames(4);
	for (int i = 1; i < 5; i++)
	{
		/*if ( (i%2) == 0)
		{
			auto frame = cache->getSpriteFrameByName("hpsprite2.png");
			oryzaeFrames.pushBack(frame);
		}
		else
		{*/
			auto frame = cache->getSpriteFrameByName(String::createWithFormat("hpsprite%ld.png",i)->getCString());
			oryzaeFrames.pushBack(frame);
		/*}*/
	}
	auto bgAnimation = Animation::createWithSpriteFrames(oryzaeFrames,1.0f/6.0f);
	bgOryzae->runAction(RepeatForever::create(Animate::create(bgAnimation)));
 
	auto userdefault=UserDefault::sharedUserDefault();
	if(!userdefault->getBoolForKey("isExisted")){
		userdefault->setBoolForKey("isExisted",true);
		userdefault->setIntegerForKey("Health",0);
		userdefault->setIntegerForKey("Section",4);
		userdefault->setIntegerForKey("Level",0);
		userdefault->setIntegerForKey("myGold",10000);
	    /*userdefault->setIntegerForKey("Item1",0);
     	userdefault->setIntegerForKey("Item2",0);
	    userdefault->setIntegerForKey("Item3",0);
     	userdefault->setIntegerForKey("Item4",0);
	    userdefault->setIntegerForKey("Item5",0);*/
		HCSVFile* data = ResourceManager::getInstance()->propsData;
		for (int i = 0; i < 6; i++)
		{
			userdefault->setIntegerForKey(data->getData(i,1),0);
		}
		
	}
    return true;
}

void IHomeMenu::onTouchButton(Object* pSender, TouchEventType type)
{
	int flag = (static_cast<Button*>(pSender))->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		switch (flag)
		{
		case UI_BUTTON_PLAYGAME:
			{
				auto modeSelector = IModeSelector::create();
				//modeSelector->registerWithTouchDispatcher();
				this->addChild(modeSelector);
				break;
			}
		case UI_BUTTON_SETUP:
			{
				auto musicSetter = IBGMusicSetter::create();
				this->addChild(musicSetter);
				break;
			}
		case UI_BUTTON_QUIT:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
			break;
		default:
			break;
		}
	default:
		break;
	}

}
