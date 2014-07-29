#ifndef __TRAP_H__
#define __TRAP_H__

#include "cocos2d.h"
#include "ResourceManager.h"
#include "Enemy.h"

USING_NS_CC;

class LandMine : public Node
{
protected:
	Sprite* m_sprite;
	Action* m_action;
private:
	bool m_isbomb;
public:
	Rect m_position;
	LandMine();
	CREATE_FUNC(LandMine);
	virtual bool init();
	
	//void onEnter() override;
	//void waitForTargets();  //�ȴ����޵Ķ���
	void bomb();  // ����ǰ���ű�ը����
	bool isBomb() {return m_isbomb;};
};


 
class Trap : public LandMine
{
private:
	int m_curState;
	int m_maxState;
	Vector<Enemy*> m_targets;
	//float m_currTime;
	//float m_holdTime;
public:
	Trap(int maxState);
	static Trap* createWithmaxState(int maxstate);
	virtual bool init() override;

	void catchEnemy(Enemy* enemy);
	void destory(); //���ٶ���
	bool isContainable();
	Vector<Enemy*>& getTargets(); 

};




#endif

