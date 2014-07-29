#ifndef __IHOMEMENU_SCENE_H__
#define __IHOMEMENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ResourceManager.h"
using namespace cocostudio;
using namespace cocos2d::ui;

USING_NS_CC;
USING_NS_CC_EXT;

class IHomeMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	// a selector callback
	void onTouchButton(Object* pSender, TouchEventType type);
	void onTouchShopButton(Object* pSender, TouchEventType type);
	//void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(IHomeMenu);
};



#endif 
