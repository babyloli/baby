#include "Bullet.h"
#include "ResourceManager.h"

Bullet::Bullet()
{
}

bool Bullet::initWithSpriteFrameName(std::string spriteFrameName, int type, int level, int damage, float speed, bool rotateEnable, bool isCollide, float density)
{
	this->setTag(TAG_BULLET);
	this->setZOrder(ZORDER_TOWER);
	m_type = type;
	m_level = level;
	m_damage = damage;
	m_speed = speed;
	m_rotateEnable = rotateEnable;
	m_isCollide = isCollide;
	m_isDie = false;
	m_body = PhysicsBody::createCircle(16.0f, cocos2d::PhysicsMaterial(density, 0.0, 1.0));
	this->setPhysicsBody(m_body);
	if (isCollide)
	{
		m_body->setCollisionBitmask(CollisionBitMask_Bullet);
		m_body->setCategoryBitmask(CategoryBitMask_Bullet);
	}
	else
	{
		m_body->setCollisionBitmask(CollisionBitMask_Bullet2);
		m_body->setCategoryBitmask(CategoryBitMask_Bullet2);
	}
	m_body->setContactTestBitmask(ContactTestBitMask_Bullet);
	Sprite* bullet = Sprite::createWithSpriteFrameName(spriteFrameName);
	if(!bullet)
	{
		return false;
	}
	if (level == 2)
		bullet->setScale(1.1f);
	else if (level == 3)
		bullet->setScale(1.2f);
	this->addChild(bullet);
	if (m_rotateEnable){
		auto action = RepeatForever::create(RotateBy::create(0.5f, 360.0f));
		bullet->runAction(action);
	}
	return true;
}

Bullet* Bullet::create(std::string spriteFrameName, int type, int level, int damage, float speed, bool rotateEnable, bool isCollide, float density)
{
	Bullet* bultemp = new Bullet();
	if(bultemp && bultemp->initWithSpriteFrameName(spriteFrameName, type, level, damage, speed, rotateEnable, isCollide, density))
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
void Bullet::setLevel(int level){
	this->m_level = level;
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