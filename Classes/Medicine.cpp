#include "Medicine.h"


//////////////////////////////////////////////////////////////////////////
PropsRestoreHp::PropsRestoreHp(Baby* bb)
{
	m_id = 0;
	m_bb = bb;
	m_sprite = Sprite::create("images/props/1.png");
	this->addChild(m_sprite);
}

PropsRestoreHp::~PropsRestoreHp()
{
}

PropsRestoreHp* PropsRestoreHp::createWithBaby(Baby* bb)
{
	PropsRestoreHp* prop = new (std::nothrow)PropsRestoreHp(bb);
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}


void PropsRestoreHp::onEnter()
{
	Node::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PropsRestoreHp::touchCallback,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

bool PropsRestoreHp::touchCallback(Touch* touch, Event* event)
{

	if (m_position.containsPoint(touch->getLocation()) && m_canBeUsed){
		m_bb->restoreHealth();
		m_canBeUsed = false;
		usePropsAndUpdate();
		return true;
	}
	return false;
}

void  PropsRestoreHp::update(float dt)
{
	if(m_canBeUsed){
		return;
	}
	else{
		if(m_usedTime >= m_cooldownTime){
			m_usedTime = 0.0;
			m_canBeUsed = true;
			m_pCdTimer->setVisible(false);
			m_pCdTimer->setPercentage(100);
		}
		else{
			m_usedTime += dt;
			m_pCdTimer->setPercentage( (m_cooldownTime - m_usedTime) / m_cooldownTime * 100 );
		}
	}
}





//////////////////////////////////////////////////////////////////////////
PropsSlowdown::PropsSlowdown()
{
	m_id = 1;
	m_sprite = Sprite::create("images/props/2.png");
	this->addChild(m_sprite);
}

PropsSlowdown::PropsSlowdown(const Vector<Enemy*>& emenies)
{
	m_id = 1;
	m_targets = emenies;
	if (m_targets.size() == 0){
		CCLOG("0");
	}
	m_sprite = Sprite::create("images/props/2.png");
	this->addChild(m_sprite);
}

PropsSlowdown::~PropsSlowdown()
{
}

PropsSlowdown* PropsSlowdown::create()
{
	PropsSlowdown* prop = new (std::nothrow)PropsSlowdown();
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}

PropsSlowdown* PropsSlowdown::createWithTargets(const Vector<Enemy*>& emenies)
{
	PropsSlowdown* prop = new PropsSlowdown(emenies);
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}


void PropsSlowdown::onEnter()
{
	Node::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PropsSlowdown::touchCallback,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

bool PropsSlowdown::touchCallback(Touch* touch, Event* event)
{
	if (m_position.containsPoint(touch->getLocation()) && m_canBeUsed){
		m_canBeUsed = false;
		usePropsAndUpdate();

		for(int i = 0; i < m_targets.size(); i++)
		{
			auto enemy = m_targets.at(i);
			enemy->setSpeed(enemy->getSpeed() / 20);
		}
		return true;
	}
	return false;
}

void PropsSlowdown::update(float dt)
{
	if(m_canBeUsed){
		/////////
		return;
	}
	else{
		if(m_usedTime >= m_cooldownTime){
			m_pCdTimer->setVisible(false);
			m_pCdTimer->setPercentage(100);
			m_canBeUsed = true;
			m_usedTime = 0.0;
		}
		else{
			m_usedTime += dt;
			m_pCdTimer->setPercentage((m_cooldownTime - m_usedTime) / m_cooldownTime * 100);
			if(m_usedTime >= m_holdTime){
				for(int i = 0; i < m_targets.size(); i++)
				{
					Enemy* enemy = m_targets.at(i);
					enemy->setSpeed(enemy->getOriginSpeed());
					m_targets.erase(i);
				}
			}
		}
	}
}

void PropsSlowdown::setSlowdownTargets(const Vector<Enemy*>& emenies)
{
	for (int i=0; i<emenies.size(); i++)
	{
			m_targets.pushBack(emenies.at(i));
	}
}









//////////////////////////////////////////////////////////////////////////
PropsSafetyGuard::PropsSafetyGuard(Baby* bb)
{
	m_id = 2;
	m_bb = bb;
	m_sprite = Sprite::create("images/props/3.png");
	this->addChild(m_sprite);

	m_safetyG = Sprite::create("images/props/SafeGuard.png");
	m_safetyG->setPosition(Vec2(0,0));
	bb->addChild(m_safetyG,7);
	m_safetyG->setVisible(false);

	m_curState = 0;
}

PropsSafetyGuard::~PropsSafetyGuard()
{
}

PropsSafetyGuard* PropsSafetyGuard::createWithBaby(Baby* bb)
{
	PropsSafetyGuard* prop = new PropsSafetyGuard(bb);
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}


void PropsSafetyGuard::onEnter()
{
	Node::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PropsSafetyGuard::touchCallback,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

bool PropsSafetyGuard::touchCallback(Touch* touch, Event* event)
{
	if(m_position.containsPoint(touch->getLocation()) && m_canBeUsed){
		m_canBeUsed = false;
		usePropsAndUpdate();
		m_curState = 0; //使保护罩有效
		m_safetyG->setVisible(true);
		return true;
	}
	return false;
}

void PropsSafetyGuard::update(float dt)
{
	if(m_canBeUsed){
		return;
	}
	else{
		if(m_usedTime >= m_cooldownTime){
			m_canBeUsed = true;
			m_pCdTimer->setPercentage(100);
			m_pCdTimer->setVisible(false);
		}
		else{  //道具冷却时间
			m_usedTime += dt;
			m_pCdTimer->setPercentage((m_cooldownTime - m_usedTime) / m_cooldownTime * 100);
			if (m_usedTime < m_holdTime){  //在保护罩保护时间内
				/*if(m_bb->getHp() < m_babyState && m_curState != m_maxState){ // 宝贝受到攻击,而且当前保护罩有效
					CCLOG("有攻击");
					int damage = m_babyState - m_bb->getHp();
					if( damage <= m_maxState - m_curState){  //宝贝受到的攻击在保护罩可以承受的范围内，抵消攻击
						m_curState += damage;
						m_bb->setDamage(-damage);
						if (m_curState == m_maxState){
							m_safetyG->setVisible(false);
						}
					}
					else{ //宝贝受到的攻击不在保护罩可以承受的范围内，抵消攻击可以承受的攻击，保护罩消失
						m_curState = m_maxState;
						m_bb->setDamage(-(m_maxState - m_curState));
						m_safetyG->setVisible(false);
					}
				}*/
			}
			else{ //超出保护时间
				CCLOG("notwork");
				m_curState = m_maxState; // 让保护罩失效
				m_safetyG->setVisible(false);
			}
		}
	}
}

bool PropsSafetyGuard::isGuarding()
{
	if(!m_canBeUsed && m_curState < m_maxState) //使用了保护罩并且保护罩有效
		return true;
	else
		return false;
}

int PropsSafetyGuard::setCurState(int damage)
{
	int hurt = m_curState + damage  - m_maxState;
	if(hurt < 0){
		m_curState += damage;
		hurt = 0;
	}
	else{
		m_curState = m_maxState;
	}
	if(m_curState >= m_maxState){
		m_safetyG->setVisible(false);
	}
	return hurt;
}















