#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#include "cocos2d.h"
USING_NS_CC;

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define NO_DIRECTION 4

class ResourceManager {
public:
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
#define DAMAGE_BULLET_0_1 20
#define DAMAGE_BULLET_0_2 30
#define DAMAGE_BULLET_0_3 50

//----------------Enemy----------------------
#define VIRUS_TYPE_0 0
#define VIRUS_TYPE_1 1 
#define VIRUS_TYPE_2 2
#define VIRUS_TYPE_3 3
#define VIRUS_TYPE_4 4
#define VIRUS_TYPE_5 5

#define DAMAGE_ENEMY_0 1
#define SPEED_ENEMY_0 500
#define DEFENCE_MAGICAL_0 10
#define DEFENCE_PHYSICS_0 10
	static std::string ANIMATION_WALK_RIGHT_0;
	static std::string ANIMATION_WALK_UP_0;
	static std::string ANIMATION_WALK_LEFT_0;
	static std::string ANIMATION_WALK_DOWN_0;
//----------------Baby-----------------------
	Texture2D* baby;
	static std::string ANIMATION_BABY_LAUGH;
	static std::string ANIMATION_BABY_HAPPY;
	static std::string ANIMATION_BABY_NORMAL;
	static std::string ANIMATION_BABY_SAD;
	static std::string ANIMATION_BABY_CRY;
	static std::string ANIMATION_BABY_HURTING;
	static std::string ANIMATION_BABY_HURTED;
	static std::string ANIMATION_BABY_ANGRY;
	static std::string ANIMATION_BABY_WIN;
public :
	static ResourceManager* getInstance();
	void init();
private:
	static ResourceManager* m_instance;
	ResourceManager();
	virtual ~ResourceManager();
	ResourceManager(const ResourceManager&);
	ResourceManager &operator = (const ResourceManager&);

	void loadAnimation();
	void loadAnimation(const char* format, int size, float delay, const std::string &name);
};

#endif