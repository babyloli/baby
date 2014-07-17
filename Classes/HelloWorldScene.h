#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "SetScene.h"

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include <iostream>
#include "SimpleAudioEngine.h"

USING_NS_CC;

class HelloWorld : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void touchButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    CREATE_FUNC(HelloWorld);
	
};

#endif // __HELLOWORLD_SCENE_H__
