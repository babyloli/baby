#pragma once

#include"cocos2d.h"

USING_NS_CC;

#define BULLET_TYPE_0 0
#define BULLET_TYPE_1 1
#define BULLET_TYPE_2 2
#define BULLET_TYPE_3 3
#define BULLET_TYPE_4 4

class Bullet: public Sprite
{
private:
	int type;
	int level;
	int speed;
	PhysicsBody* body;

public:
	CREATE_FUNC(Bullet);
	Bullet(void);
	Bullet(int type,int level,int speed);
	~Bullet(void);
	virtual bool init();
	static Bullet* create(int type,int level,int speed);

	int getType();
	void setType(int type);
	int getLevel();
	void setLevel(int level);
	int getSpeed();
	void setSpeed(int speed);
	Vec2 getBulletVelocity();
	void setBulletVelocity(Vec2 v);
};

