#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#include "cocos2d.h"
USING_NS_CC;

class ResourceManager {
public :
	static ResourceManager* getInstance();
	void init();

//----------------Tag------------------------
#define TAG_LABELPRICE 9
#define TAG_BULLET 8
#define TAG_ENEMY 7
//----------------Priority-------------------
#define Priority_EventListenerPhysicsContact 10
//----------------Z-Order--------------------
#define ZORDER_LABELPRICE 4
#define ZORDER_MENU 10
#define ZORDER_TOWER 5
//----------------PhysicsMask----------------
#define CategoryBitMask_Bullet		0x0000000F
#define CategoryBitMask_Barrier		0x000000F0
#define CategoryBitMask_Enemy		0x00000F00

#define ContactTestBitMask_Bullet	0x00000F00
#define ContactTestBitMask_Barrier	0x00000000
#define ContactTestBitMask_Enemy	0x0000000F

#define CollisionBitMask_Bullet		0x00000F00
#define CollisionBitMask_Barrier	0x00000F00
#define CollisionBitMask_Enemy		0x000000FF

//----------------Tower----------------------
#define MAX_RANGE 9999
#define TOWER_TYPE_0 0
#define TOWER_TYPE_1 1
#define TOWER_TYPE_2 2
#define TOWER_TYPE_3 3
#define TOWER_TYPE_4 4
#define TOWER_TYPE_5 5
	Texture2D* tower0;

//----------------Bullet---------------------
#define DAMAGE_0_1 20
#define DAMAGE_0_2 30
#define DAMAGE_0_3 50

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