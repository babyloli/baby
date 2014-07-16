#include "GameScene.h"
#include "ResourceManager.h"
#include "MenuItemTower.h"
#include "HelloWorldScene.h"
USING_NS_CC;
#define objPosX(obj) obj.at("x").asInt() + obj.at("width").asInt()/2
#define objPosY(obj) obj.at("y").asInt() + obj.at("height").asInt()/2
#define objWidth(obj) obj.at("width").asFloat()
#define objHeight(obj) obj.at("height").asFloat()

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
// 	auto closeItem = MenuItemImage::create("CloseNormal.png",
// 		"CloseSelected.png",
// 		CC_CALLBACK_1(Game::menuCloseCallback, this));
// 	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
// 		origin.y + closeItem->getContentSize().height/2));

	auto physicsItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuPhysicsCallback, this));
	physicsItem->setPosition(Vec2(origin.x + visibleSize.width - physicsItem->getContentSize().width/2 ,
		origin.y + visibleSize.height - physicsItem->getContentSize().height/2));

	auto stopItem = MenuItemImage::create("stop.png", "stop.png", 
		CC_CALLBACK_1(Game::menuStopCallback, this));
	stopItem->setPosition(Vec2(origin.x + visibleSize.width - stopItem->getContentSize().width/2 ,
		origin.y + stopItem->getContentSize().height*0.6));

	m_restartItem = MenuItemImage::create("restart.png", "restart.png", [](cocos2d::Ref* pSender){
		auto scene = Game::createScene();
		Director::getInstance()->replaceScene(scene);
		Director::getInstance()->resume();
	});
	m_restartItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	m_restartItem->setVisible(false);

	m_goItem = MenuItemImage::create("go.png", "go.png", [=](cocos2d::Ref* pSender){
		MenuItem* menuItem = static_cast<MenuItem*>(pSender);
		menuItem->setVisible(false);
		m_restartItem->setVisible(false);
		m_backItem->setVisible(false);
		stopItem->setVisible(true);
		Director::getInstance()->resume();
	});
	m_goItem->setPosition(Vec2(origin.x + visibleSize.width/2 + m_restartItem->getContentSize().width/2 +
		m_goItem->getContentSize().width, origin.y + visibleSize.height/2));
	m_goItem->setVisible(false);

	m_backItem = MenuItemImage::create("back.png", "back.png", [](cocos2d::Ref* pSender){
		auto scene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(scene);
		Director::getInstance()->resume();
	});
	m_backItem->setPosition(Vec2(origin.x + visibleSize.width/2 - m_restartItem->getContentSize().width/2 -
		m_backItem->getContentSize().width,	origin.y + visibleSize.height/2));
	m_backItem->setVisible(false);

	auto menu = Menu::create(/*closeItem,*/physicsItem, stopItem, m_goItem, m_restartItem, m_backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	this->reorderChild(menu, ZORDER_MENU);

	auto modalLayer = Sprite::create("modalLayer.png");
	modalLayer->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	auto modalLayer_touchListener = EventListenerTouchOneByOne::create();
	modalLayer_touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* unused_event){
		return true;
	};
	this->_eventDispatcher->addEventListenerWithFixedPriority(modalLayer_touchListener, -1);
	this->addChild(modalLayer, ZORDER_MENU - 1);

	m_map = TMXTiledMap::create(MAP1);
	this->addChild(m_map);

	TMXObjectGroup* peopleObjectGroup = m_map->getObjectGroup("people");	//读取对象层“people”
	ValueMap babyObject = peopleObjectGroup->getObject("baby");	//获取一个name为“baby”的对象
	float baby_x = babyObject.at("x").asFloat();
	float baby_y = babyObject.at("y").asFloat();
	float baby_width = objWidth(babyObject);
	float baby_height = objHeight(babyObject);
	m_baby = Baby::create();	//用图片创建一个baby精灵
	m_baby->m_position = Rect(baby_x, baby_y, baby_width, baby_height);
	m_baby->setPosition(objPosX(babyObject), objPosY(babyObject));	//设置精灵的位置
	this->addChild(m_baby);	//把精灵加到场景里

	ValueMap enemyObject = peopleObjectGroup->getObject("enemy");	//获取一个name为“enemy”的对象
	m_enemyPosition = Vec2(objPosX(enemyObject),objPosY(enemyObject));	//enemy对象的起始位置

	SpriteBatchNode* towerbase = SpriteBatchNode::create(PATH_TOWERBASE);	//用图片创建一个Batch
	towerbase->setPosition(Vec2::ZERO);	//设置这个Batch的位置
	this->addChild(towerbase);	//将这个Batch加到场景里

	TMXObjectGroup* towerObjectGroup = m_map->getObjectGroup("tower");	//读取对象层“tower”
	ValueVector towerObjects = towerObjectGroup->getObjects();	//获得“tower”对象层里面的所有对象
	int i = 0;
	for (ValueVector::iterator it = towerObjects.begin(); it != towerObjects.end(); it++, i++){//对“tower”层里的每一个对象
		ValueMap towerObject = it->asValueMap();	//得到这个对象的属性
		int tower_x = objPosX(towerObject);
		int tower_y = objPosY(towerObject);
		Sprite* tower = Sprite::createWithTexture(towerbase->getTexture());	//用Batch创建一个精灵来表示可创建Tower的位置
		tower->setPosition(tower_x, tower_y);	//设置精灵的位置
		towerbase->addChild(tower);	//把精灵加到场景里
		auto actionRepeateFadeOutIn = RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL));	//创建一个淡入淡出特效
		tower->runAction(actionRepeateFadeOutIn);	//给精灵赋予特效
		
		auto towerItemSprite = Sprite::createWithTexture(rm->tower0);
		auto towerItem = MenuItemTower::create(100, towerItemSprite, towerItemSprite, CC_CALLBACK_1(Game::towerCreateCallback, this, TOWER_TYPE_0, tower));
		towerItem->setPosition(Vec2::ZERO);
		auto menu = Menu::create(towerItem, NULL);
