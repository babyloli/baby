#include "MenuItemTower.h"

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
	MenuItemSprite::initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
	setPrice(price);
	return true;
}


void MenuItemTower::setPrice(int price){
	m_price = price;
}

/*

void MenuItemTower::selected()
{
	MenuItem::selected();

	if (_normalImage)
	{
		if (_disabledImage)
		{
			_disabledImage->setVisible(false);
		}

		if (_selectedImage)
		{
			_normalImage->setVisible(false);
			_selectedImage->setVisible(true);
		}
		else
		{
			_normalImage->setVisible(true);
		}
	}
}

void MenuItemTower::unselected()
{
	MenuItem::unselected();
	if (_normalImage)
	{
		_normalImage->setVisible(true);

		if (_selectedImage)
		{
			_selectedImage->setVisible(false);
		}

		if (_disabledImage)
		{
			_disabledImage->setVisible(false);
		}
	}
}

void MenuItemTower::setEnabled(bool bEnabled)
{
	if( _enabled != bEnabled ) 
	{
		MenuItem::setEnabled(bEnabled);
		this->updateImagesVisibility();
	}
}

// Helper 
void MenuItemTower::updateImagesVisibility()
{
	if (_enabled)
	{
		if (_normalImage)   _normalImage->setVisible(true);
		if (_selectedImage) _selectedImage->setVisible(false);
		if (_disabledImage) _disabledImage->setVisible(false);
	}
	else
	{
		if (_disabledImage)
		{
			if (_normalImage)   _normalImage->setVisible(false);
			if (_selectedImage) _selectedImage->setVisible(false);
			if (_disabledImage) _disabledImage->setVisible(true);
		}
		else
		{
			if (_normalImage)   _normalImage->setVisible(true);
			if (_selectedImage) _selectedImage->setVisible(false);
			if (_disabledImage) _disabledImage->setVisible(false);
		}
	}
}

void MenuItemTower::setNormalImage(Node* image)
{
	if (image != _normalImage)
	{
		if (image)
		{
			addChild(image, 0, kNormalTag);
			image->setAnchorPoint(Vec2(0, 0));
		}

		if (_normalImage)
		{
			removeChild(_normalImage, true);
		}

		_normalImage = image;
		this->setContentSize(_normalImage->getContentSize());
		this->updateImagesVisibility();
	}
}

void MenuItemTower::setSelectedImage(Node* image)
{
	if (image != _normalImage)
	{
		if (image)
		{
			addChild(image, 0, kSelectedTag);
			image->setAnchorPoint(Vec2(0, 0));
		}

		if (_selectedImage)
		{
			removeChild(_selectedImage, true);
		}

		_selectedImage = image;
		this->updateImagesVisibility();
	}
}

void MenuItemTower::setDisabledImage(Node* image)
{
	if (image != _normalImage)
	{
		if (image)
		{
			addChild(image, 0, kDisableTag);
			image->setAnchorPoint(Vec2(0, 0));
		}

		if (_disabledImage)
		{
			removeChild(_disabledImage, true);
		}

		_disabledImage = image;
		this->updateImagesVisibility();
	}
}*/
