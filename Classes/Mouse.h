#ifndef __MOUSE_H__
#define __MOUSE_H__
#include "cocos2d.h"
USING_NS_CC;

class Mouse : public Node{
public:
	static Mouse* create();
	Mouse();
	virtual bool init() override;

	void goUp();
	void killed();
	bool isUp(){return m_isUp;}
private:
	bool m_isUp;
	Sprite* m_sprite;
};
#endif