#include "GameScene.h"
#include "ResourceManager.h"
#include "MenuItemTower.h"
#include "ISubUIScene.h"
#include "Utils.h"
#include "Assistant.h"
#include <time.h>
USING_NS_CC;

Game::Game(int section, int id)
{
	m_section = section;
	m_id = id;
	m_countdown = 3;
	m_isGameOver = false;
	m_curRound = 0;
	m_isWaiting = true;
	m_curNumInRound = 0;
	m_elapsedTimeRound = 0;
	m_elapsedTimeMonster = 0;
}

Scene* Game::createScene(int section, int id){
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	auto layer = Game::create(section, id);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

Game* Game::create(int section, int id){
	Game *pRet = new Game(section, id); 
	if (pRet && pRet->init()) 
	{
		pRet->autorelease();
		return pRet;
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

bool Game::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	loadData();
	loadMap();
	loadToolBar();
	loadMenu();
	loadPeople();
	loadTower();
	loadRoadAndBarriers();
	loadEquipmentSlot();

	if(ResourceManager::getInstance()->isBackgroundMusicAllow()){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	srand((unsigned)time(NULL));

	this->scheduleUpdate(); //实现主循环调度
	this->schedule(schedule_selector(Game::moveAssistant), 0.5f);
	this->schedule(schedule_selector(Game::moveEnemy), 0.5f);
	this->schedule(schedule_selector(Game::deleteObject), 0.5f);
	this->schedule(schedule_selector(Game::countDown), 1.0f);
	this->schedule(schedule_selector(Game::meetTraps),0.5f);
	return true;	
}

void Game::update(float dt){
//	deleteObject(dt);
	addEnemy(dt);
//	moveEnemy(dt);
	findEnemy(dt);

	//减速道具在可用的情况下， 更新减速道具的目标怪兽
	auto sd = this->getChildByTag(TYPE_PROP_SLOWDOWN);
	auto slowdown = (PropsSlowdown*)sd;
	if(slowdown->isAvailable() && slowdown->getTargetsNumber() != m_enemies.size()){
		slowdown->setSlowdownTargets(m_enemies);
	}

}

void Game::loadData(){
	HCSVFile* enemyDesc = ResourceManager::getInstance()->enemyDesc;
	HCSVFile* sectionData = &ResourceManager::getInstance()->sections[m_section-1];
	m_numRound = std::atoi(sectionData->getData(m_id, 1));	
	m_numPerRound = std::atoi(sectionData->getData(m_id, 2));;	
	m_timeBetweenRound = std::atof(sectionData->getData(m_id, 3));
	m_money = std::atoi(sectionData->getData(m_id, 4));
	m_bossRound = std::atoi(sectionData->getData(m_id, 5));

	m_deltaMonsterGenerateTime = std::atoi(enemyDesc->getData(0, 2));
	m_deltaMonsterGenerateRate = std::atof(enemyDesc->getData(0, 3));
	m_numMonster = std::atoi(enemyDesc->getData(0, 4));
	m_numLittleBoss = std::atoi(enemyDesc->getData(1, 4));
	m_numBigBoss = std::atoi(enemyDesc->getData(2, 4));
}

void Game::loadMap(){
	SceneReader* s = SceneReader::getInstance();
	char str[30];
	sprintf(str, "publish/section%d-%d.json", m_section, m_id+1);
	Node* node = s->createNodeWithSceneFile(str);
	if(node)	
		this -> addChild(node);
	//get TMXmap
	Node* map = node->getChildByTag(101);
	auto component = (ComRender*)(map->getComponent("CCTMXTiledMap"));
	m_map = (TMXTiledMap*)(component->getNode());
}

void Game::loadMenu(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto physicsItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuPhysicsCallback, this));
	physicsItem->setPosition(Vec2(origin.x + visibleSize.width - physicsItem->getContentSize().width/2 ,
		origin.y + visibleSize.height - physicsItem->getContentSize().height));

	auto menu = Menu::create(physicsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, ZORDER_MENU);

	m_modalNode = DrawNode::create();
	Vec2 vecs[4];
	vecs[0].x = 0; vecs[0].y = 0;
	vecs[1].x = SCREEN_WIDTH; vecs[1].y = 0;
	vecs[2].x = SCREEN_WIDTH; vecs[2].y = SCREEN_HEIGHT;
	vecs[3].x = 0; vecs[3].y = SCREEN_HEIGHT;
	m_modalNode->drawPolygon(vecs, 4, Color4F(0.2f, 0.2f, 0.2f, 0.5f), 0, Color4F(0.2f, 0.2f, 0.2f, 0.5f));
	this->addChild(m_modalNode, ZORDER_MODAL);

	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
	listener1->setSwallowTouches(true);//设置不想向下传递触摸  true是不想 默认为false  
	listener1->onTouchBegan = [](Touch* touch, Event* event){   
		return true;   
	};    
	listener1->onTouchMoved = [](Touch* touch, Event* event){      
	};    
	listener1->onTouchEnded = [](Touch* touch, Event* event){    
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_modalNode);

	TTFConfig config2;
	config2.fontSize = 60;
	config2.fontFilePath = FONT_PRICE;
	m_labelCountDown = Label::createWithTTF(config2, "");
	m_labelCountDown->setColor(Color3B(255, 0, 0));
	m_labelCountDown->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(m_labelCountDown, ZORDER_TEXT);
}

void Game::loadToolBar(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SceneReader* s = SceneReader::getInstance();
	Node* node = s->createNodeWithSceneFile("UI/GameMenu/GMenu.json");
	node->setPosition(Vec2(node->getPositionX(), origin.y + visibleSize.height - 80));
	this->addChild(node, ZORDER_MENU);
	Node* toolBar = node->getChildByTag(300);
	m_pauseBtn = toolBar->getChildByTag(301);
	m_replayBtn = toolBar->getChildByTag(302);
	m_backBtn = toolBar->getChildByTag(303);
	m_playBtn = toolBar->getChildByTag(304);
	m_playBtn->setVisible(false);

	auto component = (ComRender*)(m_pauseBtn->getComponent("pause"));
	Sprite* sprite = (Sprite*)(component->getNode());
	float width = sprite->getContentSize().width;
	float height = sprite->getContentSize().height;
	Rect rect = Rect(-width/2, -height/2, width, height);

	auto modalSprite = Sprite::create("images/modalLayer.png");
	modalSprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	modalSprite->setVisible(false);
	this->addChild(modalSprite, ZORDER_MODAL);

	auto pauseListener = EventListenerTouchOneByOne::create();
	pauseListener->setSwallowTouches(true);
	pauseListener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
		auto target = event->getCurrentTarget();
		Vec2 point = target->convertTouchToNodeSpace(touch);
		if (rect.containsPoint(point)){
			if(!Director::getInstance()->isPaused()){
				Director::getInstance()->pause();
				target->setVisible(false);
				m_playBtn->setVisible(true);
				modalSprite->setVisible(true);

				if(ResourceManager::getInstance()->isBackgroundMusicAllow()){
					CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				}

				auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
				listener1->setSwallowTouches(true);//设置不想向下传递触摸  true是不想 默认为false  
				listener1->onTouchBegan = [](Touch* touch, Event* event){   
					return true;   
				};    
				listener1->onTouchMoved = [](Touch* touch, Event* event){      
				};    
				listener1->onTouchEnded = [](Touch* touch, Event* event){    
				};
				this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, modalSprite);
				return true;
			}
		}
		return false;
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pauseListener, m_pauseBtn);

	auto playListener = EventListenerTouchOneByOne::create();
	playListener->setSwallowTouches(true);
	playListener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
		auto target = event->getCurrentTarget();
		Vec2 point = target->convertTouchToNodeSpace(touch);
		if (rect.containsPoint(point)){
			if (Director::getInstance()->isPaused()){
				Director::getInstance()->resume();
				target->setVisible(false);
				m_pauseBtn->setVisible(true);
				modalSprite->setVisible(false);
				this->_eventDispatcher->removeEventListenersForTarget(modalSprite);

				if(ResourceManager::getInstance()->isBackgroundMusicAllow()){
					CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				}
				return true;
			}		
		}
		return false;
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(playListener, m_playBtn);

	auto replayListener = EventListenerTouchOneByOne::create();
	replayListener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
		auto target = event->getCurrentTarget();
		Vec2 point = target->convertTouchToNodeSpace(touch);
		if (rect.containsPoint(point)){
			auto scene = Game::createScene(m_section, m_id);
			Director::getInstance()->replaceScene(scene);
			Director::getInstance()->resume();
			return true;
		}
		return false;
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(replayListener, m_replayBtn);

	auto backListener = EventListenerTouchOneByOne::create();
	backListener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
		auto target = event->getCurrentTarget();
		Vec2 point = target->convertTouchToNodeSpace(touch);
		if (rect.containsPoint(point)){

			if(ResourceManager::getInstance()->isBackgroundMusicAllow()){
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/MenuBackgroundMusic.mp3",true);
			}

			auto scene = IGameLevelSelector::createScene(m_section);
			Director::getInstance()->replaceScene(scene);
			Director::getInstance()->resume();
			return true;
		}
		return false;
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, m_backBtn);

	auto labelPrice = node->getChildByTag(305);
	m_labelPrice = LabelPrice::create(m_money);
	labelPrice->addChild(m_labelPrice);

	TTFConfig config;
	config.fontSize = FONTSIZE_PRICE;
	config.fontFilePath = FONT_PRICE;
	auto str = String::createWithFormat("Section%d-%d    %d/%d", m_section, m_id+1, 1, m_numRound);
	m_labelSection = Label::createWithTTF(config, str->getCString());
	auto labelsection = node->getChildByTag(306);
	labelsection->addChild(m_labelSection);
}

