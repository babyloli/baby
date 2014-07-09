#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "cocos2d.h"
USING_NS_CC;

class Enemy : public Node{
private:
	int damage;
	int MaxHp;
	int Hp;
	int OriSpeed;
	int rSpeed;
	int MagicalDefence;
	int PysicalDefebce;
	int type;
	TMXObjectGroup* objects; 
    Vector<Node*> pointsVector; 
	Sequence* run;
	int pointCount;
	Scheduler *sc1;
	ActionManager* am1;

public:
	Enemy();
	~Enemy();
	bool SetObjectGroup(TMXObjectGroup* obj);
	void InitWayPoints(float offx);
	Node* currPoint();
	Node* nextPoint();
	void runbyWay();
	bool changeSpeed(int rspeed);
	int getType();
	bool setType(int type);
	int getMaxHp();
	bool setMaxHp(int hp);
	int getHp();
    bool setHp(int hp);
	int getOriSpeed();
	bool setOriSpeed(int ospeed);
	int getSpeed();
	bool setSpeed(int rspeed);
	virtual bool init() override;
	CREATE_FUNC(Enemy);
	
};
#endif