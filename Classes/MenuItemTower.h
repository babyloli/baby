#ifndef __MENUITEM_TOWER_H__
#define __MENUITEM_TOWER_H__

#include "cocos2d.h"
#include "LabelPrice.h"
USING_NS_CC;

class MenuItemTower : public MenuItemSprite{
public:
	/** creates a menu item with a normal, selected and disabled image*/
	static MenuItemTower * create(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite = nullptr);
	/** creates a menu item with a normal and selected image with a callable object */
	static MenuItemTower * create(int price, Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);
	/** creates a menu item with a normal,selected  and disabled image with target/selector */
	static MenuItemTower * create(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
	/** Sets the price to build a tower*/
	bool setPrice(int price);
	/** Gets the price to build a tower*/
	inline int getPrice(){ return m_price; }

CC_CONSTRUCTOR_ACCESS:
	MenuItemTower()
	:m_price(0)
	{}

	/** initializes a menu item with a normal, selected  and disabled image with a callable object */
	bool initWithPriceAndNormalSprite(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
protected:
	int m_price;
private:
	CC_DISALLOW_COPY_AND_ASSIGN(MenuItemTower);
};

#endif