void Game::loadPeople(){
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
	this->reorderChild(m_baby, ZORDER_ENEMY);

	ValueMap enemyObject = peopleObjectGroup->getObject("enemy");	//获取一个name为“enemy”的对象
	m_enemyPosition = Vec2(objPosX(enemyObject),objPosY(enemyObject));	//enemy对象的起始位置
	float emeny_x = enemyObject.at("x").asFloat();
	float enemy_y = enemyObject.at("y").asFloat();
	float enemy_width = objWidth(enemyObject);
	float enemy_height = objHeight(enemyObject);
	m_enemyRect = Rect(emeny_x,enemy_y,enemy_width,enemy_height);

	ValueMap assistantObject = peopleObjectGroup->getObject("assistant");
	m_assistPosition = Vec2(objPosX(assistantObject), objPosY(assistantObject));
}

void Game::loadTower(){
	ResourceManager* rm = ResourceManager::getInstance();
	m_towerbase = SpriteBatchNode::create(PATH_TOWERBASE);	//用图片创建一个Batch
	m_towerbase->setPosition(Vec2::ZERO);	//设置这个Batch的位置
	this->addChild(m_towerbase, ZORDER_TOWER);	//将这个Batch加到场景里

	TMXObjectGroup* towerObjectGroup = m_map->getObjectGroup("tower");	//读取对象层“tower”
	ValueVector towerObjects = towerObjectGroup->getObjects();	//获得“tower”对象层里面的所有对象
	int towerId = 0;
	for (ValueVector::iterator it = towerObjects.begin(); it != towerObjects.end(); it++, towerId++){//对“tower”层里的每一个对象
		ValueMap towerObject = it->asValueMap();	//得到这个对象的属性
		int tower_x = objPosX(towerObject);
		int tower_y = objPosY(towerObject);
		Sprite* tower = Sprite::createWithTexture(m_towerbase->getTexture());	//用Batch创建一个精灵来表示可创建Tower的位置
		tower->setPosition(tower_x, tower_y);	//设置精灵的位置
		m_towerbase->addChild(tower);	//把精灵加到场景里
//		auto actionRepeateFadeOutIn = RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL));	//创建一个淡入淡出特效
//		tower->runAction(actionRepeateFadeOutIn);	//给精灵赋予特效

		auto menu = Menu::create();
		std::string type = towerObject.at("type").asString();	//可建的塔的类型
		std::vector<std::string> types;
		split(type, ",", &types);
		for (int j = 0; j < types.size(); j++)
		{
			int temp = std::atoi(types.at(j).c_str());
			std::string spriteFrameName = rm->towerData->getData(temp, 1);
			Sprite* towerItemSprite = Sprite::createWithSpriteFrameName(spriteFrameName);
			if (towerItemSprite){
				auto towerItem = MenuItemTower::create(std::atoi(rm->towerData->getData(temp, 8)), towerItemSprite, towerItemSprite,
					CC_CALLBACK_1(Game::towerCreateCallback, this, temp, tower, towerId));
				towerItem->setPosition(Vec2(j * towerItem->getContentSize().width,0));//
				menu->addChild(towerItem);
			}			
		}
		menu->setPosition(Vec2(tower->getPositionX(), tower->getPositionY() + tower->getContentSize().height));
		m_menus.pushBack(menu);

		Sprite* updateSprite = Sprite::create("images/tower/update.png");	//升级按钮
		Sprite* updateDisableSprite = Sprite::create("images/tower/UpdateDisable.png");
		auto upgradeItem = MenuItemTower::create(0, updateSprite, updateSprite, updateDisableSprite, CC_CALLBACK_1(Game::towerUpgradeCallback, this, towerId));
		upgradeItem->setPosition(0, upgradeItem->getContentSize().height);
		upgradeItem->setTag(TAG_UPGRADE_ITEM);

		auto deleteItem = MenuItemImage::create("images/tower/sell.png", "images/tower/sell.png", CC_CALLBACK_1(Game::towerDeleteCallback, this, towerId, tower));
		deleteItem->setPosition(0, -deleteItem->getContentSize().height);

		auto uMenu = Menu::create(upgradeItem, deleteItem, NULL);
		uMenu->setPosition(tower->getPosition());
		m_upgradeMenus.pushBack(uMenu);

		auto listener = EventListenerTouchOneByOne::create();	//触摸监听器
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [towerId, this](Touch* touch, Event* event){
			Sprite* target = static_cast<Sprite*>(event->getCurrentTarget());
			Rect rect = target->getTextureRect();
			Vec2 point = target->convertTouchToNodeSpace(touch);
			if (rect.containsPoint(point)){
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
//	towerId = 0;
}

void Game::loadRoadAndBarriers(){
	TMXObjectGroup* roadObjectGroup = m_map->getObjectGroup("road");	//读取对象层“road”
	ValueVector roadObjects = roadObjectGroup->getObjects();	//获得“road”对象层里面的所有对象
	for (ValueVector::iterator it = roadObjects.begin(); it != roadObjects.end(); it++)//对“road”层里的每一个对象
	{
		ValueMap roadObject = it->asValueMap();	//得到这个对象的属性
		float x = roadObject.at("x").asFloat();
		float y = roadObject.at("y").asFloat();
		float width = objWidth(roadObject);
		float height = objHeight(roadObject);
		std::string directionStr = roadObject.at("direction").asString();
		int direction;
		Vec2 destination;
		float duration;
		if ("left" == directionStr){
			direction = ROAD_LEFT;
			destination = Vec2(x + width - 40, y + height / 2);
			duration = width / 40;
		} else if ("up" == directionStr) {
			direction = ROAD_UP;
			destination = Vec2(x + width / 2, y + 40);
			duration = height / 40;
		} else if ("right" == directionStr) {
			direction = ROAD_RIGHT;
			destination = Vec2(x + 40, y + height / 2);
			duration = width / 40;
		} else {
			direction = ROAD_DOWN;
			destination = Vec2(x + width / 2, y + height - 40);
			duration = height / 40;
		}
		m_roads.push_back(Road(x, y, width, height, direction));	//把这个对象看作长方形储存到数组里
		m_actionsAssistant.pushBack(MoveTo::create(duration, destination));		
	}
	m_actionsAssistant.reverse();

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
}

void Game::loadEquipmentSlot()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto equipmentslot = GUIReader::getInstance()->widgetFromJsonFile("UI/equipmentSlot_1/equipmentSlot_1.ExportJson");
	this->addChild(equipmentslot,ZORDER_TOWER);

	auto rHpPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_RESTOREHP));
	auto sdPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_SLOWDOWN));
	auto sgPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_SAFEGUARD));
	auto lmPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_LANDMINE));
	auto trapPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_TRAP));
	auto atPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_ASSISTGUARD));
	
	PropsRestoreHp* restoreHpProp =  PropsRestoreHp::createWithBaby(m_baby,MODE_GROWUP);
	restoreHpProp->setPosition(rHpPos->getPosition());
	restoreHpProp->m_position = Rect(restoreHpProp->getPositionX() - 40, restoreHpProp->getPositionY() - 40, 80, 80);
	restoreHpProp->setTag(TYPE_PROP_RESTOREHP);
	this->addChild(restoreHpProp, ZORDER_PROPS);

 	PropsSlowdown* slowdownProp = PropsSlowdown::createWithTargets(m_enemies,MODE_GROWUP);
	slowdownProp->setPosition(sdPos->getPosition());
	slowdownProp->m_position = Rect(slowdownProp->getPositionX() - 40, slowdownProp->getPositionY() - 40, 80, 80);
	slowdownProp->setTag(TYPE_PROP_SLOWDOWN);
	this->addChild(slowdownProp, ZORDER_PROPS);
	

	PropsSafetyGuard* safetyGuardProp = PropsSafetyGuard::createWithBaby(m_baby,MODE_GROWUP);
	safetyGuardProp->setPosition(sgPos->getPosition());
	safetyGuardProp->m_position = Rect(safetyGuardProp->getPositionX() - 40, safetyGuardProp->getPositionY() - 40, 80, 80);
	safetyGuardProp->setTag(TYPE_PROP_SAFETYGUARD);
	safetyGuardProp->m_safeGRect = Rect(m_baby->getPositionX() - safetyGuardProp->getSafeGuradSize().width /2 ,
		m_baby->getPositionY() - safetyGuardProp->getSafeGuradSize().height / 2,
		safetyGuardProp->getSafeGuradSize().width  ,
		safetyGuardProp->getSafeGuradSize().height );
	this->addChild(safetyGuardProp, ZORDER_PROPS);
	
	PropsLandmine* landmineProp = PropsLandmine::createWithRoads(m_roads,MODE_GROWUP);
	landmineProp->setPosition(lmPos->getPosition());
	landmineProp->m_position = Rect(landmineProp->getPositionX() - 40, landmineProp->getPositionY() - 40, 80 ,80);
	landmineProp->setTag(TYPE_PROP_LANDMIND);
	this->addChild(landmineProp, ZORDER_PROPS);

	PropsTrap* trapProp = PropsTrap::createWithRoads(m_roads,MODE_GROWUP);
	trapProp->setPosition(trapPos->getPosition());
	trapProp->m_position = Rect(trapProp->getPositionX() - 40, trapProp->getPositionY() - 40, 80, 80);
	trapProp->setTag(TYPE_PROP_TRAP);
	this->addChild(trapProp, ZORDER_PROPS);

	PropsAssistGuard* assistGuardProp = PropsAssistGuard::create(m_assistPosition,MODE_GROWUP);
	assistGuardProp->setPosition(atPos->getPosition());
	assistGuardProp->m_position = Rect(assistGuardProp->getPositionX() - 40, assistGuardProp->getPositionY() - 40, 80, 80);
	assistGuardProp->setTag(TYPE_PROP_ASSISTGUARD);
	this->addChild(assistGuardProp, ZORDER_PROPS);

}


