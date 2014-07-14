#include "GameScene.h"
#include "ResourceManager.h"
#include "MenuItemTower.h"
USING_NS_CC;
#define objPosX(obj) obj.at("x").asInt() + obj.at("width").asInt()/2
#define objPosY(obj) obj.at("y").asInt() + obj.at("height").asInt()/2
#define objWidth(obj) obj.at("width").asFloat()
#define objHeight(obj) obj.at("height").asFloat()
#define MENU_ZORDER 10
#define TOWER_ZORDER 5

Scene* Game::createScene(){
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	auto layer = Game::create();
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	ResourceManager* rm = ResourceManager::getInstance();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));
	auto physicsItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuPhysicsCallback, this));
	physicsItem->setPosition(Vec2(origin.x + visibleSize.width - physicsItem->getContentSize().width/2 ,
		origin.y + visibleSize.height - physicsItem->getContentSize().height/2));
	auto menu = Menu::create(closeItem, physicsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	this->reorderChild(menu, MENU_ZORDER);

	m_map = TMXTiledMap::create("map1.tmx");
	this->addChild(m_map);

	TMXObjectGroup* peopleObjectGroup = m_map->getObjectGroup("people");	//��ȡ����㡰people��
	ValueMap babyObject = peopleObjectGroup->getObject("baby");	//��ȡһ��nameΪ��baby���Ķ���
	int baby_x = objPosX(babyObject);	
	int baby_y = objPosY(babyObject);
	m_baby = Sprite::create("baby.png");	//��ͼƬ����һ��baby����
	m_baby->setPosition(baby_x, baby_y);	//���þ����λ��
	this->addChild(m_baby);	//�Ѿ���ӵ�������

	ValueMap enemyObject = peopleObjectGroup->getObject("enemy");	//��ȡһ��nameΪ��enemy���Ķ���
	m_enemyPosition = Vec2(objPosX(enemyObject),objPosY(enemyObject));	//enemy�������ʼλ��

	SpriteBatchNode* towerbase = SpriteBatchNode::create("towerbase.png");	//��ͼƬ����һ��Batch
	towerbase->setPosition(Vec2::ZERO);	//�������Batch��λ��
	this->addChild(towerbase);	//�����Batch�ӵ�������

	TMXObjectGroup* towerObjectGroup = m_map->getObjectGroup("tower");	//��ȡ����㡰tower��
	ValueVector towerObjects = towerObjectGroup->getObjects();	//��á�tower���������������ж���
	int i = 0;
	for (ValueVector::iterator it = towerObjects.begin(); it != towerObjects.end(); it++, i++){//�ԡ�tower�������ÿһ������
		ValueMap towerObject = it->asValueMap();	//�õ�������������
		int tower_x = objPosX(towerObject);
		int tower_y = objPosY(towerObject);
		Sprite* tower = Sprite::createWithTexture(towerbase->getTexture());	//��Batch����һ����������ʾ�ɴ���Tower��λ��
		tower->setPosition(tower_x, tower_y);	//���þ����λ��
		towerbase->addChild(tower);	//�Ѿ���ӵ�������
		auto actionRepeateFadeOutIn = RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL));	//����һ�����뵭����Ч
		tower->runAction(actionRepeateFadeOutIn);	//�����鸳����Ч
		
		auto towerItemSprite = Sprite::createWithTexture(rm->tower0);
		auto towerItem = MenuItemTower::create(100, towerItemSprite, towerItemSprite, CC_CALLBACK_1(Game::towerCreateCallback, this, TOWER_TYPE_0, tower));
		towerItem->setPosition(Vec2::ZERO);
		auto menu = Menu::create(towerItem, NULL);
