#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;
#define VIRUS_TYPE_0 0
#define VIRUS_TYPE_1 1 
#define VIRUS_TYPE_2 2
#define VIRUS_TYPE_3 3
#define VIRUS_TYPE_4 4
#define VIRUS_TYPE_5 5

class Enemy : public Node{
private:
	int m_damage;
	int m_originSpeed;
	int m_curSpeed;
	int m_magicalDefence;
	int m_physicalDefebce;
	int m_type;
	ProgressTimer* m_pProTimer;
public:
	CREATE_FUNC(Enemy);
	Enemy();
	static Enemy* create(int type);
	Enemy(int type);
	virtual bool init() override;

	int getType();
	bool setType(int type);
	int getMaxHp();
	bool setMaxHp(int hp);
	int getOriginSpeed();
	bool setOriginSpeed(int ospeed);
	int getSpeed();
	bool setSpeed(int rspeed);
	
	float getHp();
	bool setHp(float hp);
	
};
#endif