#include "Enemy.h"
#include "ResourceManager.h"
#include <math.h>
USING_NS_CC;

Enemy::Enemy()
	:m_pProTimer(NULL)
{
}

Enemy* Enemy::create(std::string name){
	Enemy *pRet = new Enemy();
	if (pRet && pRet->initWithType(name)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool Enemy::initWithType(std::string name){
	this->setTag(TAG_ENEMY);
	m_name = name;
	m_isDie = false;
	m_direction = ROAD_NONE;
	m_enemy = Sprite::create();
	auto animationCache = AnimationCache::getInstance();
//	switch (m_name)
//	{
//	default:
//        m_enemy->runAction( RepeatForever::create(Animate::create(
//			animationCache->getAnimation(ResourceManager::ANIMATION_WALK_RIGHT_0))));
		m_damage = DAMAGE_ENEMY_0;
		m_curSpeed = m_originSpeed = SPEED_ENEMY_0;
		m_physicalDefence = DEFENCE_PHYSICS_0;
		m_magicalDefence = DEFENCE_MAGICAL_0;
		m_price = PRICE_ENEMY_0;
//		break;
//	}
	if (!m_enemy)
		return false;
	this->addChild(m_enemy);

	//attach physics body
	auto body = PhysicsBody::createBox(Size(50, 50), PhysicsMaterial(0.5f, 0.0f, 0.5f));
	body->setCategoryBitmask(CategoryBitMask_Enemy);
	body->setContactTestBitmask(ContactTestBitMask_Enemy);
	body->setCollisionBitmask(CollisionBitMask_Enemy);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	
	//创建血条
	auto hpBar = Sprite::createWithTexture(ResourceManager::getInstance()->hpBar);
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

std::string Enemy::getName(){
	return this->m_name;
}
bool Enemy::setName(std::string name){
	this->m_name=name;
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

int Enemy::getDirection(){
	return m_direction;
}

void Enemy::setDirection(int direction){
	if (direction != m_direction){
		m_enemy->stopAllActions();
// 		抽搐模式
// 				HCSVFile* enemyData = ResourceManager::getInstance()->enemyData;
// 				int selectMonster = rand()%(enemyData->getRows());
// 				std::string monsterName = enemyData->getData(selectMonster,2);
// 				m_name = monsterName;
// 				m_originSpeed = m_curSpeed = std::atoi(enemyData->getData(selectMonster,6));
// 				m_magicalDefence = std::atoi(enemyData->getData(selectMonster,5));
// 				m_physicalDefence = std::atoi(enemyData->getData(selectMonster,4));

		std::string dir_cur = "";
		switch (direction)
		{
		case ROAD_RIGHT:
			dir_cur = "right";
			break;
		case ROAD_UP:
			dir_cur = "up";
			break;
		case ROAD_LEFT:
			dir_cur = "left";
			break;
		case ROAD_DOWN:
			dir_cur = "down";
			break;
		}
		m_enemy->runAction( RepeatForever::create(Animate::create(
			AnimationCache::getInstance()->getAnimation(m_name + dir_cur))));
		m_direction = direction;
	}
}

int Enemy::getPrice(){
	return m_price;
}

void Enemy::setPrice(int price){
	m_price = price;
}

Sprite* Enemy::getEnemy(){
	return m_enemy;	
}