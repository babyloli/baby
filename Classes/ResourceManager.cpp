#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance = nullptr;

void ResourceManager::init(){
	enemyData = new HCSVFile();
	enemyData->openFile("data/monsters.csv");

	auto director = Director::getInstance();
	auto textureCache = director->getTextureCache();
	//--------------------SpriteFrameCache---------------------------
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("images/enemy/Monsters.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/baby/baby1.plist");
	loadAnimation();

	//---------------------Texture----------------------------
	tower0 = textureCache->addImage("images/tower/tower0.png");
	tower1 = textureCache->addImage("images/tower/tower0.png");
	background_price = textureCache->addImage("images/priceBackground.png");
	background_price_big = textureCache->addImage("images/priceBackground2.png");
	hpBar = textureCache->addImage("images/enemy/Maxhpbar.png");
	bullet_0_1 = textureCache->addImage("images/tower/bullet_0_1.png");
	bullet_0_2 = textureCache->addImage("images/tower/bullet_0_1.png");
	bullet_0_3 = textureCache->addImage("images/tower/bullet_0_1.png");
}

void ResourceManager::loadAnimation(const char* mosterName, const char* direction, int size, float delay, const std::string &name){
	auto animationCache = AnimationCache::getInstance();
	char str[100] = {0};
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i <= size; i++){
		sprintf_s(str, "%s%s%1d.png", mosterName, direction, i);
		spriteFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(spriteFrames, delay), name);
}

void ResourceManager::loadAnimation(const char* fomat, int size, float delay, const std::string &name){
	auto animationCache = AnimationCache::getInstance();
	char str[100] = {0};
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i <= size; i++){
		sprintf_s(str, fomat, i);
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
}

ResourceManager* ResourceManager::getInstance(){
	if (!m_instance){
		m_instance = new ResourceManager();
	}
	return m_instance;
}

ResourceManager::~ResourceManager()
{
	tower0->release();
	if (enemyData)
		delete enemyData;
};

ResourceManager::ResourceManager()
{
}
