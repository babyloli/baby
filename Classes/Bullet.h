#pragma once

#include"cocos2d.h"

USING_NS_CC;

class Bullet: public Node
{
private:
	int m_type;
	int m_level;
	int m_damage;
	float m_speed;
	bool m_rotateEnable;
	bool m_isCollide;
	PhysicsBody* m_body;
	bool m_isDie;
public:
	Bullet();
	bool initWithSpriteFrameName(std::string spriteFrameNam, int type, int level, int damage, float speed, bool rotateEnable, bool isCollide, float density);
	static Bullet* create(std::string spriteFrameNam, int type, int level, int damage, float speed, bool rotateEnable, bool isCollide, float density);

	int getType();
	void setType(int type);
	inline int getLevel(){return m_level;}
	void setLevel(int level);
	int getDamage();
	void setDamage(int damage);
	Vec2 getBulletVelocity();
	void setBulletVelocity(Vec2 v);
	float getSpeed();
	void setSpeed(float speed);
	bool isDie();
	void setDie();
};

