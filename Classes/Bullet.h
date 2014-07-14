#pragma once

#include"cocos2d.h"

USING_NS_CC;

class Bullet: public Node
{
private:
	int m_type;
	int m_level;
	int m_damage;
	PhysicsBody* m_body;
	bool m_isDie;
public:
	Bullet();
	bool initWithTypeAndLevel(int type, int level);
	static Bullet* create(int type, int level);

	int getType();
	void setType(int type);
	int getLevel();
	void setLevel(int level);
	int getDamage();
	void setDamage(int damage);
	Vec2 getBulletVelocity();
	void setBulletVelocity(Vec2 v);
	bool isDie();
	void setDie();
};

