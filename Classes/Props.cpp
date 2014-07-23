#include "Props.h"

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
	return true;
}