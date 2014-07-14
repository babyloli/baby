#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance = nullptr;

void ResourceManager::init(){
	auto director = Director::getInstance();
	auto textureCache = director->getTextureCache();

	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("icedog.plist");
//----------------Tower----------------------
	tower0 = textureCache->addImage("tower0.png");
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
