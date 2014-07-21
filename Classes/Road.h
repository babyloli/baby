#ifndef __ROAD_H__
#define __ROAD_H__
#include "cocos2d.h"
USING_NS_CC;

class Road : public Rect{
private:
	int m_direction;
public:
	Road(float x, float y, float width, float height, int direction);
	Vec2 getDirectionVec2();
	int getDirection();
};
#endif