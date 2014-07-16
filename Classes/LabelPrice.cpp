#include "LabelPrice.h"
#include "ResourceManager.h"

LabelPrice::LabelPrice()
	:m_label(NULL)
{
	m_config.fontSize = FONTSIZE_PRICE;
	m_config.fontFilePath = FONT_PRICE;
}

LabelPrice* LabelPrice::create(const std::string& backgroundSprite, int price){
	LabelPrice *pRet = new LabelPrice();
	if (pRet && pRet->initWithFile(backgroundSprite, price)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool LabelPrice::initWithFile(const std::string& backgroundSprite, int price){
	auto sprite = Sprite::create(backgroundSprite);
	if (!sprite)
		return false;
	this->addChild(sprite);
	m_label = Label::createWithTTF(m_config, std::to_string(price));
	this->addChild(m_label);
	return true;
}

LabelPrice* LabelPrice::create(Texture2D* texture, int price){
	LabelPrice *pRet = new LabelPrice();
	if (pRet && pRet->initWithTexture(texture, price)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool LabelPrice::initWithTexture(Texture2D* texture, int price)
{
	auto sprite = Sprite::createWithTexture(texture);
	if (!sprite)
		return false;
	this->addChild(sprite);
	m_label = Label::createWithTTF(m_config, std::to_string(price));
	this->addChild(m_label);
	return true;
}

void LabelPrice::setPrice(int price){
	if (m_label){
		m_label->setString(std::to_string(price));
	}
}