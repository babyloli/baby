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
	//陷阱已达到最大状态，不能再吞吃小怪兽
	if(state==maxCapacity){
		return false;
	}

	//陷阱没有达到最大状态
	state++;
	return true;
}

void Trap::act(){
	if(updateState()){
		
		/*根据帧数和状态来生成相应的Animation，然后run！ */
		char str[100] = {0};

		//sprintf(str, "%s",this->getName(),state);
	}
}