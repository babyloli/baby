#include "Enemy.h"
#include "ResourceManager.h"
#include <math.h>
USING_NS_CC;

Enemy::Enemy()
	:m_pProTimer(NULL)
{
}

Enemy* Enemy::create(int type){
	Enemy *pRet = new Enemy();
	if (pRet && pRet->initWithType(type)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool Enemy::initWithType(int type){
	this->setTag(TAG_ENEMY);
	m_type = type;
	m_isDie = false;
	m_enemy = Sprite::create();
	auto animationCache = AnimationCache::getInstance();
	switch (m_type)
	{
	case VIRUS_TYPE_0:
        Animation* walkAnimation = animationCache->animationByName(ResourceManager::ANIMATION_WALK_0);
        m_enemy->runAction( RepeatForever::create(Animate::create(walkAnimation)));
		m_curSpeed = m_originSpeed = 50;
		break;
	}
	if (!m_enemy)
		return false;
	this->addChild(m_enemy);

	//attach physics body
	auto body = PhysicsBody::createBox(Size(32, 32), PhysicsMaterial(0.5f, 0.0f, 0.5f));
	body->setCategoryBitmask(CategoryBitMask_Enemy);
	body->setContactTestBitmask(ContactTestBitMask_Enemy);
	body->setCollisionBitmask(CollisionBitMask_Enemy);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	
	//´´½¨ÑªÌõ
	auto hpBar = Sprite::create("Maxhpbar.png");
	if (!hpBar)
		return false;
	m_pProTimer = ProgressTimer::create(hpBar);
	m_pProTimer->setType(ProgressTimer::Type::BAR);
	m_pProTimer->setMidpoint(Vec2(0, 0.5f));
	m_pProTimer->setBarChangeRate(Vec2(1, 0));
	m_pProTimer->setPercentage(100);
	m_pProTimer->setScale(0.06f);
	m_pProTimer->setPosition(0,25);
	this->addChild(m_pProTimer);

	return true;
}

//----------------get/set-----------------------

int Enemy::getType(){
	return this->m_type;
}
bool Enemy::setType(int type){
	this->m_type=type;
	return true;
}

float Enemy::getHp(){
	if (m_pProTimer){
		return m_pProTimer->getPercentage();
	}
	return 0;
}

bool Enemy::setHp(float hp){
	if (m_pProTimer){
		if (hp > 0)
			m_pProTimer->setPercentage(hp);
		else
		{
			m_pProTimer->setPercentage(0);
			m_isDie = true;
		}
		return true;
	}
	return false;
}
int Enemy::getOriginSpeed(){
	return this->m_originSpeed;
}
bool Enemy::setOriginSpeed(int ospeed){
	this->m_originSpeed = ospeed;
	return true;
}
int Enemy::getSpeed(){
	return this->m_curSpeed;
}
bool Enemy::setSpeed(int rspeed){
	this->m_curSpeed = rspeed;
	return true;
}

Vec2 Enemy::getVelocity(){
	return this->getPhysicsBody()->getVelocity();
}

void Enemy::setVelocity(Vec2 v){
	return this->getPhysicsBody()->setVelocity(v);
}

bool Enemy::isDie(){
	return m_isDie;
}

void Enemy::setDie(bool d){
	m_isDie = d;
}

int Enemy::getDamage(){
	return m_damage;
}

void Enemy::setDamage(int damage){
	m_damage = damage;
}

Sprite* Enemy::getEnemy(){
	return m_enemy;	
}