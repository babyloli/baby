#ifndef __ENDLESS_GAME_SCENE_H__
#define __ENDLESS_GAME_SCENE_H__
#include "GameScene.h"
#include "Mouse.h"

class Endless : public Game{
#define INTERVAL_MOUSE 2.0f
public:
	static cocos2d::Scene* createScene();
	static Endless* create();
	virtual bool init() override;
	Endless();

	void loadData() override;
	void loadMap() override;
	void loadToolBar() override;
	void loadMousePosition();
	void loadEquipmentSlot() override;

	void addEnemy(float dt) override;
	void showMouse(float dt);

	bool mouseTouchCallback(Touch* touch, Event* event);
	void winGame() override;
	void failGame() override;

private:
	float m_elapsedTimeMouse;
	Vector<Mouse*> m_mouses;
	void onTouchPage(Object* pSender, TouchEventType type);
};

#endif