#include "Bullet.h"
#include "ResourceManager.h"

Bullet::Bullet()
{
}

bool Bullet::initWithTypeAndLevel(int type, int level)
{
	this->setTag(TAG_BULLET);
	m_type = type;
	m_level = level;
	Sprite* bullet = NULL;
	m_isDie = false;
	switch (type)
	{
	case TOWER_TYPE_0:
		switch (level)
		{
		case 1:
			bullet = Sprite::create("bullet_0_1.png");
<<<<<<< HEAD
			body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(body);
			//speed = 5;
			break;
		case 2:
			bullet = Sprite::create("bullet_0_2.png");
			body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(body);
			//speed = 6;
			break;
		case 3:
			bullet = Sprite::create("bullet_0_3.png");
			body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(body);
			//speed = 8;
			break;
		default:
=======
			m_body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(m_body);
			m_damage = DAMAGE_BULLET_0_1;
			m_speed = SPEED_BULLET_0;
			break;
		case 2:
			bullet = Sprite::create("bullet_0_2.png");
			m_body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(m_body);
			m_damage = SPEED_BULLET_0;
			m_speed = 2;
			break;
		case 3:
			bullet = Sprite::create("bullet_0_3.png");
			m_body = PhysicsBody::createCircle(16.0f);
			this->setPhysicsBody(m_body);
			m_damage = SPEED_BULLET_0;
			m_speed = 2;
>>>>>>> c3bb0836c44aea7a9d6fe286d95b8a4423bcdbd7
			break;
		}
	default:
		break;
	}
	m_body->setCategoryBitmask(CategoryBitMask_Bullet);
	m_body->setCollisionBitmask(CollisionBitMask_Bullet);
	m_body->setContactTestBitmask(ContactTestBitMask_Bullet);
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

bool Bullet::isDie(){
	return m_isDie;
}

void Bullet::setDie(){
	m_isDie = true;
}

float Bullet::getSpeed(){
	return m_speed;
}

void Bullet::setSpeed(float speed){
	m_speed = speed;
}