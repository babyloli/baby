#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance = nullptr;
std::string ResourceManager::ANIMATION_WALK_0 = "walk";

void ResourceManager::init(){
	auto director = Director::getInstance();
	auto textureCache = director->getTextureCache();
	//--------------------SpriteFrameCache---------------------------
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("icedog.plist");
	//--------------------AnimationCache-----------------------------
	auto animationCache = AnimationCache::getInstance();
	Vector<SpriteFrame*> walkFrames_0(4);
	char str[100] = {0};  
	for (int i = 1; i <= 4; i++)  
	{  
		sprintf(str, "Albinism_right%1d.png",i);  
		auto frame = spriteFrameCache->getSpriteFrameByName( str );
		walkFrames_0.pushBack(frame);  
	}  
	// Creating walk animation  
	auto *walkAnimation_0 = Animation::createWithSpriteFrames(walkFrames_0, 1.0f / 12.0f);  
	animationCache->addAnimation(walkAnimation_0, ANIMATION_WALK_0);

	//---------------------Texture----------------------------
	tower0 = textureCache->addImage("tower0.png");
	baby = textureCache->addImage("baby.png");
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
