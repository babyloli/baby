#include "SetScene.h"

USING_NS_CC;

Scene* SetScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SetScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SetScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
// 	auto bg=Sprite::create("background1.psd_Psd.Dir/background1.png");
// 	bg->setAnchorPoint(Vec2(0,0));
// 	bg->setPosition(0,0);
// 	this->addChild(bg);
	auto UI =cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UI/SetUI0/SetUI_1.ExportJson");
	this->addChild(UI);
	auto UIimage=UI->getChildByTag(8);
	music = static_cast<cocos2d::ui::CheckBox*>(UIimage->getChildByTag(9));
	effect = static_cast<cocos2d::ui::CheckBox*>(UIimage->getChildByTag(10));
	back = static_cast<cocos2d::ui::Button*>(UIimage->getChildByTag(11));
	
	music->addEventListener(CC_CALLBACK_2(SetScene::selectedEvent1, this));
	music->setSelectedState(true);
	effect->addEventListener(CC_CALLBACK_2(SetScene::selectedEvent2, this));
	effect->setSelectedState(true);
	back->addTouchEventListener(CC_CALLBACK_2(SetScene::touchButton1, this));

    return true;
}


void SetScene::menuCloseCallback(Ref* pSender)
{
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
	 
void SetScene::touchButton1(Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	auto button = static_cast<cocos2d::ui::Button*>(pSender);

	int tag = button->getTag();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if(tag == 11)
		{
			auto s2 = HelloWorld::createScene();
			Director::getInstance()->replaceScene(s2);

		}
		break;		
	default:
		break;
	}
	
}

void  SetScene::selectedEvent1(Ref* pSender, cocos2d::ui::CheckBox::EventType type){
	switch(type){
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		break;
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		break;
	default:
		break;
	}
}
void SetScene::selectedEvent2(Ref* pSender, cocos2d::ui::CheckBox::EventType type){
	switch(type){
    case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
		break;
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
		break;
	default:
		break;
	}
}