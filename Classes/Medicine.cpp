#include "Medicine.h"


//////////////////////////////////////////////////////////////////////////
PropsRestoreHp::PropsRestoreHp(Baby* bb, Mode mode)
{
	m_id = 0;
	m_bb = bb;
	m_sprite = Sprite::create("images/props/propsIcon1.png");
	this->addChild(m_sprite);
	m_mode = mode;
}

PropsRestoreHp::~PropsRestoreHp()
{
}

PropsRestoreHp* PropsRestoreHp::createWithBaby(Baby* bb, Mode mode)
{
	PropsRestoreHp* prop = new (std::nothrow)PropsRestoreHp(bb, mode);
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
		usePropsAndUpdate();
		return true; //接受触摸事件
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
			endCooldownAndRestart();
		}
		else{
			m_usedTime += dt;
			m_pCdTimer->setPercentage( (m_cooldownTime - m_usedTime) / m_cooldownTime * 100 );
		}
	}
}




//////////////////////////////////////////////////////////////////////////
PropsSlowdown::PropsSlowdown(const Vector<Enemy*>& emenies, Mode mode)
{
	m_id = 1;
	m_targets = emenies;
	m_sprite = Sprite::create("images/props/propsIcon2.png");
	this->addChild(m_sprite);
	m_mode = mode;
	m_isUsing = false;
}

PropsSlowdown::~PropsSlowdown()
{
	m_targets.clear();
}

PropsSlowdown* PropsSlowdown::createWithTargets(const Vector<Enemy*>& emenies, Mode mode)
{
	PropsSlowdown* prop = new PropsSlowdown(emenies, mode);
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
		m_isUsing = true;
		usePropsAndUpdate();
		for(int i = 0; i < m_targets.size(); i++)
		{
			auto enemy = m_targets.at(i);
			enemy->setSpeed(enemy->getSpeed() / 10);
		}
		return true;
	}
	return false;
}

void PropsSlowdown::update(float dt)
{
	switch (m_mode)
	{
	case MODE_GROWUP:{
		if(m_canBeUsed){
			return;
		}
		else{
			if(m_usedTime >= m_cooldownTime){
				endCooldownAndRestart();
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
					m_isUsing  = false;
				}
			}
		}
		break;
					 }
	case  MODE_ENDLESS:{
		if(m_isUsing){
			if(m_usedTime >= m_holdTime){
				for(int i = 0; i < m_targets.size(); i++)
				{
					Enemy* enemy = m_targets.at(i);
					enemy->setSpeed(enemy->getOriginSpeed());
					m_targets.erase(i);
				}
				m_isUsing = false;
			}
			else{
				m_usedTime += dt;
			}
		}
		break;
					   }
	default:
		break;
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
PropsSafetyGuard::PropsSafetyGuard(Baby* bb, Mode mode)
{
	m_id = 2;
	m_bb = bb;
	m_sprite = Sprite::create("images/props/propsIcon3.png");
	this->addChild(m_sprite);

	m_safetyG = Sprite::create("images/props/SafeGuard.png");
	m_safetyG->setPosition(Vec2(0,0));
	bb->addChild(m_safetyG);
	m_safetyG->setVisible(false);

	m_visiableG = Sprite::create();
	m_visiableG->setPosition(Vec2(0,0));
	m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_1)));
	m_visiableG->runAction(m_state);
	bb->addChild(m_visiableG);
	m_visiableG->setVisible(false);

	m_curState = RAND_MAX;
	m_lastState = RAND_MAX;
	m_mode = mode;
}

PropsSafetyGuard::~PropsSafetyGuard()
{
}

PropsSafetyGuard* PropsSafetyGuard::createWithBaby(Baby* bb,Mode mode)
{
	PropsSafetyGuard* prop = new PropsSafetyGuard(bb,mode);
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
		usePropsAndUpdate();
		m_curState = 0; //使保护罩有效
		m_lastState = 0;
		m_visiableG->setVisible(true);
		return true;
	}
	return false;
}

void PropsSafetyGuard::update(float dt)
{
	switch (m_mode)
	{
	case MODE_GROWUP:
		{
			if(m_canBeUsed){
				return;
			}
			else{
				if(m_usedTime >= m_cooldownTime){
					endCooldownAndRestart();
				}
				else{  //道具冷却时间
					m_usedTime += dt;
					m_pCdTimer->setPercentage((m_cooldownTime - m_usedTime) / m_cooldownTime * 100);
					if (m_usedTime < m_holdTime){  //在保护罩保护时间内
						if(m_lastState != m_curState){
							m_visiableG->stopAllActions();
							switch (m_maxState - m_curState)
							{
							case 3: m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_1)));
								break;
							case 2: m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_2)));
								break;
							case 1: m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_3)));
								break;
							default:m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_1)));
								break;
							}
							m_lastState = m_curState;
							m_visiableG->runAction(m_state);
						}
					}
					else{ //超出保护时间
						m_curState = m_maxState; // 让保护罩失效
						m_visiableG->setVisible(false);
					}
				}
			}
			break;
		}
	case MODE_ENDLESS:
		{
			m_usedTime += dt;
			if (m_usedTime < m_holdTime){  //在保护罩保护时间内
				if(m_lastState != m_curState){
					m_visiableG->stopAllActions();
					switch (m_maxState - m_curState)
					{
					case 3: m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_1)));
						break;
					case 2: m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_2)));
						break;
					case 1: m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_3)));
						break;
					default:m_state= RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_SAFETYGUARD_STATE_1)));
						break;
					}
					m_lastState = m_curState;
					m_visiableG->runAction(m_state);
				}
			}
			else{ //超出保护时间
				m_curState = m_maxState; // 让保护罩失效
				m_visiableG->setVisible(false);
			}
			break;
		}
	default:
		break;
	}
}

