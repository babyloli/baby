#include "Trap.h"


void Trap::setValue(const int id, const int capacity)
{
	typeId = id;
	state = 0;
	maxCapacity = capacity;
}


Trap::~Trap(void)
{
}

bool Trap::updateState()
{
	//�����Ѵﵽ���״̬���������̳�С����
	if(state==maxCapacity){
		return false;
	}

	//����û�дﵽ���״̬
	state++;
	return true;
}

void Trap::act(){
	if(updateState()){
		
		/*����֡����״̬��������Ӧ��Animation��Ȼ��run�� */
		char str[100] = {0};

		//sprintf(str, "%s",this->getName(),state);
	}
}