#ifndef __MENUITEM_TOWER_H__
#define __MENUITEM_TOWER_H__

#include "cocos2d.h"
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
	void setPrice(int price);
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


/*
class MenuItemTower : public MenuItem{
	public:
    / ** creates a menu item with a normal, selected and disabled image* /
    static MenuItemTower * create(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite = nullptr);
    / ** creates a menu item with a normal and selected image with a callable object * /
    static MenuItemTower * create(int price, Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);
    / ** creates a menu item with a normal,selected  and disabled image with target/selector * /
    static MenuItemTower * create(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);

    / ** Gets the image used when the item is not selected * /
    inline Node* getNormalImage() const { return _normalImage; };
    
    / ** Sets the image used when the item is not selected * /
    void setNormalImage(Node* image);
    
    / ** Gets the image used when the item is selected * /
    inline Node* getSelectedImage() const { return _selectedImage; };
    
    / ** Sets the image used when the item is selected * /
    void setSelectedImage(Node* image);
    
    / ** Gets the image used when the item is disabled * /
    inline Node* getDisabledImage() const { return _disabledImage; };
    
    / ** Sets the image used when the item is disabled * /
    void setDisabledImage(Node* image);

	/ ** Sets the price to build a tower* /
	void setPrice(int price);
    
    / **
     @since v0.99.5
     * /
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemTower()
    :_normalImage(nullptr)
    ,_selectedImage(nullptr)
    ,_disabledImage(nullptr)
    {}
    
    / ** initializes a menu item with a normal, selected  and disabled image with a callable object * /
    bool initWithNormalSprite(int price, Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
    
protected:
    virtual void updateImagesVisibility();

    / ** the image used when the item is not selected * /
    Node* _normalImage;
    / ** the image used when the item is selected * /
    Node* _selectedImage;
    / ** the image used when the item is disabled * /
    Node* _disabledImage;
	/ ** the price to build a tower* /
	int m_price;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemTower);
};*/
#endif
