#include "Enemy.h"
#include "ResourceManager.h"
#include <math.h>
USING_NS_CC;

Enemy::Enemy()
	:m_pProTimer(NULL)
	,m_road(NULL)
{
}

Enemy* Enemy::create(int id, int curRound, bool mode){
	Enemy *pRet = new Enemy();
	if (pRet && pRet->initWithId(id, curRound, mode)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool Enemy::initWithId(int id, int curRound, bool mode){
	this->setTag(TAG_ENEMY);
	m_curRound = curRound;
	initial(id);
	if (m_type < 2)
		this->setZOrder(ZORDER_ENEMY);
	else
	{
		this->setZOrder(ZORDER_BIGBOSS);
	}
	m_hp = m_maxHp;
	m_direction = ROAD_NONE;
	m_isDie = false;
	m_mode = mode;
	m_sprite = Sprite::create();
	if (!m_sprite)
		return false;
	this->addChild(m_sprite);

	//attach physics body
//	auto body = PhysicsBody::createBox(Size(50, 50), PhysicsMaterial(0.5f, 0.0f, 0.5f));
	auto body = PhysicsBody::createCircle(20.0f, PhysicsMaterial(0.5f, 0.0f, 0.5f));
	if (m_type < 2)
	{
		body->setCategoryBitmask(CategoryBitMask_Enemy);
		body->setContactTestBitmask(ContactTestBitMask_Enemy);
		body->setCollisionBitmask(CollisionBitMask_Enemy);
	}
	else
	{
		body->setCategoryBitmask(CategoryBitMask_Boss);
		body->setContactTestBitmask(ContactTestBitMask_Boss);
		body->setCollisionBitmask(CollisionBitMask_Boss);
	}
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

void Enemy::initial(int id){
	HCSVFile* enemyData = ResourceManager::getInstance()->enemyData;	
	m_damage = std::atoi(enemyData->getData(id, 7));
	m_curSpeed = m_originSpeed = std::atoi(enemyData->getData(id, 6));
	int defenceUp = std::atoi(enemyData->getData(id, 9)) * (m_curRound - 1);
	m_physicalDefence = std::atoi(enemyData->getData(id, 4)) + defenceUp;
	m_magicalDefence = std::atoi(enemyData->getData(id, 5)) + defenceUp;
	m_price = std::atoi(enemyData->getData(id, 8));
	m_type = std::atoi(enemyData->getData(id, 1));
	m_id = id;
	m_name = enemyData->getData(id, 2);
	m_maxHp = std::atoi(enemyData->getData(id, 10));
	m_rate = m_maxHp / 100.0f;
}

void Enemy::killed(){
	m_sprite->runAction(Sequence::create(EaseSineIn::create(
		Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_KILLED)))
		, CallFuncN::create([this](Node* node){
			this->removeFromParent();
		}), NULL));
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
	return m_hp;
}

bool Enemy::setHp(float hp){
	if (m_pProTimer){
		if (hp > 0){
			m_hp = hp;
		}
		else
		{
			m_hp = 0;			
			m_isDie = true;
			m_curSpeed = 0;
		}
		m_pProTimer->setPercentage(m_hp / m_rate);
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

int Enemy::getPhysicalDefence(){
	return m_physicalDefence;
}

void Enemy::setPhysicalDefence(int d){
	m_physicalDefence = d;
}

int Enemy::getMagicalDefence(){
	return m_magicalDefence;
}

void Enemy::setMagicalDefence(int d){
	m_magicalDefence = d;
}

int Enemy::getDirection(){
	return m_direction;
}

void Enemy::setDirection(int direction){
	if (direction != m_direction){
		m_sprite->stopAllActions();
		//抽搐模式
		if (m_mode){
			if (m_type == 0){
				HCSVFile* enemyData = ResourceManager::getInstance()->enemyData;
				int num = std::atoi(ResourceManager::getInstance()->enemyDesc->getData(0, 4));
				int row = rand() % num;
				this->initial(row);
			}			
		}	

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
		m_sprite->runAction( RepeatForever::create(Animate::create(
			AnimationCache::getInstance()->getAnimation(m_name + dir_cur))));
		m_direction = direction;
	}
}

void Enemy::setRoad(Road* road)
{
	m_road = road;
}

int Enemy::getPrice(){
	return m_price;
}

void Enemy::setPrice(int price){
	m_price = price;
}

bool Enemy::getMode(){
	return m_mode;
}

void Enemy::setMode(bool b){
	m_mode = b;
}

int Enemy::getType(){
	return m_type;
}

Sprite* Enemy::getEnemy(){
	return m_sprite;	
}