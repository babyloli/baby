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
#define TAG_ASSISTANT 95
	//----------------Priority-------------------
#define Priority_EventListenerPhysicsContact 10
	//----------------Z-Order--------------------
#define ZORDER_LABELPRICE 4
#define ZORDER_TEXT 11
#define ZORDER_MENU 10
#define ZORDER_MODAL 9
#define ZORDER_MENUITEMTOWER 8
#define ZORDER_PROPS 7
#define ZORDER_TOWER 6
#define ZORDER_BIGBOSS 5
#define ZORDER_ENEMY 4
	//----------------PhysicsMask----------------
#define CategoryBitMask_Bullet		0x0000000F
#define CategoryBitMask_Bullet2		0x0F000000
#define CategoryBitMask_Barrier		0x000000F0
#define CategoryBitMask_Enemy		0x00000F00
#define CategoryBitMask_Assist		0x0FF00000
#define CategoryBitMask_Boss		0x00000F00

#define ContactTestBitMask_Bullet	0x00000F00
#define ContactTestBitMask_Bullet2	0x00000F00
#define ContactTestBitMask_Barrier	0x00000000
#define ContactTestBitMask_Enemy	0x0F00000F
#define ContactTestBitMask_Assist	0x00000F00
#define ContactTestBitMask_Boss		0X0F00000F

#define CollisionBitMask_Bullet		0x00000F00
#define CollisionBitMask_Bullet2	0x00000000
#define CollisionBitMask_Barrier	0x00F00F00
#define CollisionBitMask_Enemy		0x000000FF
#define CollisionBitMask_Assist		0x000000F0
#define CollisionBitMask_Boss		0X000000F0

	//----------------Tower----------------------
#define MAX_RANGE 9999
	HCSVFile * towerData;
	//----------------Enemy----------------------
#define ANIMATION_EXPLOSION "animation_explosion"
#define ANIMATION_KILLED "animation_killed"
	HCSVFile * enemyData;
	HCSVFile * enemyDesc;
	Texture2D* hpBar;
	//----------------Props----------------------
#define TYPE_PROPS 200
#define TYPE_PROP_RESTOREHP 201
#define TYPE_PROP_SLOWDOWN 202
#define TYPE_PROP_SAFETYGUARD 203
#define TYPE_PROP_LANDMIND 204
#define TYPE_PROP_TRAP 205
#define TYPE_PROP_ASSISTGUARD 206
#define ANIMATION_SAFETYGUARD_STATE_1 "safeguard_state_1"
#define ANIMATION_SAFETYGUARD_STATE_2 "safeguard_state_2"
#define ANIMATION_SAFETYGUARD_STATE_3 "safeguard_state_3"
#define ANIMATION_LANDMINE_CREATE "landmine_create"
#define ANIMATION_LANDMINE_INVALIDABLESET "landmine_invalidableset"
#define ANIMATION_LANDMINE_WAIT "landmine_wait"
#define ANIMATION_LANDMINE_BOMB "landmine_bomb"
#define ANIMATION_TRAP_STATE_1 "trap_state_1"
#define ANIMATION_TRAP_STATE_2 "trap_state_2"
#define ANIMATION_TRAP_STATE_3 "trap_state_3"
#define ANIMATION_ASSISTANT "assistant"
#define UI_POSITION_RESTOREHP 221
#define UI_POSITION_SLOWDOWN 222
#define UI_POSITION_SAFEGUARD 223
#define UI_POSITION_LANDMINE 224
#define UI_POSITION_TRAP 225
#define UI_POSITION_ASSISTGUARD 226
#define  TAG_SLOWSNOW 288
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
#define FONT_GOLD "fonts/number.fnt"
	//-----------------Game-----------------------
#define PATH_TOWERBASE "images/tower/towerbase.png"
#define NUM_SECTIONS 4
#define ANIMATION_MOUSE "animation_mouse"
#define ANIMAITON_WIN "animation_win"
#define ANIMATION_FAIL "animation_fail"
#define TILESIZE 80
		//----------------Music-------------
#define BACKGROUND_MUSIC_MENU "music/MenuBackgroundMusic.mp3"
#define BACKGROUND_MUSIC_GAMESCENE_1 "music/GameSceneMusic0.mp3"
#define BACKGROUND_MUSIC_GAMESCENE_2 "music/GameSceneMusic1.mp3"
#define BACKGROUND_MUSIC_GAMESCENE_3 "music/GameSceneMusic2.mp3"
#define BACKGROUND_MUSIC_GAMESCENE_4 "music/GameSceneMusic3.mp3"

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