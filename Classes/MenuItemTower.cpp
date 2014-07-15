#include "MenuItemTower.h"
#include "ResourceManager.h"

MenuItemTower* MenuItemTower::create(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite /* = nullptr */){
	return MenuItemTower::create(price, normalSprite, selectedSprite, disabledSprite, (const ccMenuCallback&)nullptr);
}

MenuItemTower* MenuItemTower::create(int price, Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback){
	return MenuItemTower::create(price, normalSprite, selectedSprite, nullptr, callback);
}

MenuItemTower* MenuItemTower::create(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback){
	MenuItemTower *ret = new MenuItemTower();
	ret->initWithPriceAndNormalSprite(price, normalSprite, selectedSprite, disabledSprite, callback);
	ret->autorelease();
	return ret;
}

bool MenuItemTower::initWithPriceAndNormalSprite(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback){	
	bool ret = MenuItemSprite::initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
	if (ret)
		if (setPrice(price) != ret)
			return false;
	return ret;
}


bool MenuItemTower::setPrice(int price){
	m_price = price;
	auto labelPrice = LabelPrice::create("priceBackground.png", price);
	if (labelPrice == NULL)
		return false;
	Node* child = this->getChildByTag(TAG_LABELPRICE);
	if (child != NULL){
		this->removeChildByTag(TAG_LABELPRICE);
	}
	labelPrice->setPosition(_normalImage->getContentSize()/2);
	this->addChild(labelPrice, ZORDER_LABELPRICE, TAG_LABELPRICE);
	return true;
}
