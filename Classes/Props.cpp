#include "Props.h"
TTFConfig configProps("fonts/cardFont.ttf",15);

Props* Props::createWithId(int id)
{
	Props *sprite = new (std::nothrow) Props(id);
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Props::Props(int id)
{
	m_id = id;
}

Props::Props(){}

Props::~Props(void)
{
}

bool Props::init()
{
	HCSVFile* propsData = ResourceManager::getInstance()->propsData;
	m_name = propsData->getData(m_id, 1);
	m_price = std::atoi(propsData->getData(m_id, 2));
	m_maxState = std::atoi(propsData->getData(m_id, 3));
	m_framesNumber = std::atoi(propsData->getData(m_id,4));
	m_cooldownTime = std::atof(propsData->getData(m_id,5));
	m_holdTime = std::atof(propsData->getData(m_id,6));

	m_usedTime = 0.0;
	m_canBeUsed = true;

	m_notebg = Sprite::create("images/props/noteBackground.png");
	m_notebg->setPosition(40,40);
	this->addChild(m_notebg);
	int num = UserDefault::sharedUserDefault()->getIntegerForKey(m_name.c_str());
	CCLOG("wrong");
	m_number = Label::createWithTTF(configProps,std::to_string(num));
	m_number->setPosition(40,40);
	this->addChild(m_number);
	
	auto cdBar = Sprite::create("images/props/mask.png");
	m_pCdTimer = ProgressTimer::create(cdBar);
	m_pCdTimer->setType(ProgressTimer::Type::BAR);
	m_pCdTimer->setMidpoint(Vec2(0,0.5f));
	m_pCdTimer->setBarChangeRate(Vec2(1,0));
	m_pCdTimer->setRotation(-90);
	m_pCdTimer->setPercentage(100);
	this->addChild(m_pCdTimer,4);
	m_pCdTimer->setVisible(false);

	if (num <= 0){
		m_sprite->setVisible(false);
		m_notebg->setVisible(false);
		m_number->setVisible(false);
	}

	this->scheduleUpdate();

	return true;
}

void Props::usePropsAndUpdate()
{
	int num = UserDefault::sharedUserDefault()->getIntegerForKey(m_name.c_str()) - 1;
	UserDefault::sharedUserDefault()->setIntegerForKey(m_name.c_str(),num);
	m_number->setString(std::to_string(num));
	if(num <= 0){
		m_sprite->setVisible(false);
		m_notebg->setVisible(false);
		m_number->setVisible(false);
	}
	m_pCdTimer->setVisible(true);
}
