#include "Baby.h"
#include "ResourceManager.h"

Baby::Baby()
	:m_hp(8)
	,m_sprite(NULL)
	,m_action(NULL)
{}

bool Baby::init(){
	m_sprite = Sprite::createWithTexture(ResourceManager::getInstance()->baby);
	this->addChild(m_sprite);
	m_action = RepeatForever::create(Animate::create(
		AnimationCache::getInstance()->getAnimation(ResourceManager::ANIMATION_BABY_NORMAL)));
	m_sprite->runAction(m_action);
	
	return true;
}

void Baby::onEnter(){
	Node::onEnter();
	auto listener = EventListenerTouchOneByOne::create();	//´¥Ãþ¼àÌýÆ÷
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Baby::touchCallback, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Baby::setDamage(int damage){
	m_hp -= damage;
	m_sprite->stopAllActions();
	if (m_hp <= 0){
		return true;
	}
	auto cache = AnimationCache::getInstance();
	if (m_hp > 0 && m_hp <= 2){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_HURTED)));
	} else if (m_hp > 2 && m_hp <= 4){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_CRY)));
	} else if (m_hp > 4 && m_hp <= 6){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_SAD)));
	} else if (m_hp > 6 && m_hp <= 8){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_NORMAL)));
	} 
	m_sprite->runAction(m_action);
	return false;
}

void Baby::hurt(){
	m_sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(ResourceManager::ANIMATION_BABY_HURTING)));
}

bool Baby::touchCallback(Touch* touch, Event* event){
//	Baby* baby = static_cast<Baby*>(pSender);
	if (m_hp >= 8){
		m_sprite->stopAllActions();
		m_sprite->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([this](){
			this->setDamage(0);
		}), NULL));
		m_action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ResourceManager::ANIMATION_BABY_LAUGH)));
		m_sprite->runAction(m_action);
 	} 
	else if (m_hp > 6) {
		m_sprite->stopAllActions();
		m_sprite->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([this](){
			this->setDamage(0);
		}), NULL));
		m_action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ResourceManager::ANIMATION_BABY_HAPPY)));
		m_sprite->runAction(m_action);
 	}
	return true;
}