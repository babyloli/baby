#pragma once
#include "ResourceManager.h"
class Props: public Sprite
{
protected:
	int m_id;
	std::string m_name;
	int m_price;
	int m_maxState;
public:
	static Props* createWithId(int id);
	virtual bool init() override;
	Props(int id);
	Props();
	virtual ~Props(void);

	const std::string getName(){return m_name;}
	const int getPrice(){return m_price;}
};

