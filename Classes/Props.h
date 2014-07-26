#pragma once
#include "ResourceManager.h"
#include "IHomeMenuScene.h"
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
	float m_cooldownTime;
	float m_holdTime;
	float m_usedTime;
	bool m_canBeUsed;
	
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

protected:
	void usePropsAndUpdate();
};


