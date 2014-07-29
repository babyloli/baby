#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;

class Enemy : public Node{
protected:
	int m_curRound;
	int m_damage;
	int m_originSpeed;
	int m_curSpeed;
	int m_magicalDefence;
	int m_physicalDefence;
	int m_price;
	int m_type; //monster littleBoss bigBoss
	int m_id;
	std::string m_name;
	int m_direction;
	bool m_isDie;
	ProgressTimer* m_pProTimer;
	Sprite* m_enemy;
public:
	static Enemy* create(int id, int curRound);
	Enemy();
	bool initWithId(int id, int curRound);
	void initial(int id);

	std::string getName();
	bool setName(std::string name);
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
	int getPhysicalDefence();
	void setPhysicalDefence(int d);
	int getMagicalDefence();
	void setMagicalDefence(int d);
	int getDirection();
	void setDirection(int direction);
	int getPrice();
	void setPrice(int price);
	Sprite* getEnemy();
};
#endif