void Game::countDown(float dt){

	if (m_countdown <= 0){
		this->unschedule(schedule_selector(Game::countDown));
		this->_eventDispatcher->removeEventListenersForTarget(m_modalNode);
		m_modalNode->setVisible(false);
		m_towerbase->setVisible(false);
		m_isWaiting = false;
		m_curRound = 1;
		m_labelCountDown->removeFromParent();
		//生成大BOSS
		if (m_curRound == m_bossRound){
			int row = rand() % (m_numBigBoss) + m_numMonster + m_numLittleBoss;
			Enemy* enemy = Enemy::create(row, m_curRound, false);
			if (!enemy)
				return;
			enemy->setPosition(m_enemyPosition);
			this->addChild(enemy);
			m_enemies.pushBack(enemy);
		}

		if(ResourceManager::getInstance()->isBackgroundMusicAllow()){		
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/GameSceneMusic0.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/GameSceneMusic0.mp3",true);
		}
	}
	else
	{
		m_labelCountDown->setString(itos(m_countdown--));
	}
}


void Game::addEnemy(float dt){
	if (!m_isGameOver){ //如果游戏还没结束
		if (m_isWaiting){	//如果在倒计时状态
			if (m_curRound != 0){	//如果不是刚进入游戏（刚进入游戏需要倒数3秒）
				m_elapsedTimeRound += dt;
				if (m_elapsedTimeRound > m_timeBetweenRound){
					m_elapsedTimeRound = 0;
					if (m_curRound != m_numRound){
						m_curRound++;
						m_isWaiting = false;
						auto str = String::createWithFormat("Section%d-%d    %d/%d", m_section, m_id+1, m_curRound, m_numRound);
						m_labelSection->setString(str->getCString());
						//生成大BOSS
						if (m_curRound == m_bossRound){
							int row = rand() % (m_numBigBoss) + m_numMonster + m_numLittleBoss;
							Enemy* enemy = Enemy::create(row, m_curRound, false);
							if (!enemy)
								return;
							enemy->setPosition(m_enemyPosition);
							this->addChild(enemy);
							m_enemies.pushBack(enemy);
						}
					}
				}
			}
		}
		else { //如果不在倒计时状态(正在生成怪物）
			if (m_curNumInRound < m_numPerRound){
				m_elapsedTimeMonster += dt;
				if (m_elapsedTimeMonster > m_deltaMonsterGenerateTime){
					m_elapsedTimeMonster -= m_deltaMonsterGenerateTime;
					//generate monster
					Enemy* enemy = NULL;
					double rate = rand() / (double)RAND_MAX;
					if (rate < m_deltaMonsterGenerateRate)
					{
						int row = rand() % (m_numMonster);	
						enemy = Enemy::create(row, m_curRound, false);
					}else
					{
						int row = rand() % (m_numLittleBoss) + m_numMonster;
						enemy = Enemy::create(row, m_curRound, false);
					}
					if (!enemy)
						return;
					enemy->setPosition(m_enemyPosition);
					this->addChild(enemy);
					m_enemies.pushBack(enemy);
					m_curNumInRound++;
				}
			}
			else
			{
				if (m_curRound != m_numRound)
					m_curNumInRound = 0;
				m_isWaiting = true;
			}
		}
	}
}

