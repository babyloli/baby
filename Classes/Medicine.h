#pragma once
/************************************************************************/
/* There  are 6 props provide in game scene.                            */
/************************************************************************/


#include "Props.h"
#include "GameScene.h"
#include "Trap.h"
#include "Assistant.h"


//////////////////////////////////////////////////////////////////////////
// A prop to improve Baby's Hp
class PropsRestoreHp : public Props
{
private:
	Baby* m_bb;

public:
	 PropsRestoreHp(Baby* bb,Mode mode);
	~PropsRestoreHp();
	static PropsRestoreHp* createWithBaby(Baby* bb, Mode mode);

	void onEnter() override;
	bool touchCallback(Touch* touch, Event* event);
	void update(float dt);

};




//////////////////////////////////////////////////////////////////////////
// A prop to make all the enemies slow down in game scene
class PropsSlowdown : public Props
{
private:
	Vector<Enemy*> m_targets;
	bool m_isUsing;
public:
	PropsSlowdown(const Vector<Enemy*>& emenies, Mode mode);
	~PropsSlowdown();
	static PropsSlowdown* createWithTargets(const Vector<Enemy*>& emenies, Mode mode);
	
	void onEnter() override;
	bool touchCallback(Touch* touch, Event* event);
	void update(float dt);   

	void setSlowdownTargets(const Vector<Enemy*>& emenies);
	bool isAvailable() {return m_canBeUsed;};
	int getTargetsNumber()  {return m_targets.size();};
};



//////////////////////////////////////////////////////////////////////////
// A prop to provide a guard to protect baby
class PropsSafetyGuard : public Props
{
private:
	Baby* m_bb;
	Sprite* m_safetyG;
	Sprite* m_visiableG;
	int m_curState;
	int m_lastState;
	Action* m_state;

public:
	Rect m_safeGRect;

public:
	PropsSafetyGuard(Baby* bb, Mode mode);
	~PropsSafetyGuard();
	static PropsSafetyGuard* createWithBaby(Baby* bb, Mode mode);

	void onEnter() override;
	bool touchCallback(Touch* touch, Event* event);
	void update(float dt);

	bool isGuarding();
	int setCurState(int damage);
	Size getSafeGuradSize() {return m_safetyG->getContentSize();};
};



//////////////////////////////////////////////////////////////////////////
// A prop to place land mine
// When emenies step on land mine, the land mine would bomb. 
class PropsLandmine : public Props
{
private:
	Sprite* m_landmindcreate;
	Action* m_landmineAnimation;
	Vector<LandMine*> m_landmines;
	std::vector<Road> m_roads;

public:
	~PropsLandmine();
	PropsLandmine(const std::vector<Road>& roads, Mode mode);
	static PropsLandmine* createWithRoads(const std::vector<Road>& roads, Mode mode);

	void onEnter() override;
	bool touchBeginCallback(Touch* touch, Event* event);
	void touchMovedCallback(Touch* touch, Event* event);
	void touchEndenCallback(Touch* touch, Event* event);
	
	void update(float dt);

	Vector<LandMine*>& getLandmines();
	int getNumofLandmines();
};




//////////////////////////////////////////////////////////////////////////
// A prop to place trap
// A trap can make enemy stop in place.
// When the number of enemies stuck in the trap arrive at max number, the
// trap would be destroyed and enemies would be killed at the same time.
class PropsTrap : public Props
{
private:
	Sprite* m_trapcreate;
	//Action* m_trapAnimation;
	Vector<Trap*> m_traps;
	std::vector<Road> m_roads;

public:
	~PropsTrap();
	PropsTrap(const std::vector<Road>& roads,Mode mode);
	static PropsTrap* createWithRoads(const std::vector<Road>& roads, Mode mode);

	void onEnter() override;
	bool touchBeginCallback(Touch* touch, Event* event);
	void touchMovedCallback(Touch* touch, Event* event);
	void touchEndenCallback(Touch* touch, Event* event);

	void update(float dt);

	Vector<Trap*> getTraps();
	int getNumofTraps();
};



//////////////////////////////////////////////////////////////////////////
// A prop to provide an assistant to resist enemies
class PropsAssistGuard : public Props
{
private:
	Vec2 m_startPoint;
public:

	PropsAssistGuard(Vec2 start, Mode mode);
	~PropsAssistGuard();
	static PropsAssistGuard* create(Vec2 start, Mode mode);

	void onEnter()override;
	bool onTouchCallback(Touch* touch, Event* event);
	void update(float dt);
	void addAssistant();

};

