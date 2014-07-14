#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
USING_NS_CC;

class Tower : public Node
{
private:
	int m_type;
	int m_level;
	int m_range;
	Enemy* m_target;
	Vector<Bullet*> m_bullets;
	Sprite* m_sprite;
public:
	Tower();
	static Tower* create(int type);
	bool initWithType(int type);

	Enemy* getCloseTarget();
	void generateBullet();//生成子弹并且向target发射
	void shotBullet(Bullet* bullet,Enemy* target); //子弹向目标enemy发射

	int getType();
	void setType(int type);
	int getlevel();
	void upgrade();//升级
	int getRange();
	void setRange(int r);

};

