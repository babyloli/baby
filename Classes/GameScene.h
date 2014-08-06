#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "IHomeMenuScene.h"
#include "Enemy.h"
#include "Road.h"
#include "Tower.h"
#include "Baby.h"
#include "LabelPrice.h"
#include "Medicine.h"
#include "Trap.h"
#include "Assistant.h"
 
USING_NS_CC;
class Game : public cocos2d::Layer
{
#define objPosX(obj) obj.at("x").asInt() + obj.at("width").asInt()/2
#define objPosY(obj) obj.at("y").asInt() + obj.at("height").asInt()/2
#define objWidth(obj) obj.at("width").asFloat()
#define objHeight(obj) obj.at("height").asFloat()
protected:
	TMXTiledMap* m_map;
	Baby* m_baby;
	Rect m_enemyRect;
	Vec2 m_enemyPosition;
	Vec2 m_assistPosition;
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
	int m_bossRound;
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
	Vector<FiniteTimeAction*> m_actionsAssistant;
	Vector<Assistant*> m_assistants;
	
public:
	static cocos2d::Scene* createScene(int section, int id);
	virtual bool init() override;  
	static Game* create(int section, int id);
	Game(int section, int id);

	void onEnter() override;
	void onExit() override;
	virtual void loadData();
	virtual void loadMap();
	void loadMenu();
	virtual void loadToolBar();
	void loadPeople();
	void loadTower();
	void loadRoadAndBarriers();
	virtual void loadEquipmentSlot();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPhysicsCallback(cocos2d::Ref* pSender);
	void towerCreateCallback(cocos2d::Ref* pSender, int type, Sprite* towerbase, int menuId);
	void towerUpgradeCallback(cocos2d::Ref* pSender, int towerId);
	void towerDeleteCallback(cocos2d::Ref* pSender, int towerId, Sprite* towerbase);

	void countDown(float dt);
	virtual void addEnemy(float dt);
	void moveAssistant(float dt);
	void moveEnemy(float dt);
	void findEnemy(float dt);
	void deleteObject(float dt);
	void meetTraps(float dt);
	void update(float dt);

	void gameOver(bool isWin);
	virtual void winGame();
	virtual void failGame();

	void setPhysicsWorld(PhysicsWorld* world);
	void addMoney(int money);
	Vector<Enemy*>& getEnemies();
	void addBullet(Bullet* bullet);
	Vector<FiniteTimeAction*>& getActionsAssistant();
	Vector<Assistant*>& getAssistants();
private:
	void onTouchWinPage(Object* pSender, TouchEventType type);
	void onTouchFailPage(Object* pSender, TouchEventType type);
};
#endif
