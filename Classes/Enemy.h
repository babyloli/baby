#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Road.h"
USING_NS_CC;

class Enemy : public Node{
protected:
	bool m_mode;	//抽搐模式
	int m_curRound;
	int m_damage;
	int m_originSpeed;
	int m_curSpeed;
	int m_magicalDefence;
	int m_physicalDefence;
	int m_price;
	int m_type; //monster littleBoss bigBoss
	int m_id;
	int m_hp;
	int m_maxHp;
	float m_rate;
	std::string m_name;
	int m_direction;
	bool m_isDie;
	ProgressTimer* m_pProTimer;
	Sprite* m_sprite;
	Road* m_road;	//当前所在的道路
public:
	static Enemy* create(int id, int curRound, bool mode);
	Enemy();
	bool initWithId(int id, int curRound, bool mode);
	void initial(int id);

	void killed();

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
	Road* getRoad(){return m_road;}
	void setRoad(Road* road);
	int getPrice();
	void setPrice(int price);
	bool getMode();
	void setMode(bool b);
	virtual Sprite* getEnemy();
};
#endif