void Game::moveAssistant(float dt){
	if (!m_isGameOver){
		for (int i = 0; i < m_assistants.size(); i++)//如果有assistant
		{
			Assistant* assist = m_assistants.at(i);
			if(assist->isDie()){  //如果它英勇牺牲了
				assist->removeFromParent();
				m_assistants.eraseObject(assist);
			}
			else{ //木有死就调整方向
				Vec2 assist_position = assist->getPosition();
				if(m_enemyRect.containsPoint(assist_position)){
					assist->setDie(true);
				}
			}
		}
	}
	else	//game over
	{
		for (int i = 0; i < m_assistants.size(); i++){		//对每个Assistant
			Assistant* as = m_assistants.at(i);
			as->removeFromParent();	//然后就把它消除掉
		}
		m_assistants.clear();
	}
}

void Game::moveEnemy(float dt){
	if (!m_isGameOver){
		for (int i = 0; i < m_enemies.size(); i++){		//对每个enemy
			Enemy* enemy = m_enemies.at(i);
			if (enemy->isDie()){	//如果它死了
				this->addMoney(enemy->getPrice());	//那么它会掉金钱
				m_enemies.eraseObject(enemy);	//容器里要释放哦
				enemy->killed();	//然后就把它消除掉
			}else{	//如果它没死
				Vec2 enemy_position = enemy->getPosition();	//看看它的位置
				PropsSafetyGuard* safeguard = (PropsSafetyGuard*)this->getChildByTag(TYPE_PROP_SAFETYGUARD);
				if(safeguard->isGuarding() && safeguard->m_safeGRect.containsPoint(enemy_position)){  
					//检测是否有保护罩，有保护罩就保护宝贝
					m_isGameOver = m_baby->setDamage(safeguard->setCurState(enemy->getDamage()));
					enemy->removeFromParent();	//把enemy消除掉
					m_enemies.eraseObject(enemy);	//容器里也要释放哦
				}
				// 木有保护罩
				else if (m_baby->m_position.containsPoint(enemy_position)){	//如果碰到Baby了
					m_isGameOver = m_baby->setDamage(enemy->getDamage());	//扣Baby的血看她死不死
					enemy->removeFromParent();	//把enemy消除掉
					m_enemies.eraseObject(enemy);	//容器里也要释放哦
					m_baby->hurt();	//Baby痛了一下
					if (m_isGameOver)
					{
						gameOver(false);
					}
				} 
				else
				{	//根据所在的road调整速度（方向）
					Road* road = enemy->getRoad();
					if (road && road->containsPoint(enemy_position)){	//如果还在原本的道路上
							enemy->setVelocity(road->getDirectionVec2() * enemy->getSpeed());
					}
					else //如果走到了其他路上
					{
						for (int k = 0; k < m_roads.size(); k++){
							Road* it = &m_roads.at(k);
							if (it->containsPoint(enemy_position)){
								enemy->setDirection(it->getDirection());
								enemy->setVelocity(it->getDirectionVec2() * enemy->getSpeed());
								enemy->setRoad(it);
								break;
							}
						}
					}			
				}
			}
		}
		if (m_enemies.empty() && m_curRound == m_numRound && m_curNumInRound == m_numPerRound){
			//win
			m_isGameOver = true;
			gameOver(true);
		}
	}
	else	//game over
	{
		for (int i = 0; i < m_enemies.size(); i++){		//对每个enemy
			Enemy* enemy = m_enemies.at(i);
			enemy->removeFromParent();	//然后就把它消除掉
		}
		m_enemies.clear();
	}
}

