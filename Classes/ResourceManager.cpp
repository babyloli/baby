#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance = nullptr;

void ResourceManager::init(){
	m_backgroundMusicAllow = true;
	m_effectMusicAllow = true;

	enemyData = new HCSVFile();
	enemyData->openFile("data/monsters.csv");
	enemyDesc = new HCSVFile();
	enemyDesc->openFile("data/monsterDesign.csv");
	towerData = new HCSVFile();
	towerData->openFile("data/towerDesign.csv");
	propsData = new HCSVFile();
	propsData->openFile("data/Props.csv");
	sections = new HCSVFile[NUM_SECTIONS];
	for (int i = 1; i <= NUM_SECTIONS; i++){
		char str[20] = {0};
		sprintf(str, "data/gameData%1d.csv", i);
		sections[i-1].openFile(str);
	}

	auto director = Director::getInstance();
	auto textureCache = director->getTextureCache();
	//--------------------SpriteFrameCache---------------------------
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("images/enemy/Monsters.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/baby/baby1.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/tower/Towers.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/props/safetyguard.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/props/landmine.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/props/traps.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/props/assist.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/mouse/Mouse.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/enemy/ExplosionMonster.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/enemy/Killed.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/gameover/win.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/gameover/fail.plist");
	loadAnimation();

	//---------------------Texture----------------------------
	background_price = textureCache->addImage("images/priceBackground.png");
	background_price_big = textureCache->addImage("images/priceBackground2.png");
	hpBar = textureCache->addImage("images/enemy/Maxhpbar.png");

	//---------------------PreLoad Music and Effect sound------------
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC_MENU);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC_GAMESCENE_1);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC_GAMESCENE_2);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC_GAMESCENE_3);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC_GAMESCENE_4);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sceneSound/321go.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sceneSound/ohmygod.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sceneSound/ohno.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sceneSound/victory.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sceneSound/youwin.mp3");

	for (int i = 0; i < towerData->getRows(); i++) 
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(towerData->getData(i,17));
	}
}

void ResourceManager::loadAnimation(const char* mosterName, const char* direction, int size, float delay, const std::string &name){
	auto animationCache = AnimationCache::getInstance();
	char str[100] = {0};
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i <= size; i++){
		sprintf(str, "%s%s%1d.png", mosterName, "right", i);
		spriteFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(spriteFrames, delay), name);
}

void ResourceManager::loadAnimation(const char* fomat, int size, float delay, const std::string &name){
	auto animationCache = AnimationCache::getInstance();
	char str[100] = {0};
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i <= size; i++){
		sprintf(str, fomat, i);
		spriteFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(spriteFrames, delay), name);
}

void ResourceManager::loadAnimation(){
	for (int i = 0; i < enemyData->getRows(); i++){
		std::string monsterName = enemyData->getData(i, 2);
		const char* monsterNameCString = monsterName.c_str();
		int numOfFrames = std::atoi(enemyData->getData(i, 3));
		loadAnimation(monsterNameCString, "right", numOfFrames, 0.08f, monsterName+"right");
		loadAnimation(monsterNameCString, "up", numOfFrames, 0.08f, monsterName+"up");
		loadAnimation(monsterNameCString, "left", numOfFrames, 0.08f, monsterName+"left");
		loadAnimation(monsterNameCString, "down", numOfFrames, 0.08f, monsterName+"down");
	}
	loadAnimation("baby1laugh%1d.png", 6, 0.2f, ANIMATION_BABY_LAUGH);
	loadAnimation("baby1happy%1d.png", 6, 0.2f, ANIMATION_BABY_HAPPY);
	loadAnimation("baby1normal%1d.png", 6, 0.2f, ANIMATION_BABY_NORMAL);
	loadAnimation("baby1sad%1d.png", 6, 0.2f, ANIMATION_BABY_SAD);
	loadAnimation("baby1cry%1d.png", 6, 0.2f, ANIMATION_BABY_CRY);
	loadAnimation("baby1hurting%1d.png", 4, 0.2f, ANIMATION_BABY_HURTING);
	loadAnimation("baby1hurted%1d.png", 6, 0.2f, ANIMATION_BABY_HURTED);
	loadAnimation("baby1angry%1d.png", 6, 0.2f, ANIMATION_BABY_ANGRY);
	loadAnimation("baby1win%1d.png", 6, 0.2f, ANIMATION_BABY_WIN);

	loadAnimation("safebubble_state_0_%ld.png",3,0.2f,ANIMATION_SAFETYGUARD_STATE_1);
	loadAnimation("safebubble_state_1_%ld.png",3,0.2f,ANIMATION_SAFETYGUARD_STATE_2);
	loadAnimation("safebubble_state_2_%ld.png",3,0.2f,ANIMATION_SAFETYGUARD_STATE_3);
	loadAnimation("landmine_ create_%ld.png",5,0.15f,ANIMATION_LANDMINE_CREATE);
	loadAnimation("landmine_invalidable_%ld.png",3,0.1f,ANIMATION_LANDMINE_INVALIDABLESET);
	loadAnimation("landmine_waiting_%ld.png",4,0.1f,ANIMATION_LANDMINE_WAIT);
	loadAnimation("landmine_bomb_%ld.png",5,0.1f,ANIMATION_LANDMINE_BOMB);
	loadAnimation("trap_state_3_%ld.png",3,0.1f,ANIMATION_TRAP_STATE_1);
	loadAnimation("trap_state_2_%ld.png",3,0.1f,ANIMATION_TRAP_STATE_2);
	loadAnimation("trap_state_1_%ld.png",3,0.1f,ANIMATION_TRAP_STATE_3);
	loadAnimation("oryzae%ld.png",6,0.1f,ANIMATION_ASSISTANT);

	loadAnimation("mouse%d.png",10,0.15f,ANIMATION_MOUSE);
	loadAnimation("explosion%d.png",6,0.1f,ANIMATION_EXPLOSION);
	loadAnimation("killed%ld.png",3,0.08f,ANIMATION_KILLED);
	loadAnimation("win%ld.png",10,0.1f,ANIMAITON_WIN);
	loadAnimation("fail%ld.png",9,0.1f,ANIMATION_FAIL);
}

ResourceManager* ResourceManager::getInstance(){
	if (!m_instance){
		m_instance = new ResourceManager();
	}
	return m_instance;
}

ResourceManager::~ResourceManager()
{
	if (enemyData)
		delete enemyData;
	if (enemyDesc)
		delete enemyDesc;
	if (towerData)
		delete towerData;
	if (propsData)
		delete propsData;
	if (sections)
		delete [] sections;
};

ResourceManager::ResourceManager()
{
}

void ResourceManager::setBackgroundMusic(const bool isAllow)
{
	m_backgroundMusicAllow = isAllow;
}

void ResourceManager::setEffectMusic(const bool isAllow)
{
	m_effectMusicAllow = isAllow;
}


bool ResourceManager::isBackgroundMusicAllow()
{
	return m_backgroundMusicAllow;
}

bool ResourceManager::isEffectMusicAllow()
{
	return m_effectMusicAllow;
}
