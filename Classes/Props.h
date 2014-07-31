#pragma once
#include "ResourceManager.h"
#include "IHomeMenuScene.h"

enum Mode
{
	MODE_ENDLESS,
	MODE_GROWUP
};

//////////////////////////////////////////////////////////////////////////
// Basic class for props
class Props: public Node
{
protected:
	int m_id;
	std::string m_name;
	int m_price;
	int m_maxState;
	int m_framesNumber;
	int m_damage;
	float m_cooldownTime;
	float m_holdTime;
	float m_usedTime;
	bool m_canBeUsed;
	
	int m_mode;
	int m_count;
	Sprite* m_notebg;
	ProgressTimer* m_pCdTimer;
	Label* m_number;
public:
	Sprite* m_sprite;
	Rect m_position;
public:
	static Props* createWithId(int id);
	virtual bool init() override;
	Props(int id);
	Props();
	virtual ~Props(void);

	const std::string getName(){return m_name;}
	const int getPrice(){return m_price;}
	const int getDamage(){return m_damage;}
	void AndEndlessNumber();

protected:
	void usePropsAndUpdate();
	void endCooldownAndRestart();
};


