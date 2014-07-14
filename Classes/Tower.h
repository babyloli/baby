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
	void generateBullet();//�����ӵ�������target����
	void shotBullet(Bullet* bullet,Enemy* target); //�ӵ���Ŀ��enemy����

	int getType();
	void setType(int type);
	int getlevel();
	void upgrade();//����
	int getRange();
	void setRange(int r);

};
