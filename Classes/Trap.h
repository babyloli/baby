#pragma once
#include "props.h"


//
class Trap :
	public Props
{
private:
	int typeId;
	int maxCapacity;//monster�����������gamescene���趨��
	int state;//state������������ʼΪ0������maxCapacity������ľ���

	bool updateState();

public:
	Trap();
	~Trap(void);

	void setValue(const int id, const int capacity);

	// ��������ID
	const int getTypeId(){return typeId;};
	
	// ��⵽��ײ֮�󣬸��ݸ��º��state������Ӧ����
	void act();

};

