#include "LabelPrice.h"

LabelPrice::LabelPrice()
{
}

LabelPrice* LabelPrice::create(const std::string& backgroundSprite, int price){
	LabelPrice *pRet = new LabelPrice();
	if (pRet && pRet->initWithSprite(backgroundSprite, price)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

bool LabelPrice::initWithSprite(const std::string& backgroundSprite, int price){
	auto sprite = Sprite::create(backgroundSprite);
	this->addChild(sprite);

	TTFConfig config;
	config.fontSize = 20;
	config.fontFilePath = "cardFont.ttf";
	auto label = Label::createWithTTF(config, std::to_string(price));
	this->addChild(label);
	return true;
}