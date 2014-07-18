#include "GameScene.h"
#include "ResourceManager.h"
#include "MenuItemTower.h"
#include "HelloWorldScene.h"
#include "Utils.h"
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

	auto physicsItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuPhysicsCallback, this));
	physicsItem->setPosition(Vec2(origin.x + visibleSize.width - physicsItem->getContentSize().width/2 ,
		origin.y + visibleSize.height - physicsItem->getContentSize().height));

	auto modalSprite = Sprite::create("images/modalLayer.png");
	modalSprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	modalSprite->setVisible(false);
	this->addChild(modalSprite, ZORDER_MODAL);
	
	auto stopItem = MenuItemImage::create("stop.png", "stop.png", [=](cocos2d::Ref* pSender){
	if(!Director::getInstance()->isPaused()){
		Director::getInstance()->pause();
		MenuItem* menuItem = static_cast<MenuItem*>(pSender);
		menuItem->setVisible(false);
		m_goItem->setVisible(true);
		m_restartItem->setVisible(true);
		m_backItem->setVisible(true);
		modalSprite->setVisible(true);
		auto listener1 = EventListenerTouchOneByOne::create();//����һ����������    
		listener1->setSwallowTouches(true);//���ò������´��ݴ���  true�ǲ��� Ĭ��Ϊfalse  
		listener1->onTouchBegan = [](Touch* touch, Event* event){   
			return true;   
		};    
		listener1->onTouchMoved = [](Touch* touch, Event* event){      
		};    

		listener1->onTouchEnded = [](Touch* touch, Event* event){    
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, modalSprite);
	}});
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
		modalSprite->setVisible(false);
		this->_eventDispatcher->removeEventListenersForTarget(modalSprite);
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

	auto menu = Menu::create(physicsItem, stopItem, m_goItem, m_restartItem, m_backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	this->reorderChild(menu, ZORDER_MENU);

	m_money = INIT_PRICE;
	m_labelPrice = LabelPrice::create(rm->background_price_big, m_money);
	m_labelPrice->setPosition(origin.x + m_labelPrice->getContentSize().width/2, origin.y + 
		visibleSize.height - m_labelPrice->getContentSize().height);
	this->addChild(m_labelPrice, ZORDER_LABELPRICE);

	m_map = TMXTiledMap::create(MAP1);
	this->addChild(m_map);

	TMXObjectGroup* peopleObjectGroup = m_map->getObjectGroup("people");	//��ȡ����㡰people��
	ValueMap babyObject = peopleObjectGroup->getObject("baby");	//��ȡһ��nameΪ��baby���Ķ���
	float baby_x = babyObject.at("x").asFloat();
	float baby_y = babyObject.at("y").asFloat();
	float baby_width = objWidth(babyObject);
	float baby_height = objHeight(babyObject);
	m_baby = Baby::create();	//��ͼƬ����һ��baby����
	m_baby->m_position = Rect(baby_x, baby_y, baby_width, baby_height);
	m_baby->setPosition(objPosX(babyObject), objPosY(babyObject));	//���þ����λ��
	this->addChild(m_baby);	//�Ѿ���ӵ�������

	ValueMap enemyObject = peopleObjectGroup->getObject("enemy");	//��ȡһ��nameΪ��enemy���Ķ���
	m_enemyPosition = Vec2(objPosX(enemyObject),objPosY(enemyObject));	//enemy�������ʼλ��

	SpriteBatchNode* towerbase = SpriteBatchNode::create(PATH_TOWERBASE);	//��ͼƬ����һ��Batch
	towerbase->setPosition(Vec2::ZERO);	//�������Batch��λ��
	this->addChild(towerbase, ZORDER_TOWER);	//�����Batch�ӵ�������

	TMXObjectGroup* towerObjectGroup = m_map->getObjectGroup("tower");	//��ȡ����㡰tower��
	ValueVector towerObjects = towerObjectGroup->getObjects();	//��á�tower���������������ж���
	int towerId = 0;
	for (ValueVector::iterator it = towerObjects.begin(); it != towerObjects.end(); it++, towerId++){//�ԡ�tower�������ÿһ������
		ValueMap towerObject = it->asValueMap();	//�õ�������������
		int tower_x = objPosX(towerObject);
		int tower_y = objPosY(towerObject);
		Sprite* tower = Sprite::createWithTexture(towerbase->getTexture());	//��Batch����һ����������ʾ�ɴ���Tower��λ��
		tower->setPosition(tower_x, tower_y);	//���þ����λ��
		towerbase->addChild(tower);	//�Ѿ���ӵ�������
//		auto actionRepeateFadeOutIn = RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL));	//����һ�����뵭����Ч
//		tower->runAction(actionRepeateFadeOutIn);	//�����鸳����Ч

		auto menu = Menu::create();
		std::string type = towerObject.at("type").asString();
		std::vector<std::string> types;
		split(type, ",", &types);
		for (int j = 0; j < types.size(); j++)
		{
			int temp = std::atoi(types.at(j).c_str());
			Sprite* towerItemSprite = NULL;
			switch (temp)
			{
			case 0:
				towerItemSprite = Sprite::createWithTexture(rm->tower0);
				break;
			case 1:
				towerItemSprite = Sprite::createWithTexture(rm->tower1);
				break;
			}
			if (towerItemSprite){
				auto towerItem = MenuItemTower::create(Tower::getPrice(temp, 1), towerItemSprite, towerItemSprite,
					CC_CALLBACK_1(Game::towerCreateCallback, this, temp, tower, towerId));
				towerItem->setPosition(Vec2(j * towerItem->getContentSize().width,0));//
				menu->addChild(towerItem);
			}			
		}
		menu->setPosition(Vec2(tower->getPositionX(), tower->getPositionY() + tower->getContentSize().height));
		m_menus.pushBack(menu);

		Sprite* updateSprite = Sprite::create("update.png");
		auto upgradeItem = MenuItemTower::create(0, updateSprite, updateSprite, CC_CALLBACK_1(Game::towerUpgradeCallback, this, towerId));
//		upgradeItem->setPosition(-upgradeItem->getContentSize().width/2, upgradeItem->getContentSize().height/2);
		upgradeItem->setPosition(0, upgradeItem->getContentSize().height);
		upgradeItem->setTag(TAG_UPGRADE_ITEM);
		
		auto deleteItem = MenuItemImage::create("sell.png", "sell.png", CC_CALLBACK_1(Game::towerDeleteCallback, this, towerId, tower));
//		deleteItem->setPosition(-deleteItem->getContentSize().width/2, -deleteItem->getContentSize().height/2);
		deleteItem->setPosition(0, -deleteItem->getContentSize().height);

		auto uMenu = Menu::create(upgradeItem, deleteItem, NULL);
		uMenu->setPosition(tower->getPosition());
		m_upgradeMenus.pushBack(uMenu);

		auto listener = EventListenerTouchOneByOne::create();	//����������
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [towerId, tower, this](Touch* touch, Event* event){
 			auto target = event->getCurrentTarget();
			if (tower->getTextureRect().containsPoint(target->convertTouchToNodeSpace(touch))){
//				tower->stopAction(actionRepeateFadeOutIn);
				Menu* menu = this->m_menus.at(towerId);
				if (menu->getParent() == NULL){
					for (Node* node : menu->getChildren())
					{
						MenuItemTower* item = dynamic_cast<MenuItemTower*>(node);
						if (item){
							if (item->getPrice() > m_money){
								item->setEnabled(false);
							}else
							{
								item->setEnabled(true);
							}
						}
					}
					this->addChild(menu);
					this->reorderChild(menu, ZORDER_MENUITEMTOWER);
				}
			}
			else
			{
				Menu* menu = this->m_menus.at(towerId);
				this->removeChild(menu, false);
			}
			return false;
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, tower);
	}
	towerId = 0;

	TMXObjectGroup* roadObjectGroup = m_map->getObjectGroup("road");	//��ȡ����㡰road��
	ValueVector roadObjects = roadObjectGroup->getObjects();	//��á�road���������������ж���
	for (ValueVector::iterator it = roadObjects.begin(); it != roadObjects.end(); it++)//�ԡ�road�������ÿһ������
	{
		ValueMap roadObject = it->asValueMap();	//�õ�������������
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
 	this->schedule(schedule_selector(Game::moveEnemy), 0.5f);
 	this->schedule(schedule_selector(Game::deleteObject), 0.5f);
	return true;
}

void Game::update(float dt){
//	deleteObject(dt);
//	moveEnemy(dt);
	findEnemy(dt);
}

void Game::addEnemy(float dt)
{	
	Enemy* enemy = Enemy::create("ascarid");
	if (!enemy)
		return;
	enemy->setPosition(m_enemyPosition);
	this->addChild(enemy);
	m_enemies.pushBack(enemy);
}

void Game::moveEnemy(float dt){
	for (int i = 0; i < m_enemies.size(); i++){		//��ÿ��enemy
		Enemy* enemy = m_enemies.at(i);
		if (enemy->isDie()){	//���������
			this->addMoney(enemy->getPrice());	//��ô�������Ǯ
			enemy->removeFromParent();	//Ȼ��Ͱ���������
			m_enemies.eraseObject(enemy);	//������ҲҪ�ͷ�Ŷ
		}else{	//�����û��
			Vec2 enemy_position = enemy->getPosition();	//��������λ��
			if (m_baby->m_position.containsPoint(enemy_position)){	//�������Baby��
				bool gameover = m_baby->setDamage(enemy->getDamage());	//��Baby��Ѫ����������
				enemy->removeFromParent();	//��enemy������
				m_enemies.eraseObject(enemy);	//������ҲҪ�ͷ�Ŷ
				m_baby->hurt();	//Babyʹ��һ��
				if (gameover)
				{
					//TODO-------------------------------------------------------------------------------------
				}
			} 
			else
			{	//�������ڵ�road�����ٶȣ�����
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
//			bullet->getPhysicsBody()->setCategoryBitmask(CategoryBitMask_Bullet2);
//			bullet->getPhysicsBody()->setCollisionBitmask(CollisionBitMask_Bullet2);
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

void Game::towerCreateCallback(cocos2d::Ref* pSender, int type, Sprite* towerbase, int menuId){
	MenuItemTower* menuItemTower = static_cast<MenuItemTower*>(pSender);	//ת��ΪMenuItmeTower����
	Node* menu = menuItemTower->getParent();	//�õ��˵�
	menu->removeFromParentAndCleanup(false);	//���ز˵�
	this->addMoney(-menuItemTower->getPrice());	//��Ǯ����

	Tower* tower = Tower::create(type);	//����һ����Ӧ���͵���
	if(!tower)
		return;
	tower->setTag(menuId);
	Vec2 towerPosition = towerbase->getPosition();	//�õ�����λ��
	tower->setPosition(towerPosition);	//��������λ��
	this->addChild(tower);	//�������볡��
	this->reorderChild(tower, ZORDER_TOWER);	//�����������ȼ�
	this->m_towers.pushBack(tower);	//������������
//	towerbase->removeFromParentAndCleanup(true);	//�������
	towerbase->retain();
	towerbase->removeFromParentAndCleanup(false);

 	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
		Tower* tower = static_cast<Tower*>(event->getCurrentTarget());
		float width = tower->getContentSize().width;
		float height = tower->getContentSize().height;
		Rect rect = Rect(-width/2, -height/2, width, height);
		Vec2 point = tower->convertTouchToNodeSpace(touch);
		if (rect.containsPoint(point)){
			auto upgradeMenu = m_upgradeMenus.at(menuId);
			if (upgradeMenu->getParent() == NULL){
				MenuItemTower* menuItemTower = static_cast<MenuItemTower*>(upgradeMenu->getChildByTag(TAG_UPGRADE_ITEM));
				int level = tower->getlevel() + 1;
				if (level > 3){
					menuItemTower->setEnabled(false);
				} else
				{
					int price = tower->getPrice(tower->getType(), level);
					menuItemTower->setPrice(price);
					if (price > m_money)
						menuItemTower->setEnabled(false);
					else
					{
						menuItemTower->setEnabled(true);
					}
				}
				tower->showRange(true);
 				this->addChild(upgradeMenu);
 				this->reorderChild(upgradeMenu, ZORDER_MENUITEMTOWER);
//				tower->addChild(upgradeMenu);
			}
		}
		else
		{
			tower->showRange(false);
			auto upgradeMenu = m_upgradeMenus.at(menuId);
			this->removeChild(upgradeMenu, false);
//			tower->removeChild(upgradeMenu, false);
		}
		return false;
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, tower);
}

void Game::towerUpgradeCallback(cocos2d::Ref* pSender, int towerId)
{
	auto menu = m_upgradeMenus.at(towerId);
	menu->removeFromParentAndCleanup(false);
	Tower* tower = static_cast<Tower*>(this->getChildByTag(towerId));
	tower->upgrade();
	this->addMoney(-tower->getPrice(tower->getType(), tower->getlevel()));
}

void Game::towerDeleteCallback(cocos2d::Ref* pSender, int towerId, Sprite* towerbase)
{
	auto menu = m_upgradeMenus.at(towerId);
	menu->removeFromParentAndCleanup(false);
	this->addChild(towerbase);
	towerbase->release();
	Tower* tower = static_cast<Tower*>(this->getChildByTag(towerId));
	this->addMoney(tower->getPrice(tower->getType(), tower->getlevel()) * 0.5f);
	this->removeChild(tower);
	this->m_towers.eraseObject(tower);
}

//------------------get/sets-----------------------------

void Game::setPhysicsWorld(PhysicsWorld* world){
	m_physicsWorld = world;
}

Vector<Enemy*>& Game::getEnemies()
{
	return this->m_enemies;
}

void Game::addMoney(int money){
	m_money += money;
	m_labelPrice->setPrice(m_money);
}

void Game::addBullet(Bullet* bullet){
	m_bullets.pushBack(bullet);
}
