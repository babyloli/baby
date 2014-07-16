#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Enemy.h"
#include "Road.h"
#include "Tower.h"
#include "Baby.h"

USING_NS_CC;
class Game : public cocos2d::Layer
{
private:
	TMXTiledMap* m_map;
	Baby* m_baby;
	Vec2 m_enemyPosition;
	MenuItem* m_goItem;
	MenuItem* m_restartItem;
	MenuItem* m_backItem;
	Vector<Menu*> m_menus;
	Vector<Enemy*> m_enemies;
	Vector<Tower*> m_towers;
	Vector<Bullet*> m_bullets;
	std::vector<Road> m_roads;
	PhysicsWorld* m_physicsWorld;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	CREATE_FUNC(Game);

	void onEnter() override;

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPhysicsCallback(cocos2d::Ref* pSender);
	void menuStopCallback(cocos2d::Ref* pSender);
	void towerCreateCallback(cocos2d::Ref* pSender, int type, Sprite* towerbase);

	void addEnemy(float dt);
	void moveEnemy(float dt);
	void findEnemy(float dt);
	void deleteObject(float dt);
	void update(float dt);

	void setPhysicsWorld(PhysicsWorld* world);
	Vector<Enemy*>& getEnemies();
	void addBullet(Bullet* bullet);
};
#endif