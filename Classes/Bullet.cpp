#include "Bullet.h"
#include "ResourceManager.h"

Bullet::Bullet()
{
}

bool Bullet::initWithTypeAndLevel(int type, int level)
{
	m_type = type;
	m_level = level;
	Sprite* bullet = NULL;
	switch (type)
	{
	case TOWER_TYPE_0:
		switch (level)
		{
		case 1:
			bullet = Sprite::create("bullet_0_1.png");
			m_body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(m_body);
			m_damage = 50;
			break;
		case 2:
			bullet = Sprite::create("bullet_0_2.png");
			m_body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(m_body);
			m_damage = 60;
			break;
		case 3:
			bullet = Sprite::create("bullet_0_3.png");
			m_body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(m_body);
			m_damage = 80;
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
Bullet* Bullet::create(int type, int level)
{
	Bullet* bultemp = new Bullet();
	if(bultemp && bultemp->initWithTypeAndLevel(type, level))
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
	return m_type;
}
void Bullet::setType(int type)
{
	this->m_type = type;
}
int Bullet::getLevel()
{
	return m_level;
}
void Bullet::setLevel(int level)
{
	level++;
}
int Bullet::getDamage()
{
	return m_damage;
}
void Bullet::setDamage(int damage)
{
	this->m_damage = damage;
}

Vec2 Bullet::getBulletVelocity()
{
	return this->m_body->getVelocity();
}
void Bullet::setBulletVelocity(Vec2 v)
{
	this->m_body->setVelocity(v);
}