#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#include "cocos2d.h"
#include "HCSVFile.h"
#include <string>
USING_NS_CC;

class ResourceManager {
public:
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ROAD_LEFT 0
#define ROAD_UP 1
#define ROAD_RIGHT 2
#define ROAD_DOWN 3
#define ROAD_NONE 4
	//----------------Tag------------------------
#define TAG_UPGRADE_ITEM 96
#define TAG_LABELPRICE 99
#define TAG_BULLET 98
#define TAG_ENEMY 97
	//----------------Priority-------------------
#define Priority_EventListenerPhysicsContact 10
	//----------------Z-Order--------------------
#define ZORDER_LABELPRICE 4
#define ZORDER_TEXT 11
#define ZORDER_MENU 10
#define ZORDER_MODAL 9
#define ZORDER_MENUITEMTOWER 8
#define ZORDER_TOWER 5
#define ZORDER_ENEMY 4
	//----------------PhysicsMask----------------
#define CategoryBitMask_Bullet		0x0000000F
#define CategoryBitMask_Barrier		0x000000F0
#define CategoryBitMask_Enemy		0x00000F00
#define CategoryBitMask_Assist		0x0FF00000

#define ContactTestBitMask_Bullet	0x00000F00
#define ContactTestBitMask_Barrier	0x00000000
#define ContactTestBitMask_Enemy	0x0F00000F
#define ContactTestBitMask_Assist	0x00000F00

#define CollisionBitMask_Bullet		0x00000F00
#define CollisionBitMask_Barrier	0x00F00F00
#define CollisionBitMask_Enemy		0x000000FF
#define CollisionBitMask_Assist		0x000000F0

#define CategoryBitMask_Bullet2		0x0F000000
#define CollisionBitMask_Bullet2	0x00000000

	//----------------Tower----------------------
#define MAX_RANGE 9999
	HCSVFile * towerData;
	//----------------Enemy----------------------
	HCSVFile * enemyData;
	HCSVFile * enemyDesc;
	Texture2D* hpBar;
	//----------------Props----------------------
	HCSVFile * propsData;
	//----------------Baby-----------------------
#define ANIMATION_BABY_LAUGH "baby_laugh"
#define ANIMATION_BABY_HAPPY "baby_happy"
#define ANIMATION_BABY_NORMAL "baby_normal"
#define ANIMATION_BABY_SAD "baby_sad"
#define ANIMATION_BABY_CRY "baby_cry"
#define ANIMATION_BABY_HURTING "baby_hurting"
#define ANIMATION_BABY_HURTED "baby_hurt"
#define ANIMATION_BABY_ANGRY "baby_angry"
#define ANIMATION_BABY_WIN "baby_win"
	//----------------Price-----------------------
#define FONTSIZE_PRICE 20
#define FONT_PRICE "fonts/cardFont.ttf"
	//-----------------Game-----------------------
#define PATH_TOWERBASE "images/tower/towerbase.png"
#define NUM_SECTIONS 4
	HCSVFile* sections;
	Texture2D* background_price;
	Texture2D* background_price_big;
public :
	static ResourceManager* getInstance();
	void init();

	void setBackgroundMusic(const bool isAllow);
	bool isBackgroundMusicAllow();

	void setEffectMusic(const bool isAllow);
	bool isEffectMusicAllow();

private:
	static ResourceManager* m_instance;

	bool m_backgroundMusicAllow;
	bool m_effectMusicAllow;

	ResourceManager();
	virtual ~ResourceManager();
	ResourceManager(const ResourceManager&);
	ResourceManager &operator = (const ResourceManager&);

	void loadAnimation();
	void loadAnimation(const char* mosterName, const char* direction, int size, float delay, const std::string &name);
	void loadAnimation(const char* fomat, int size, float delay, const std::string &name);
};

#endif