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
#include "LabelPrice.h"

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
	Vector<Menu*> m_upgradeMenus;
	Vector<Menu*> m_menus;
	Vector<Enemy*> m_enemies;
	Vector<Tower*> m_towers;
	Vector<Bullet*> m_bullets;
	std::vector<Road> m_roads;
	PhysicsWorld* m_physicsWorld;
	LabelPrice* m_labelPrice;
	int m_money;
	int m_numRound;
	int m_curRound;
	int m_numPerRound;
	int m_curNumInRound;
	float m_timeBetweenRound;
	float m_elapsedTimeRound;
	bool m_isWaiting;

	int m_deltaMonsterDefence;
	int m_deltaMonsterGenerateTime;
	float m_deltaMonsterGenerateRate;
	float m_elapsedTimeMonster;
	int m_numMonster;

	int m_deltaLittleBossDefence;
	int m_numLittleBoss;

	int m_bigBossAttack;
	int m_numBigBoss;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(Game);

	void onEnter() override;
	void loadData();
	void loadMenu();
	void loadPeople();
	void loadTower();
	void loadRoadAndBarriers();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPhysicsCallback(cocos2d::Ref* pSender);
	void towerCreateCallback(cocos2d::Ref* pSender, int type, Sprite* towerbase, int menuId);
	void towerUpgradeCallback(cocos2d::Ref* pSender, int towerId);
	void towerDeleteCallback(cocos2d::Ref* pSender, int towerId, Sprite* towerbase);

	void addEnemy(float dt);
	void moveEnemy(float dt);
	void findEnemy(float dt);
	void deleteObject(float dt);
	void update(float dt);

	void setPhysicsWorld(PhysicsWorld* world);
	void addMoney(int money);
	Vector<Enemy*>& getEnemies();
	void addBullet(Bullet* bullet);
};
#endif