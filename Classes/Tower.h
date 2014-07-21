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
	float m_speed;
	float m_elapsedTime;
	Enemy* m_target;
	Sprite* m_sprite;
public:
	Tower();
	static Tower* create(int type);
	bool initWithType(int type);

	Enemy* getCloseTarget();
	void generateBullet(float dt);//�����ӵ�������target����
	void shotBullet(Bullet* bullet,Enemy* target); //�ӵ���Ŀ��enemy����

	int getType();
	void setType(int type);
	int getlevel();
	void upgrade();//����
	int getRange();
	void setRange(int r);
	void setTowerTexture(const std::string& filename);

};

