#ifndef __ASSISTANT_H__
#define __ASSISTANT_H__
#include "cocos2d.h"
USING_NS_CC;
class Assistant : public Node
{
private:
	int m_curSpeed;
	int m_magicalDefence;
	int m_physicalDefence;
	//std::string m_name;
	int m_direction;
	bool m_isDie;
	ProgressTimer* m_pProTimer;
	Sprite* m_assistant;
public:
	Assistant();
	static Assistant* create();
	virtual bool init();

	int getSpeed();
	bool setSpeed(int rspeed);
	bool isDie();
	void setDie(bool b);
	int getDirection();
	void setDirection(int direction);
	Vec2 getVelocity();
	void setVelocity(Vec2 v);

	float getHp();
	bool setHp(float hp);
	int getDamage();
	void setDamage(int damage);
	int getPhysicalDefence();
	int getMagicalDefence();
};



#endif