#include "StartScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* Start::createScene()
{
	auto scene = Scene::create();
	auto layer = Start::create();
	scene->addChild(layer);
	return scene;
}


bool Start::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Start::menuStartCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}


void Start::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void Start::menuStartCallback(cocos2d::Ref* pSender)
{
	auto game=Game::createScene();
	Director::getInstance()->replaceScene(game);
}