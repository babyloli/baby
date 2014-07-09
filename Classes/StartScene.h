#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class Start : public cocos2d::Layer
{

public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Start);	
};
#endif