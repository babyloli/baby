#pragma once
#include "Props.h"
#include "Baby.h"
#include "GameScene.h"

//////////////////////////////////////////////////////////////////////////
// A prop to improve Baby's Hp
class PropsRestoreHp : public Props
{
private:
	Baby* m_bb;
	//¾«Áé
	//¶¯»­
public:
	 PropsRestoreHp(Baby* bb);
	~PropsRestoreHp();
	static PropsRestoreHp* createWithBaby(Baby* bb);

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
public:
	PropsSlowdown();
	PropsSlowdown(const Vector<Enemy*>& emenies);
	~PropsSlowdown();
	static PropsSlowdown* create();
	static PropsSlowdown* createWithTargets(const Vector<Enemy*>& emenies);
	
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
	int m_curState;
public:
	Rect m_safeGRect;

public:
	PropsSafetyGuard(Baby* bb);
	~PropsSafetyGuard();
	static PropsSafetyGuard* createWithBaby(Baby* bb);

	void onEnter() override;
	bool touchCallback(Touch* touch, Event* event);
	void update(float dt);

	bool isGuarding();
	int setCurState(int damage);
	Size getSafeGuradSize() {return m_safetyG->getContentSize();};
};
