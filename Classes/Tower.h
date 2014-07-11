#pragma once

#include"cocos2d.h"
#include"Enemy.h"
#include"Bullet.h"
#include"GameScene.h"

USING_NS_CC;

#define TOWER_TYPE_0 0
#define TOWER_TYPE_1 1
#define TOWER_TYPE_2 2
#define TOWER_TYPE_3 3
#define TOWER_TYPE_4 4
#define TOWER_TYPE_5 5

class Tower:public Sprite
{
private:
	int type;
	int level;
	int range;
	Enemy* target;
	Sprite* tower;
	Vector<Bullet*> bullets;

public:
	CREATE_FUNC(Tower);
	Tower();
	Tower(int type);
	~Tower(void);
	virtual bool init();
	static Tower* create(int type);
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

