#ifndef __ENDLESS_GAME_SCENE_H__
#define __ENDLESS_GAME_SCENE_H__
#include "GameScene.h"

class Endless : public Game{
public:
	static cocos2d::Scene* createScene();
	static Endless* create();
	Endless();

	void loadData() override;
	void loadToolBar() override;

	void addEnemy(float dt) override;
};

#endif