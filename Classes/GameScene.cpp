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

	TMXObjectGroup* peopleObjectGroup = m_map->getObjectGroup("people");	//��ȡ����㡰people��
	ValueMap babyObject = peopleObjectGroup->getObject("baby");	//��ȡһ��nameΪ��baby���Ķ���
	int baby_x = objPosX(babyObject);	
	int baby_y = objPosY(babyObject);
	m_baby = Sprite::create("baby.png");	//��ͼƬ����һ��baby����
	m_baby->setPosition(baby_x, baby_y);	//���þ����λ��
	this->addChild(m_baby);	//�Ѿ���ӵ�������

	ValueMap enemyObject = peopleObjectGroup->getObject("enemy");	//��ȡһ��nameΪ��baby���Ķ���
	Vec2 enemyPosition(objPosX(enemyObject),objPosY(enemyObject));	//enemy�������ʼλ��

	TMXObjectGroup* towerObjectGroup = m_map->getObjectGroup("tower");	//��ȡ����㡰tower��
	ValueVector towerObjects = towerObjectGroup->getObjects();	//��á�tower���������������ж���
	SpriteBatchNode* towerbase = SpriteBatchNode::create("towerbase.png");	//��ͼƬ����һ��Batch
	towerbase->setPosition(Vec2::ZERO);	//�������Batch��λ��
	this->addChild(towerbase);	//�����Batch�ӵ�������
	for (ValueVector::iterator it = towerObjects.begin(); it != towerObjects.end(); it++){//�ԡ�tower�������ÿһ������
		ValueMap towerObject = it->asValueMap();	//�õ�������������
		int tower_x = objPosX(towerObject);
		int tower_y = objPosY(towerObject);
		Sprite* tower = Sprite::createWithTexture(towerbase->getTexture());	//��Batch����һ����������ʾ�ɴ���Tower��λ��
		tower->setPosition(tower_x, tower_y);	//���þ����λ��
		this->addChild(tower);	//�Ѿ���ӵ�������
		auto actionRepeateFadeOutIn = RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL));	//����һ�����뵭����Ч
		tower->runAction(actionRepeateFadeOutIn);	//�����鸳����Ч
	}

//	auto enemy=Enemy::create();
// 	enemy->setTag(123);
// 	enemy->SetObjectGroup(map->getObjectGroup("OBJ"));
// 	enemy->InitWayPoints(0);
// 	enemy->setOriSpeed(10);
// 	this->addChild(enemy);
// 	enemy->runbyWay();
    return true;
}

void Game::menuCloseCallback(Ref* pSender)
{
	Enemy* a=(Enemy*)getChildByTag(123);
	a->changeSpeed(10);
}