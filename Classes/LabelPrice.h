#ifndef __LABEL_PRICE_H__
#define __LABEL_PRICE_H__

#include "cocos2d.h"
USING_NS_CC;
class LabelPrice : public Node{
private:
	Label* m_label;
	TTFConfig m_config;
public:
	CREATE_FUNC(LabelPrice);
	LabelPrice();
	static LabelPrice* create(const std::string& backgroundSprite, int price);
	bool initWithFile(const std::string& backgroundSprite, int price);
	static LabelPrice* create(Texture2D* texture, int price);
	bool initWithTexture(Texture2D* texture, int price);

	void setPrice(int price);
};
#endif