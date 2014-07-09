#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class Game : public cocos2d::Layer
{
private:
	TMXTiledMap* m_map;
	Sprite* m_baby;
public:
    static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool init();  
	CREATE_FUNC(Game);	
};
#endif