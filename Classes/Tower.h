#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
USING_NS_CC;

class Tower : public Node
{
private:
	int m_level;
	int m_id;
	std::string m_name;	//tower name
	int m_type;	//physics or magic
	float m_speed;	//attack frequency
	int m_attack;
	int m_deltaAttack;	//when upgrade
	int m_range;
	int m_deltaRange;	//when upgrade
	int m_price;
	int m_deltaPrice;	//when upgrade
	float m_moneyReturnRate;
	std::string m_bulletName;
	int m_bulletSpeed;
	bool m_rotateEnable;
	bool m_bulletRotateEnable;
	bool m_bulletCollide;

	float m_elapsedTime;
	Enemy* m_target;
	Sprite* m_sprite;
	DrawNode* m_circle;
public:
	Tower();
	static Tower* create(int id);
	bool initWithType(int id);

	Enemy* getCloseTarget();
	void generateBullet(float dt);//生成子弹并且向target发射
	void shotBullet(Bullet* bullet,Enemy* target); //子弹向目标enemy发射

	int getId();
	void setId(int id);
	int getlevel();
	void upgrade();//升级
	int getRange();
	void setRange(int r);
	void showRange(bool);

	int getUpgradePrice();
	int getMoneyWhenDeleted();
};

