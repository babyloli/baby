#include "Road.h"
#include "ResourceManager.h"

Road::Road(float x, float y, float width, float height, int direction)
	:Rect(x, y, width, height)
{
	m_direction = direction;
}

Vec2 Road::getDirectionVec2(){
	if (m_direction == LEFT)
		return Vec2(-1, 0);
	if (m_direction == UP)
		return Vec2(0, 1);
	if (m_direction == RIGHT)
		return Vec2(1, 0);
	if (m_direction == DOWN)
		return Vec2(0, -1);
	return Vec2::ZERO;
}

int Road::getDirection(){
	return m_direction;
}