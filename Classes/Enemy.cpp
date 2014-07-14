#include "Enemy.h"
#include "ResourceManager.h"
#include <math.h>
USING_NS_CC;

Enemy::Enemy()
	:m_damage(1)
	,m_originSpeed(3)
	,m_curSpeed(3)
	,m_magicalDefence(0)
	,m_physicalDefebce(0)
	,m_type(0)
	,m_pProTimer(NULL)
{
}

Enemy::Enemy(int type)
	:m_damage(1)
	,m_originSpeed(3)
	,m_curSpeed(3)
	,m_magicalDefence(0)
	,m_physicalDefebce(0)
	,m_type(type)
	,m_pProTimer(NULL)
{
}

Enemy* Enemy::create(int type){
	Enemy *pRet = new Enemy(type);
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool Enemy::init(){
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> walkFrames(4);
	switch (m_type)
	{
	case VIRUS_TYPE_0:
		enemy = Sprite::createWithSpriteFrameName("Albinism_right1.png");  
		  
        char str[100] = {0};  
        for (int i = 1; i <= 4; i++)  
        {  
            sprintf(str, "Albinism_right%1d.png",i);  
            auto frame = cache->getSpriteFrameByName( str );  
            //CCSpriteFrame *frame = cache->getSpriteFrameByName(CCString::createWithFormat("bear%1d.png", i)->getCString());  
            walkFrames.pushBack(frame);  
        }  
          
        // Creating animations  
        auto *walkAnimation = Animation::createWithSpriteFrames(walkFrames, 1.0f / 12.0f);  
        enemy->runAction( RepeatForever::create( Animate::create(walkAnimation) ) );  

//		this->setPhysicsBody(PhysicsBody::createCircle(32.0f, PhysicsMaterial(1.0f, 0.0f, 0.1f)));
		m_body = PhysicsBody::createCircle(16.0f);
		this->setPhysicsBody(m_body);
		m_curSpeed = m_originSpeed = 50;
		break;
	}
	if (!enemy)
		return false;
	this->addChild(enemy);
	
	auto hpBar = Sprite::create("Maxhpbar.png");
	if (!hpBar)
		return false;
	m_pProTimer = ProgressTimer::create(hpBar);
	m_pProTimer->setType(ProgressTimer::Type::BAR);
	m_pProTimer->setMidpoint(Vec2(0, 0.5f));
	m_pProTimer->setBarChangeRate(Vec2(1, 0));
	m_pProTimer->setPercentage(30);
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
		m_pProTimer->setPercentage(hp);
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
	return this->m_body->getVelocity();
}

void Enemy::setVelocity(Vec2 v){
	return this->m_body->setVelocity(v);
}


Sprite* Enemy::getEnemy(){
	return enemy;	
}