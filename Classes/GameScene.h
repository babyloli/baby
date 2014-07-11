#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "Enemy.h"
#include "Road.h"
#include "Tower.h"
#include "Bullet.h"

USING_NS_CC;
class Game : public cocos2d::Layer
{
private:
	TMXTiledMap* m_map;
	Sprite* m_baby;
	Vec2 m_enemyPosition;
	Vector<Enemy*> m_enemies;
	std::vector<Road> m_roads;
	PhysicsWorld* m_physicsWorld;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	CREATE_FUNC(Game);

	void onEnter() override;

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPhysicsCallback(cocos2d::Ref* pSender);

	void addEnemy(float dt);
	void moveEnemy(float dt);

	void onTouchCreateTower(const std::vector<Touch*>& touches, Event* event);
	bool addTower(Vec2 location);

	void setPhysicsWorld(PhysicsWorld* world);
	Vector<Enemy*> getEnemies();
};
#endif