#include "Baby.h"
#include "ResourceManager.h"

Baby::Baby()
	:m_hp(8)
	,m_sprite(NULL)
{}

bool Baby::init(){
	m_sprite = Sprite::createWithTexture(ResourceManager::getInstance()->baby);
	this->addChild(m_sprite);
	m_sprite->runAction(RepeatForever::create(Animate::create(
		AnimationCache::getInstance()->getAnimation(ResourceManager::ANIMATION_BABY_NORMAL))));
	return true;
}

bool Baby::setDamage(int damage){
	m_hp -= damage;
	m_sprite->stopAllActions();
	if (m_hp <= 0){
		return true;
	}
	auto cache = AnimationCache::getInstance();
	if (m_hp > 0 && m_hp <= 2){
		m_sprite->runAction(RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_HURTED))));
	} else if (m_hp > 2 && m_hp <= 4){
		m_sprite->runAction(RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_CRY))));
	} else if (m_hp > 4 && m_hp <= 6){
		m_sprite->runAction(RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_SAD))));
	} else if (m_hp > 6 && m_hp <= 8){
		m_sprite->runAction(RepeatForever::create(Animate::create(
			cache->getAnimation(ResourceManager::ANIMATION_BABY_NORMAL))));
	} 
	return false;
}