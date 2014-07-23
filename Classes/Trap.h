#pragma once
#include "props.h"


//
class Trap :
	public Props
{
private:
	int typeId;
	int maxCapacity;//monster的最大容量，gamescene中设定；
	int state;//state对于容量，初始为0，大于maxCapacity则陷阱耗尽；

	bool updateState();

public:
	Trap();
	~Trap(void);

	void setValue(const int id, const int capacity);

	// 返回类型ID
	const int getTypeId(){return typeId;};
	
	// 检测到碰撞之后，根据更新后的state做出相应处理；
	void act();

};