void Game::findEnemy(float dt){
	if (!m_isGameOver){
		for (int i = 0; i < m_towers.size(); i++){
			Tower* tower = m_towers.at(i);
			tower->generateBullet(dt);
		}
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

void Game::gameOver(bool isWin){
	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
	listener1->setSwallowTouches(true);//设置不想向下传递触摸  true是不想 默认为false  
	listener1->onTouchBegan = [](Touch* touch, Event* event){   
		return true;   
	};    
	listener1->onTouchMoved = [](Touch* touch, Event* event){      
	};    
	listener1->onTouchEnded = [](Touch* touch, Event* event){    
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_modalNode);
	m_modalNode->setVisible(true); //黑色那层

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	Sprite* sprite = NULL;
	if (isWin){
		sprite = Sprite::create("youWin.png");
	}
	else
	{
		sprite = Sprite::create("youFail.png");
	}
	if (sprite){
		auto action = EaseBounceOut::create(MoveTo::create(0.3f, Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2)));
		sprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height));
		this->addChild(sprite, ZORDER_TEXT);
		sprite->runAction(action);
	}

	if (isWin){
		auto toolbar = this->getChildByTag(10004)->getChildByTag(300);
		this->_eventDispatcher->removeEventListenersForTarget(m_pauseBtn);
		this->_eventDispatcher->removeEventListenersForTarget(m_playBtn);
		auto next = Sprite::create("UI/GameMune.psd_Psd.Dir/next.png");
		next->setPosition(toolbar->getChildByTag(301)->getPosition());
		toolbar->addChild(next, 2);
		auto listener2 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
		listener2->setSwallowTouches(true);//设置不想向下传递触摸  true是不想 默认为false  
		listener2->onTouchBegan = [next, this](Touch* touch, Event* event){
			Rect rect = next->getTextureRect();
			auto target = event->getCurrentTarget();
			Vec2 point = target->convertTouchToNodeSpace(touch);
			if (rect.containsPoint(point)){
				//跳到下一关
				int rows = ResourceManager::getInstance()->sections[m_section-1].getRows();
				m_id++;
				if (m_id >= rows)//这个section清完了
				{
					m_section++;
					if (m_section >= NUM_SECTIONS) //整个游戏通关了
					{
						if(ResourceManager::getInstance()->isBackgroundMusicAllow()){
							CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
							CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/MenuBackgroundMusic.mp3",true);
						}

						auto scene = ISectionSelector::createScene();
						Director::getInstance()->replaceScene(scene);
					}
					else	//下一个section的第一关(if any)
					{
						if (ResourceManager::getInstance()->sections[m_section-1].getRows() > 0){
							auto scene = Game::createScene(m_section, 0);
							Director::getInstance()->replaceScene(scene);
						}
						else
						{
							if(ResourceManager::getInstance()->isBackgroundMusicAllow()){
								CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
								CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/MenuBackgroundMusic.mp3",true);
							}

							auto scene = ISectionSelector::createScene();
							Director::getInstance()->replaceScene(scene);
						}
					}
				}
				else //跳到这个section的下一关
				{
					auto scene = Game::createScene(m_section, m_id);
					Director::getInstance()->replaceScene(scene);
				}

				return true;
			}
			return false;   
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, next);
	}	
}

