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
protected:
	TMXTiledMap* m_map;
	Baby* m_baby;
	Vec2 m_enemyPosition;
	Node* m_pauseBtn;
	Node* m_backBtn;
	Node* m_replayBtn;
	Node* m_playBtn;
	Vector<Menu*> m_upgradeMenus;
	Vector<Menu*> m_menus;
	Vector<Enemy*> m_enemies;
	Vector<Tower*> m_towers;
	Vector<Bullet*> m_bullets;
	std::vector<Road> m_roads;
	PhysicsWorld* m_physicsWorld;
	LabelPrice* m_labelPrice;
	Label* m_labelCountDown;
	Label* m_labelSection; //1 ~ NUM_SECTIONS
	DrawNode* m_modalNode; //0 ~ NUM_STAGES
	SpriteBatchNode* m_towerbase;
	int m_money;
	int m_numRound;
	int m_curRound;
	int m_numPerRound;
	int m_curNumInRound;
	float m_timeBetweenRound;
	float m_elapsedTimeRound;
	bool m_isWaiting;
	bool m_isGameOver;

	int m_deltaMonsterGenerateTime;
	float m_deltaMonsterGenerateRate;
	float m_elapsedTimeMonster;
	int m_numMonster;
	int m_numLittleBoss;
	int m_numBigBoss;

	int m_id;
	int m_section;
	int m_countdown;

	EventListenerPhysicsContact* m_contactListener;
public:
	static cocos2d::Scene* createScene(int section, int id);
	virtual bool init();  
	static Game* create(int section, int id);
	Game(int section, int id);
	
	/*~Game();*/
	void onEnter() override;
	void onExit() override;
	virtual void loadData();
	void loadMenu();
	virtual void loadToolBar();
	void loadPeople();
	void loadTower();
	void loadRoadAndBarriers();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPhysicsCallback(cocos2d::Ref* pSender);
	void towerCreateCallback(cocos2d::Ref* pSender, int type, Sprite* towerbase, int menuId);
	void towerUpgradeCallback(cocos2d::Ref* pSender, int towerId);
	void towerDeleteCallback(cocos2d::Ref* pSender, int towerId, Sprite* towerbase);

	void countDown(float dt);
	virtual void addEnemy(float dt);
	void moveEnemy(float dt);
	void findEnemy(float dt);
	void deleteObject(float dt);
	void update(float dt);

	void gameOver(bool isWin);

	void setPhysicsWorld(PhysicsWorld* world);
	void addMoney(int money);
	Vector<Enemy*>& getEnemies();
	void addBullet(Bullet* bullet);
};
#endif
