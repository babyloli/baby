#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;

class Enemy : public Node{
private:
	int m_damage;
	int m_originSpeed;
	int m_curSpeed;
	int m_magicalDefence;
	int m_physicalDefebce;
	int m_type;
	bool m_isDie;
	ProgressTimer* m_pProTimer;
	Sprite* m_enemy;
public:
	static Enemy* create(int type);
	Enemy();
	bool initWithType(int type);

	int getType();
	bool setType(int type);
	int getMaxHp();
	bool setMaxHp(int hp);
	int getOriginSpeed();
	bool setOriginSpeed(int ospeed);
	int getSpeed();
	bool setSpeed(int rspeed);
	Vec2 getVelocity();
	void setVelocity(Vec2 v);
	bool isDie();
	void setDie(bool d);
	float getHp();
	bool setHp(float hp);
	int getDamage();
	void setDamage(int damage);
	Sprite* getEnemy();
};
#endif