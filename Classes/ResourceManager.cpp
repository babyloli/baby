#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance = nullptr;

void ResourceManager::init(){
	auto director = Director::getInstance();
	auto textureCache = director->getTextureCache();
	//--------------------SpriteFrameCache---------------------------
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("images/enemy/icedog.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/baby/baby1.plist");
	loadAnimation();

	//---------------------Texture----------------------------
	tower0 = textureCache->addImage("images/tower/tower0.png");
	tower1 = textureCache->addImage("images/tower/tower0.png");
	background_price = textureCache->addImage("images/priceBackground.png");
	background_price_big = textureCache->addImage("images/priceBackground2.png");
	hpBar = textureCache->addImage("images/enemy/Maxhpbar.png");
	bullet_0_1 = textureCache->addImage("images/tower/bullet_0_1.png");
}

void ResourceManager::loadAnimation(const char* format, int size, float delay, const std::string &name){
	auto animationCache = AnimationCache::getInstance();
	char str[100] = {0};
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i <= size; i++){
		sprintf_s(str, format, i);
		spriteFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(spriteFrames, delay), name);
}

void ResourceManager::loadAnimation(){
	loadAnimation("Albinism_right%1d.png", 4, 1.0f/12.0f, ANIMATION_WALK_RIGHT_0);
	loadAnimation("Albinism_up%1d.png", 4, 1.0f/12.0f, ANIMATION_WALK_UP_0);
	loadAnimation("Albinism_left%1d.png", 4, 1.0f/12.0f, ANIMATION_WALK_LEFT_0);
	loadAnimation("Albinism_down%1d.png", 4, 1.0f/12.0f, ANIMATION_WALK_DOWN_0);
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
};

ResourceManager::ResourceManager()
{
}