bool PropsSafetyGuard::isGuarding()
{
	if( m_curState < m_maxState) //使用了保护罩并且保护罩有效
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
		m_visiableG->setVisible(false);
	}
	return hurt;
}




//////////////////////////////////////////////////////////////////////////
PropsLandmine::PropsLandmine(const std::vector<Road>& roads, Mode mode)
{
	m_id = 3;
	m_sprite = Sprite::create("images/props/propsIcon4.png");
	this->addChild(m_sprite);

	m_roads = roads;
	m_landmindcreate = Sprite::create();
	this->addChild(m_landmindcreate);
	m_landmineAnimation = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_LANDMINE_CREATE)));
	
	m_landmindcreate->runAction(m_landmineAnimation);
	m_landmindcreate->setVisible(false);
	m_mode = mode;
}


PropsLandmine::~PropsLandmine()
{
	for(int i= 0; i < m_landmines.size(); i++)
	{
		m_landmines.at(i)->removeFromParent();
	}
	m_landmines.clear();
	m_roads.clear();
}

PropsLandmine* PropsLandmine::createWithRoads(const std::vector<Road>& roads, Mode mode)
{
	PropsLandmine* prop = new PropsLandmine(roads,mode);
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}

void PropsLandmine::onEnter()
{
	Node::onEnter();
	auto listenter = EventListenerTouchOneByOne::create();
	listenter->setSwallowTouches(true);
	listenter->onTouchBegan = CC_CALLBACK_2(PropsLandmine::touchBeginCallback, this);
	listenter->onTouchMoved = CC_CALLBACK_2(PropsLandmine::touchMovedCallback, this);
	listenter->onTouchEnded = CC_CALLBACK_2(PropsLandmine::touchEndenCallback, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenter,this);
}

bool PropsLandmine::touchBeginCallback(Touch* touch, Event* event)
{
	if(m_position.containsPoint(touch->getLocation()) && m_canBeUsed){
		m_landmindcreate->setPosition(Vec2::ZERO);
		m_landmindcreate->setVisible(true);
		return true;
	}
	return false;

}

void PropsLandmine::touchMovedCallback(Touch* touch, Event* event)
{
	Vec2 beginPoint = touch->getLocation();
	Vec2 landmineCurPt = m_landmindcreate->getPosition();
	Vec2 endPoint = touch->getPreviousLocation(); //获取触摸前一个位置
	Vec2 offSet = ccpSub(beginPoint,endPoint);
	Vec2 toPoint = ccpAdd(m_landmindcreate->getPosition(),offSet);
	m_landmindcreate->setPosition(toPoint);
}

void PropsLandmine::touchEndenCallback(Touch* touch, Event* event)
{
	Vec2 lastPoint = touch->getLocation(); //获取结束点位置
	bool setFlag = false;
	for (std::vector<Road>::iterator it = m_roads.begin(); it != m_roads.end(); it++) //结束点是否在道路上
	{
		if(it->containsPoint(lastPoint)){
			setFlag = true;
			break;
		}
	}
	if(!setFlag){ //结束点不在道路上，使用不正确，执行create不正确动画后消失
		m_landmindcreate->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_LANDMINE_INVALIDABLESET)));
		m_landmindcreate->setVisible(false);
	}
	else{ //使用正确，冷却道具，添加地雷，create消失
		usePropsAndUpdate();
		m_landmindcreate->setVisible(false);
		auto landmine = LandMine::create();
		landmine->setPosition(lastPoint);
		landmine->m_position = Rect(lastPoint.x - 75,lastPoint.y - 75,150,150); //攻击范围为150*150
		m_landmines.pushBack(landmine);
		this->getParent()->addChild(landmine,ZORDER_ENEMY);
	}
}

void PropsLandmine::update(float dt)
{
	if(m_canBeUsed){
		return ;
	}
	else{
		if(m_usedTime >= m_cooldownTime){
			endCooldownAndRestart();
		}
		else{
			m_usedTime += dt;
			m_pCdTimer->setPercentage((m_cooldownTime - m_usedTime) / m_cooldownTime * 100);
		}
	}
}

Vector<LandMine*>& PropsLandmine::getLandmines()
{
	return this->m_landmines;
}

int PropsLandmine::getNumofLandmines()
{
	return m_landmines.size();
}




