#include "Assistant.h"
#include "ResourceManager.h"

Assistant::Assistant()
{
	m_pProTimer = NULL;
}

Assistant* Assistant::create()
{
	Assistant* assist = new Assistant();
	if(assist && assist->init()){
		assist->autorelease();
		return assist;
	}
	CC_SAFE_DELETE(assist);
	return nullptr;
}

bool Assistant::init()
{
	this->setZOrder(ZORDER_BIGBOSS);
	m_direction = ROAD_NONE;

	//���ݵȼ�ȷ��������,�ٶȵ�
	int health = UserDefault::sharedUserDefault()->getIntegerForKey("Health");
	m_curSpeed = 40;//û���õ�
	m_physicalDefence = 2 * health;
	m_magicalDefence = 2 * health;
	m_isDie = false;

	m_assistant = Sprite::create();
	if (!m_assistant){
		return false;
	}
	auto* action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_ASSISTANT)));
	m_assistant->runAction(action);
	this->addChild(m_assistant);


	auto body = PhysicsBody::createBox(Size(40, 40), PhysicsMaterial(0.5f, 0.0f, 0.5f));
	body->setCategoryBitmask(CategoryBitMask_Assist);
	body->setContactTestBitmask(ContactTestBitMask_Assist);
	body->setCollisionBitmask(CollisionBitMask_Assist);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	auto hpBar = Sprite::create("images/enemy/hpbar.png");
	if(!hpBar)
		return false;
	m_pProTimer = ProgressTimer::create(hpBar);
	m_pProTimer->setType(ProgressTimer::Type::BAR);
	m_pProTimer->setMidpoint(Vec2(0,0.5f));
	m_pProTimer->setBarChangeRate(Vec2(1,0));
	m_pProTimer->setPercentage(100);
	m_pProTimer->setScale(0.08f);
	m_pProTimer->setPosition(0,45);
	this->addChild(m_pProTimer,ZORDER_ENEMY);

	return true;
}


//----------------------gets/sets--------------
int Assistant::getSpeed()
{
	return m_curSpeed;
}

bool Assistant::setSpeed(int rspeed)
{
	this->m_curSpeed = rspeed;
	return true;
}

bool Assistant::isDie()
{
	return m_isDie;
}

void Assistant::setDie(bool b)
{
	m_isDie = b;
}

int Assistant::getDirection()
{
	return m_direction;
}

void Assistant::setDirection(int direction)
{
	m_direction = direction;
}

Vec2 Assistant::getVelocity()
{
	return this->getPhysicsBody()->getVelocity();
}

void Assistant::setVelocity(Vec2 v)
{
	return this->getPhysicsBody()->setVelocity(v);
}

float Assistant::getHp()
{
	if (m_pProTimer){
		return m_pProTimer->getPercentage();
	}
	return 0;
}

bool Assistant::setHp(float hp)
{
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

int Assistant::getPhysicalDefence()
{
	return m_physicalDefence;
}

int Assistant::getMagicalDefence()
{
	return m_magicalDefence;
}