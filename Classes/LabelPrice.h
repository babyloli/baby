#ifndef __LABEL_PRICE_H__
#define __LABEL_PRICE_H__

#include "cocos2d.h"
USING_NS_CC;
class LabelPrice : public Node{
public:
	CREATE_FUNC(LabelPrice);
	LabelPrice();
	static LabelPrice* create(const std::string& backgroundSprite, int price);
	bool initWithSprite(const std::string& backgroundSprite, int price);
};
#endif