//		menu->setPosition(Vec2(tower->getPositionX(), tower->getPositionY()));
		menu->setPosition(Vec2(tower->getPositionX(),
			tower->getPositionY() + tower->getContentSize().height / 2 + towerItem->getContentSize().height / 2));
		m_menus.pushBack(menu);

		auto listener = EventListenerTouchOneByOne::create();	//触摸监听器
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [i, tower, this](Touch* touch, Event* event){
 			auto target = event->getCurrentTarget();
			if (tower->getTextureRect().containsPoint(target->convertTouchToNodeSpace(touch))){
//				tower->stopAction(actionRepeateFadeOutIn);
				Menu* menu = this->m_menus.at(i);
				if (menu->getParent() == NULL){
					this->addChild(menu);
					this->reorderChild(menu, ZORDER_MENU);
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

	TMXObjectGroup* roadObjectGroup = m_map->getObjectGroup("road");	//读取对象层“road”
	ValueVector roadObjects = roadObjectGroup->getObjects();	//获得“road”对象层里面的所有对象
	for (ValueVector::iterator it = roadObjects.begin(); it != roadObjects.end(); it++)//对“road”层里的每一个对象
	{
		ValueMap roadObject = it->asValueMap();	//得到这个对象的属性
		std::string directionStr = roadObject.at("direction").asString();
		int direction;
		if ("left" == directionStr){
			direction = ROAD_LEFT;
		} else if ("up" == directionStr) {
			direction = ROAD_UP;
		} else if ("right" == directionStr) {
			direction = ROAD_RIGHT;
		} else {
			direction = ROAD_DOWN;
		}
		m_roads.push_back(Road(roadObject.at("x").asFloat(), roadObject.at("y").asFloat(),
			objWidth(roadObject), objHeight(roadObject),
			direction));	//把这个对象看作长方形储存到数组里
	}

	PhysicsMaterial staticMaterial(PHYSICS_INFINITY, 0, 0.5f);
	TMXObjectGroup* barrierObjectGroup = m_map->getObjectGroup("barrier");	//读取对象层“barrier”
	ValueVector barrierObjects = barrierObjectGroup->getObjects();	//获得“barrier”对象层里面的所有对象
	for (ValueVector::iterator it = barrierObjects.begin(); it != barrierObjects.end(); it++)//对“barrier”层里的每一个对象
	{
		ValueMap barrierObject = it->asValueMap();	//得到这个对象的属性
		Node* node = Node::create();
		auto body = PhysicsBody::createBox(Size(objWidth(barrierObject), objHeight(barrierObject)), staticMaterial);
		body->setDynamic(false);
		body->setCategoryBitmask(CategoryBitMask_Barrier);
		body->setContactTestBitmask(ContactTestBitMask_Barrier);
		body->setCollisionBitmask(CollisionBitMask_Barrier);
		node->setPhysicsBody(body);
		node->setPosition(objPosX(barrierObject), objPosY(barrierObject));
		this->addChild(node);
	}

	this->scheduleUpdate();
// 	this->schedule(schedule_selector(Game::findEnemy), 1.0f);
 	this->schedule(schedule_selector(Game::addEnemy), 2.0f);
// 	this->schedule(schedule_selector(Game::moveEnemy), 0.5f);
// 	this->schedule(schedule_selector(Game::deleteObject), 1.0f);
	return true;
}

void Game::update(float dt){
	deleteObject(dt);
	moveEnemy(dt);
	findEnemy(dt);
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
		if (enemy->isDie()){
			enemy->removeFromParent();
			m_enemies.eraseObject(enemy);
		}else{
			Vec2 enemy_position = enemy->getPosition();
			if (m_baby->m_position.containsPoint(enemy_position)){
				bool gameover = m_baby->setDamage(enemy->getDamage());
				enemy->removeFromParent();
				m_enemies.eraseObject(enemy);
				m_baby->hurt();
				if (gameover)
				{
					//TODO-------------------------------------------------------------------------------------
				}
			} 
			else
			{
				for (std::vector<Road>::iterator it = m_roads.begin(); it != m_roads.end(); it++){
					if (it->containsPoint(enemy_position)){
						enemy->setVelocity(it->getDirectionVec2() * enemy->getSpeed());
						enemy->setDirection(it->getDirection());
						break;
					}
				}
			}
		}
	}
}

void Game::findEnemy(float dt){
	for (int i = 0; i < m_towers.size(); i++){
		Tower* tower = m_towers.at(i);
		tower->generateBullet(dt);
	}
}

void Game::deleteObject(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float minX = origin.x;
	float minY = origin.y;
	float maxX = minX + visibleSize.width;
	float maxY = minY + visibleSize.height;
	for (int i = 0; i < m_bullets.size(); i++){
		Bullet* bullet = m_bullets.at(i);
		float x = bullet->getPositionX();
		float y = bullet->getPositionY();
		if (bullet->isDie() || x < minX || x > maxX || y < minY || y > maxY)
		{
			bullet->removeFromParent();
			m_bullets.eraseObject(bullet);
		}
	}
}

void Game::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [this](PhysicsContact &contact)->bool{
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();
		Bullet* bullet = NULL;
		Enemy* enemy = NULL;
		int tagA = nodeA->getTag();
		int tagB = nodeB->getTag();
		if (TAG_BULLET == tagA && TAG_ENEMY == tagB){
			bullet = dynamic_cast<Bullet*>(nodeA);
			enemy = dynamic_cast<Enemy*>(nodeB);
		} else if (TAG_ENEMY == tagA && TAG_BULLET == tagB){
			bullet = dynamic_cast<Bullet*>(nodeB);
			enemy = dynamic_cast<Enemy*>(nodeA);
		}
		if (bullet && enemy){
			int damage = bullet->getDamage();
			enemy->setHp(enemy->getHp() - damage);
			bullet->setDie();
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(listener, Priority_EventListenerPhysicsContact);
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

void Game::menuStopCallback(cocos2d::Ref* pSender){
	if(!Director::getInstance()->isPaused()){
		Director::getInstance()->pause();
		MenuItem* menuItem = static_cast<MenuItem*>(pSender);
		menuItem->setVisible(false);
		m_goItem->setVisible(true);
		m_restartItem->setVisible(true);
		m_backItem->setVisible(true);
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
	this->reorderChild(tower, ZORDER_TOWER);
	this->m_towers.pushBack(tower);
	towerbase->removeFromParentAndCleanup(true);
}

//------------------get/sets-----------------------------

void Game::setPhysicsWorld(PhysicsWorld* world){
	m_physicsWorld = world;
}


Vector<Enemy*>& Game::getEnemies()
{
	return this->m_enemies;
}

void Game::addBullet(Bullet* bullet){
	m_bullets.pushBack(bullet);
}
