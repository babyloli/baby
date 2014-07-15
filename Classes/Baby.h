#ifndef __BABY_H__
#define __BABY_H__
#include "cocos2d.h"
USING_NS_CC;

class Baby : public Node
{
private:
	int m_hp;
	Sprite* m_sprite;
public:
	Baby();
	CREATE_FUNC(Baby);
	virtual bool init() override;

	/**return true if game over*/
	bool setDamage(int damage);
};

#endif