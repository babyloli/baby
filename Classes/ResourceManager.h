#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#include "cocos2d.h"
USING_NS_CC;

class ResourceManager {
public :
	static ResourceManager* getInstance();
	void init();

//----------------PhysicsMask----------------
#define CategoryBitMask_Bullet	
#define CategoryBitMask_Barrier
#define CategoryBitMask_Enemy

#define ContactTestBitMask_Bullet
#define ContactTestBitMask_Barrier
#define ContactTestBitMask_Enemy

#define CollisionBitMask_Bullet
#define CollisionBitMask_Barrier
#define CollisionBitMask_Enemy

//----------------Tower----------------------
#define TOWER_TYPE_0 0
#define TOWER_TYPE_1 1
#define TOWER_TYPE_2 2
#define TOWER_TYPE_3 3
#define TOWER_TYPE_4 4
#define TOWER_TYPE_5 5
	Texture2D* tower0;

//----------------Enemy----------------------
#define VIRUS_TYPE_0 0
#define VIRUS_TYPE_1 1 
#define VIRUS_TYPE_2 2
#define VIRUS_TYPE_3 3
#define VIRUS_TYPE_4 4
#define VIRUS_TYPE_5 5


private:
	static ResourceManager* m_instance;
	ResourceManager();
	virtual ~ResourceManager();
	ResourceManager(const ResourceManager&);
	ResourceManager &operator = (const ResourceManager&);
};

#endif