void Game::victoryGame()
{
	//Sprite* mysprie = Sprite::createWithSpriteFrame();
}

void Game::failGame()
{

}

void Game::meetTraps(float dt)
{
	PropsLandmine* landmines = (PropsLandmine*)this->getChildByTag(TYPE_PROP_LANDMIND);
	if(landmines->getNumofLandmines() > 0){
		for (int i = 0; i < landmines->getNumofLandmines(); i++) //对于每个地雷
		{
			LandMine* landmine = landmines->getLandmines().at(i);
			if(landmine->isBomb()){
				landmine->removeFromParent();
				landmines->getLandmines().eraseObject(landmine);
				continue;
			}
			bool step = false;
			for(int j = 0; j < m_enemies.size(); j++) //检测每只怪兽是否踩到它
			{
				Enemy* enemy = m_enemies.at(j);
				if(landmine->m_position.containsPoint(enemy->getPosition())){ 
					step = true; //踩到了就炸了它
					enemy->setHp(enemy->getHp() - landmines->getDamage());
				}
			}
			if(step){ //被踩了自己也要被炸
				landmine->bomb();
			}
		}
	}

	PropsTrap* traps = (PropsTrap*)this->getChildByTag(TYPE_PROP_TRAP);
	if(traps->getNumofTraps() > 0){
		for(int i =0; i < traps->getNumofTraps(); i++)
		{
			Trap* trap = traps->getTraps().at(i);
			if(!trap->isContainable()){
				for(int j = 0; j < trap->getTargets().size(); j++){
					Enemy* enemy = trap->getTargets().at(j);
					enemy->setHp(enemy->getHp() - traps->getDamage());
					if(enemy->getHp() > 0){
						enemy->setSpeed(enemy->getOriginSpeed());
					}
					trap->getTargets().eraseObject(enemy);
				}
				trap->destory();
				trap->removeFromParent();
				traps->getTraps().eraseObject(trap);
				continue;
			}
			for (int j = 0; j < m_enemies.size(); j++)
			{
				Enemy* enemy = m_enemies.at(j);
				if(trap->m_position.containsPoint(enemy->getPosition())){
					trap->catchEnemy(enemy);
				}
			}
			//if(!trap->isContainable())
		}
	}
}

