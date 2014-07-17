#ifndef __SET_SCENE_H__
#define __SET_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class SetScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void menuCloseCallback(cocos2d::Ref* pSender);
	void touchButton1(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(SetScene);
	cocos2d::ui::CheckBox* music;
	cocos2d::ui::CheckBox* effect;
	cocos2d::ui::Button* back;
	void selectedEvent1(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	void selectedEvent2(Ref* pSender, cocos2d::ui::CheckBox::EventType type);

};


#endif