#include "Trap.h"

LandMine::LandMine()
{
	m_sprite = NULL;
}

bool LandMine::init()
{
	m_sprite = Sprite::create();
	this->addChild(m_sprite);
	m_action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_LANDMINE_WAIT)));
	m_sprite->runAction(m_action);
	m_isbomb = false;
	return true;
}

void LandMine::bomb()
{
	//被踩到时的动画
	m_sprite->stopAction(m_action);
	m_sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_LANDMINE_BOMB)));
	m_isbomb = true;
}



//////////////////////////////////////////////////////////////////////////

Trap::Trap(int maxState)
{
	m_sprite = NULL;
	m_maxState = maxState;
}

bool Trap::init()
{
	m_sprite = Sprite::create();
	this->addChild(m_sprite);
	m_action = RepeatForever::create(Animate::create((AnimationCache::getInstance()->getAnimation(ANIMATION_TRAP_STATE_1))));
	m_sprite->runAction(m_action);
	
	m_curState = 0;
	return true;
}

Trap* Trap::createWithmaxState(int maxState)
{
	Trap* trap = new Trap(maxState);
	if(trap && trap->init()){
		trap->autorelease();
		return trap;
	}
	CC_SAFE_DELETE(trap);
	return nullptr;
}


void Trap::catchEnemy(Enemy* enemy)
{
	if(enemy == NULL){
		return;
	}
	for(int i = 0; i < m_targets.size(); i++ )
	{
		if(enemy == m_targets.at(i)){
			return;
		}
	}
	m_sprite->stopAllActions();

	enemy->setSpeed(0);
	enemy->setMode(false);
	m_targets.pushBack(enemy);
	m_curState++;

	switch (m_curState)
	{
	case 0: m_action = RepeatForever::create(Animate::create((AnimationCache::getInstance()->getAnimation(ANIMATION_TRAP_STATE_1))));
			break;
	case 1: m_action = RepeatForever::create(Animate::create((AnimationCache::getInstance()->getAnimation(ANIMATION_TRAP_STATE_2))));
			break;
	case 2: m_action = RepeatForever::create(Animate::create((AnimationCache::getInstance()->getAnimation(ANIMATION_TRAP_STATE_3))));
			break;
	default: m_action = RepeatForever::create(Animate::create((AnimationCache::getInstance()->getAnimation(ANIMATION_TRAP_STATE_3))));
			break;
	}
	m_sprite->runAction(m_action);
}

void Trap::destory()
{
	m_sprite->stopAction(m_action);
	m_curState = m_maxState;
}

bool Trap::isContainable()
{
	if(m_curState < m_maxState){
		return true;
	}
	else{
		return false;
	}
}

Vector<Enemy*>& Trap::getTargets()
{
	return this->m_targets;
}
