#include "Mouse.h"
#include "ResourceManager.h"

Mouse::Mouse(){
	m_isUp = false;
};

Mouse* Mouse::create(){
	Mouse *pRet = new Mouse();
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

bool Mouse::init(){
	m_sprite = Sprite::create();
	this->addChild(m_sprite);
	return true;
}

void Mouse::goUp(){
	m_isUp = true;
	m_sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_MOUSE))
		, CallFuncN::create([this](Node* node)->void{
			m_isUp = false;
	}), NULL)); 
}

void Mouse::killed(){
	m_isUp = false;
	m_sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_EXPLOSION)));
}