void Game::onEnter(){
	Layer::onEnter();
	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = [this](PhysicsContact &contact)->bool{
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
			damage -= enemy->getPhysicalDefence();
			if (damage > 0)
				enemy->setHp(enemy->getHp() - damage);
			bullet->setDie();
			return true;
		}
		if(m_assistants.size() > 0){
			Assistant* assistant = NULL;
			if(TAG_ASSISTANT == tagA && TAG_ENEMY == tagB){
				assistant =dynamic_cast<Assistant*>(nodeA);
				enemy = dynamic_cast<Enemy*>(nodeB);
			}
			else if(TAG_ENEMY == tagA &&TAG_ASSISTANT == tagB){
				enemy = dynamic_cast<Enemy*>(nodeA);
				assistant = dynamic_cast<Assistant*>(nodeB);
			}
			if(enemy && assistant){
				int damage = assistant->getPhysicalDefence() - enemy->getPhysicalDefence();
				damage = damage < 0 ? -damage : damage;
				float rate = enemy->getPhysicalDefence() / (assistant->getPhysicalDefence() + enemy->getPhysicalDefence());
				enemy->setHp(enemy->getHp() - damage * ( 1 - rate ));
				assistant->setHp(assistant->getHp() - damage * rate );
				return true;
			}
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(m_contactListener, Priority_EventListenerPhysicsContact);
}

void Game::onExit(){
	Layer::onExit();
	_eventDispatcher->removeEventListener(m_contactListener);
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
	MenuItemTower* menuItemTower = static_cast<MenuItemTower*>(pSender);	//转化为MenuItmeTower类型
	Node* menu = menuItemTower->getParent();	//得到菜单
	menu->removeFromParentAndCleanup(false);	//隐藏菜单
	this->addMoney(-menuItemTower->getPrice());	//扣钱建塔

	Tower* tower = Tower::create(type);	//创建一个对应类型的塔
	if(!tower)
		return;
	tower->setTag(menuId);
	Vec2 towerPosition = towerbase->getPosition();	//得到塔的位置
	tower->setPosition(towerPosition);	//设置塔的位置
	this->addChild(tower);	//将塔加入场景
	this->reorderChild(tower, ZORDER_TOWER);	//调整塔的优先级
	this->m_towers.pushBack(tower);	//将塔加入容器
	//	towerbase->removeFromParentAndCleanup(true);	//清除塔基
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
					int price = tower->getUpgradePrice();
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
			}
		}
		else
		{
			tower->showRange(false);
			auto upgradeMenu = m_upgradeMenus.at(menuId);
			this->removeChild(upgradeMenu, false);
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
	MenuItemTower* menuItemTower = static_cast<MenuItemTower*>(pSender);
	this->addMoney(-menuItemTower->getPrice());
}

void Game::towerDeleteCallback(cocos2d::Ref* pSender, int towerId, Sprite* towerbase)
{
	auto menu = m_upgradeMenus.at(towerId);
	menu->removeFromParentAndCleanup(false);
	this->addChild(towerbase);
	towerbase->release();
	Tower* tower = static_cast<Tower*>(this->getChildByTag(towerId));
	this->addMoney(tower->getMoneyWhenDeleted());
	this->removeChild(tower);
	this->m_towers.eraseObject(tower);
}


void Game::onTouchWinPage(Object* pSender, TouchEventType type)
{

}

void Game::onTouchFailPage(Object* pSender, TouchEventType type)
{

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

Vector<FiniteTimeAction*>& Game::getActionsAssistant(){
	return m_actionsAssistant;
}

Vector<Assistant*>& Game::getAssistants(){
	return m_assistants;
}