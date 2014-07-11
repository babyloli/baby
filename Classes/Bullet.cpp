#include "Bullet.h"


Bullet::Bullet()
{
	this->type = 0;
	this->level = 1;
	this->speed = 5;
	this->body = NULL;
}
Bullet::Bullet(int type,int level, int speed)
{
	this->type = type;
	this->level = level;
	this->speed = speed; 
	this->body = NULL;
}
Bullet::~Bullet(void)
{
}


bool Bullet::init()
{
	Sprite* bullet = NULL;
	switch (type)
	{
	case BULLET_TYPE_0:
		switch (level)
		{
		case 1:
			bullet = Sprite::create("bullet_0_1.png");
			body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(body);
			speed = 5;
			break;
		case 2:
			bullet = Sprite::create("bullet_0_2.png");
			body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(body);
			speed = 6;
			break;
		case 3:
			bullet = Sprite::create("bullet_0_3.png");
			body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(body);
			speed = 8;
			break;
		default:
			break;
		}
	default:
		break;
	}
	if(!bullet)
	{
		return false;
	}
	this->addChild(bullet);

	return true;
}
Bullet* Bullet::create(int type,int level,int speed)
{
	Bullet* bultemp = new Bullet(type,level,speed);
	if(bultemp && bultemp->init())
	{
		bultemp->autorelease();
		return bultemp;
	}
	else
	{
		delete bultemp;
		bultemp = NULL;
		return NULL;
	}
}




////////////////////////////////////////////////////////
int Bullet::getType()
{
	return type;
}
void Bullet::setType(int type)
{
	this->type = type;
}
int Bullet::getLevel()
{
	return level;
}
void Bullet::setLevel(int level)
{
	level++;
}
int Bullet::getSpeed()
{
	return speed;
}
void Bullet::setSpeed(int speed)
{
	this->speed = speed;
}

Vec2 Bullet::getBulletVelocity()
{
	return this->body->getVelocity();
}
void Bullet::setBulletVelocity(Vec2 v)
{
	this->body->setVelocity(v);
}