//		menu->setPosition(Vec2(tower->getPositionX(), tower->getPositionY()));
		menu->setPosition(Vec2(tower->getPositionX(),
			tower->getPositionY() + tower->getContentSize().height / 2 + towerItem->getContentSize().height / 2));
		m_menus.pushBack(menu);

		auto listener = EventListenerTouchOneByOne::create();	//����������
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [i, tower, this](Touch* touch, Event* event){
 			auto target = event->getCurrentTarget();
			if (tower->getTextureRect().containsPoint(target->convertTouchToNodeSpace(touch))){
//				tower->stopAction(actionRepeateFadeOutIn);
				Menu* menu = this->m_menus.at(i);
				if (menu->getParent() == NULL){
					this->addChild(menu);
					this->reorderChild(menu, MENU_ZORDER);
				}
			}
			else
			{
				Menu* menu = this->m_menus.at(i);
				this->removeChild(menu, false);
			}
			return false;
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, tower);
	}
	i = 0;

	TMXObjectGroup* roadObjectGroup = m_map->getObjectGroup("road");	//��ȡ����㡰road��
	ValueVector roadObjects = roadObjectGroup->getObjects();	//��á�road���������������ж���
	for (ValueVector::iterator it = roadObjects.begin(); it != roadObjects.end(); it++)//�ԡ�road�������ÿһ������
	{
		ValueMap roadObject = it->asValueMap();	//�õ�������������
		std::string directionStr = roadObject.at("direction").asString();
		int direction;
		if ("left" == directionStr){
			direction = LEFT;
		} else if ("up" == directionStr) {
			direction = UP;
		} else if ("right" == directionStr) {
			direction = RIGHT;
		} else {
			direction = DOWN;
		}
		m_roads.push_back(Road(roadObject.at("x").asFloat(), roadObject.at("y").asFloat(),
			objWidth(roadObject), objHeight(roadObject),
			direction));	//����������������δ��浽������
	}

	PhysicsMaterial staticMaterial(PHYSICS_INFINITY, 0, 0.5f);
	TMXObjectGroup* barrierObjectGroup = m_map->getObjectGroup("barrier");	//��ȡ����㡰barrier��
	ValueVector barrierObjects = barrierObjectGroup->getObjects();	//��á�barrier���������������ж���
	for (ValueVector::iterator it = barrierObjects.begin(); it != barrierObjects.end(); it++)//�ԡ�barrier�������ÿһ������
	{
		ValueMap barrierObject = it->asValueMap();	//�õ�������������
		Node* node = Node::create();
		auto body = PhysicsBody::createBox(Size(objWidth(barrierObject), objHeight(barrierObject)), staticMaterial);
		body->setDynamic(false);
		node->setPhysicsBody(body);
		node->setPosition(objPosX(barrierObject), objPosY(barrierObject));
		this->addChild(node);
	}

	this->schedule(schedule_selector(Game::findEnemy), 1.0f);
	this->schedule(schedule_selector(Game::addEnemy), 2.0f);
	this->schedule(schedule_selector(Game::moveEnemy), 0.5f);
	return true;
}

void Game::addEnemy(float dt)
{	
	Enemy* enemy = Enemy::create(VIRUS_TYPE_0);
	if (!enemy)
		return;
	enemy->setPosition(m_enemyPosition);
	this->addChild(enemy);
	m_enemies.pushBack(enemy);
}

void Game::moveEnemy(float dt){
	for (int i = 0; i < m_enemies.size(); i++){
		Enemy* enemy = m_enemies.at(i);

		Vec2 enemy_position = enemy->getPosition();
		for (std::vector<Road>::iterator it = m_roads.begin(); it != m_roads.end(); it++){
			if (it->containsPoint(enemy_position)){
			//	enemy->runAction(MoveBy::create(0.5f, it->getDirection() * enemy->getSpeed()));
				enemy->setVelocity(it->getDirection() * enemy->getSpeed());
				break;
			}
		}
	}
}

void Game::findEnemy(float dt){
	for (int i = 0; i < m_towers.size(); i++){
		Tower* tower = m_towers.at(i);
		tower->generateBullet();
	}
}

void Game::onEnter(){
	Layer::onEnter();
//	auto listener = EventListenerPhysicsContactWithGroup::create();
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

void Game::menuPhysicsCallback(cocos2d::Ref* pSender)
{
	if (m_physicsWorld->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)
		m_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	else
	{
		m_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void Game::towerCreateCallback(cocos2d::Ref* pSender, int type, Sprite* towerbase){
	Node* menuItemTower = static_cast<Node*>(pSender);
	Node* menu = menuItemTower->getParent();
	menu->removeFromParentAndCleanup(false);

	Tower* tower = Tower::create(type);
	if(!tower)
		return;
	tower->setPosition(towerbase->getPosition());
	this->addChild(tower);
	this->reorderChild(tower, TOWER_ZORDER);
	this->m_towers.pushBack(tower);
	towerbase->removeFromParentAndCleanup(true);
}

//------------------get/sets-----------------------------

void Game::setPhysicsWorld(PhysicsWorld* world){
	m_physicsWorld = world;
}


Vector<Enemy*> Game::getEnemies()
{
	return this->m_enemies;
}

