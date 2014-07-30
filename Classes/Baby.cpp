#include "Baby.h"
#include "ResourceManager.h"

Baby::Baby()
	:m_hp(8)
	,m_sprite(NULL)
	,m_action(NULL)
{}

bool Baby::init(){
	m_sprite = Sprite::create();
	this->addChild(m_sprite);
	m_action = RepeatForever::create(Animate::create(
		AnimationCache::getInstance()->getAnimation(ANIMATION_BABY_NORMAL)));
	//m_sprite->setScale(1.5);
	m_sprite->runAction(m_action);

	auto labelBg = Sprite::create("images/baby/HpBackground.png");
	labelBg->setPosition(Vec2(m_sprite->getPositionX(),m_sprite->getPositionY() - labelBg->getContentSize().height * 1.3));
	labelBg->setScale(1.2f);
	this->addChild(labelBg);
	TTFConfig config("fonts/cardFont.ttf",20);
	m_hpLabel = Label::createWithTTF(config,itos(m_hp));
	m_hpLabel->setPosition(Vec2(m_sprite->getPositionX(),m_sprite->getPositionY() - labelBg->getContentSize().height * 1.3));
	m_hpLabel->setColor(Color3B(114,85,52));
	this->addChild(m_hpLabel);
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
	m_hpLabel->setString(itos(m_hp));
	
	if (m_hp <= 0){
		return true;
	}
	auto cache = AnimationCache::getInstance();
	if (m_hp > 0 && m_hp <= 2){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ANIMATION_BABY_HURTED)));
	} else if (m_hp > 2 && m_hp <= 4){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ANIMATION_BABY_CRY)));
	} else if (m_hp > 4 && m_hp <= 6){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ANIMATION_BABY_SAD)));
	} else if (m_hp > 6 /* && m_hp <= 8 */){
		m_action = RepeatForever::create(Animate::create(
			cache->getAnimation(ANIMATION_BABY_NORMAL)));
	} 
	m_sprite->runAction(m_action);
	return false;
}

void Baby::hurt(){
	m_sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_BABY_HURTING)));
}

bool Baby::touchCallback(Touch* touch, Event* event){
	if (m_position.containsPoint(touch->getLocation())){
		if (m_hp >= 8){
			m_sprite->stopAllActions();
			m_sprite->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([this](){
				this->setDamage(0);
			}), NULL));
			m_action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_BABY_LAUGH)));
			m_sprite->runAction(m_action);
		} 
		else if (m_hp > 6) {
			m_sprite->stopAllActions();
			m_sprite->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([this](){
				this->setDamage(0);
			}), NULL));
			m_action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_BABY_HAPPY)));
			m_sprite->runAction(m_action);
		}
		return true;
	}
	return false;
}

void Baby::restoreHealth(){
	m_hp = m_hp + 1;
	setDamage(0);
}