//////////////////////////////////////////////////////////////////////////
PropsTrap::PropsTrap(const std::vector<Road>& roads, Mode mode)
{
	m_id = 4;
	m_sprite = Sprite::create("images/props/propsIcon5.png");
	this->addChild(m_sprite);

	m_trapcreate = Sprite::create("images/props/trap.png");
	this->addChild(m_trapcreate);
	m_trapcreate->setVisible(false);

	m_roads = roads;
	m_mode = mode;
}

PropsTrap* PropsTrap::createWithRoads(const std::vector<Road>& roads, Mode mode)
{
	PropsTrap* prop = new PropsTrap(roads,mode);
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}

PropsTrap::~PropsTrap()
{
	for (int i = 0; i < m_traps.size(); i++)
	{
		m_traps.at(i)->removeFromParent();
	}
	m_traps.clear();
	m_roads.clear();
}


void PropsTrap::onEnter()
{
	Node::onEnter();
	auto listenter = EventListenerTouchOneByOne::create();
	listenter->setSwallowTouches(true);
	listenter->onTouchBegan = CC_CALLBACK_2(PropsTrap::touchBeginCallback, this);
	listenter->onTouchMoved = CC_CALLBACK_2(PropsTrap::touchMovedCallback, this);
	listenter->onTouchEnded = CC_CALLBACK_2(PropsTrap::touchEndenCallback, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenter,this);
}

bool PropsTrap::touchBeginCallback(Touch* touch, Event* event)
{
	if(m_position.containsPoint(touch->getLocation()) && m_canBeUsed){
		m_trapcreate->setPosition(Vec2::ZERO);
		m_trapcreate->setVisible(true);
		return true;
	}
	return false;
}

void PropsTrap::touchMovedCallback(Touch* touch, Event* event)
{
	Vec2 beginPoint = touch->getLocation();
	Vec2 landmineCurPt = m_trapcreate->getPosition();
	Vec2 endPoint = touch->getPreviousLocation(); //获取触摸前一个位置
	Vec2 offSet = ccpSub(beginPoint,endPoint);
	Vec2 toPoint = ccpAdd(m_trapcreate->getPosition(),offSet);
	m_trapcreate->setPosition(toPoint);
}

void PropsTrap::touchEndenCallback(Touch* touch, Event* event)
{
	Vec2 lastpoint = touch->getLocation();
	for(std::vector<Road>::iterator it = m_roads.begin(); it != m_roads.end(); it++)
	{
		if(it->containsPoint(lastpoint)){ 
			usePropsAndUpdate();
			auto trap = Trap::createWithmaxState(m_maxState);
			trap->setPosition(lastpoint);
			trap->m_position = Rect(lastpoint.x - 60,lastpoint.y - 60,120,120);
			m_traps.pushBack(trap);
			this->getParent()->addChild(trap,ZORDER_TOWER);
			break;
		}
	}
	m_trapcreate->setVisible(false);
}

void PropsTrap::update(float dt)
{
	if(m_canBeUsed){
		return ;
	}
	else{
		if(m_usedTime >= m_cooldownTime){
			endCooldownAndRestart();
		}
		else{
			m_usedTime += dt;
			m_pCdTimer->setPercentage((m_cooldownTime - m_usedTime) / m_cooldownTime * 100);
		}
	}
}

Vector<Trap*> PropsTrap::getTraps()
{
	return this->m_traps;
}

int PropsTrap::getNumofTraps()
{
	return m_traps.size();
}





//////////////////////////////////////////////////////////////////////////
PropsAssistGuard::PropsAssistGuard(Vec2 start, Mode mode)
{
	m_id = 5;
	m_sprite = Sprite::create("images/props/propsIcon6.png");
	this->addChild(m_sprite);
	m_startPoint = start;
	m_mode = mode;
}

PropsAssistGuard::~PropsAssistGuard()
{
}

PropsAssistGuard* PropsAssistGuard::create(Vec2 start, Mode mode)
{
	PropsAssistGuard* prop = new PropsAssistGuard(start, mode);
	if(prop && prop->init()){
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}


void PropsAssistGuard::onEnter()
{
	Node::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PropsAssistGuard::onTouchCallback, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PropsAssistGuard::onTouchCallback(Touch* touch, Event* event)
{
	if(m_position.containsPoint(touch->getLocation()) && m_canBeUsed){
		usePropsAndUpdate();
		addAssistant();
		return true;
	}
	return false;
}

void PropsAssistGuard::update(float dt)
{
	if(m_canBeUsed){
		return;
	}
	else{
		if(m_usedTime >= m_cooldownTime){
			endCooldownAndRestart();
		}
		else{
			m_usedTime += dt;
			m_pCdTimer->setPercentage((m_cooldownTime - m_usedTime) / m_cooldownTime * 100);
		}
	}
}

void PropsAssistGuard::addAssistant()
{
	auto game = (Game*)(this->getParent());
	if(game != NULL){
		Assistant* assistant = Assistant::create();
		assistant->setPosition(m_startPoint);
		assistant->setTag(TAG_ASSISTANT);
		game->addChild(assistant);
		game->getAssistants().pushBack(assistant);
		assistant->runAction(Sequence::create(game->getActionsAssistant()));
	}
}
