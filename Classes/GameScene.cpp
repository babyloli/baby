#include "GameScene.h"
#include "Enemy.h"
USING_NS_CC;
#define objPosX(obj) obj.at("x").asInt() + obj.at("width").asInt()/2
#define objPosY(obj) obj.at("y").asInt() + obj.at("height").asInt()/2

Scene* Game::createScene(){
	auto scene = Scene::create();
	auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(Game::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	m_map = TMXTiledMap::create("map1.tmx");
	this->addChild(m_map);

	TMXObjectGroup* peopleObjectGroup = m_map->getObjectGroup("people");	//读取对象层“people”
	ValueMap babyObject = peopleObjectGroup->getObject("baby");	//获取一个name为“baby”的对象
	int baby_x = objPosX(babyObject);	
	int baby_y = objPosY(babyObject);
	m_baby = Sprite::create("baby.png");	//用图片创建一个baby精灵
	m_baby->setPosition(baby_x, baby_y);	//设置精灵的位置
	this->addChild(m_baby);	//把精灵加到场景里

	ValueMap enemyObject = peopleObjectGroup->getObject("enemy");	//获取一个name为“baby”的对象
	m_enemyPosition = Vec2(objPosX(enemyObject),objPosY(enemyObject));	//enemy对象的起始位置

	TMXObjectGroup* towerObjectGroup = m_map->getObjectGroup("tower");	//读取对象层“tower”
	ValueVector towerObjects = towerObjectGroup->getObjects();	//获得“tower”对象层里面的所有对象
	SpriteBatchNode* towerbase = SpriteBatchNode::create("towerbase.png");	//用图片创建一个Batch
	towerbase->setPosition(Vec2::ZERO);	//设置这个Batch的位置
	this->addChild(towerbase);	//将这个Batch加到场景里
	for (ValueVector::iterator it = towerObjects.begin(); it != towerObjects.end(); it++){//对“tower”层里的每一个对象
		ValueMap towerObject = it->asValueMap();	//得到这个对象的属性
		int tower_x = objPosX(towerObject);
		int tower_y = objPosY(towerObject);
		Sprite* tower = Sprite::createWithTexture(towerbase->getTexture());	//用Batch创建一个精灵来表示可创建Tower的位置
		tower->setPosition(tower_x, tower_y);	//设置精灵的位置
		this->addChild(tower);	//把精灵加到场景里
		auto actionRepeateFadeOutIn = RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL));	//创建一个淡入淡出特效
		tower->runAction(actionRepeateFadeOutIn);	//给精灵赋予特效
	}

	this->scheduleOnce(schedule_selector(Game::addEnemy), 1.0f);
    return true;
}

void Game::addEnemy(float dt){
	Enemy* enemy = Enemy::create(VIRUS_TYPE_0);
	if (!enemy)
		return;
	enemy->setPosition(m_enemyPosition);
	this->addChild(enemy);
}

void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}