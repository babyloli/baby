#include "EndlessGameScene.h"
#include "HCSVFile.h"
#include "IHomeMenuScene.h"
#include "ResourceManager.h"

const int UI_BUTTON_ENDLESS_RETURN = 73;
const int UI_BUTTON_ENDLESS_REPLAY = 74;

Endless::Endless()
	:Game(1, 0)
{
	m_elapsedTimeMouse = 0;
}

Scene* Endless::createScene(){
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	auto layer = Endless::create();
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

Endless* Endless::create(){
	Endless *pRet = new Endless(); 
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

bool Endless::init(){
	if (!Game::init())
		return false;
	loadMousePosition();

	this->schedule(schedule_selector(Endless::showMouse));
	return true;
}

void Endless::loadData(){
	HCSVFile* enemyDesc = ResourceManager::getInstance()->enemyDesc;
	m_numRound = -1;
	m_numPerRound = 15;	
	m_timeBetweenRound = 10;
	m_money = 0;
	m_bossRound = -1;

	m_deltaMonsterGenerateTime = std::atoi(enemyDesc->getData(0, 2));
	m_deltaMonsterGenerateRate = std::atof(enemyDesc->getData(0, 3));
	m_numMonster = std::atoi(enemyDesc->getData(0, 4));
	m_numLittleBoss = std::atoi(enemyDesc->getData(1, 4));
	m_numBigBoss = std::atoi(enemyDesc->getData(2, 4));
}

void Endless::loadMap(){
	cocostudio::SceneReader* s = cocostudio::SceneReader::getInstance();
	m_map = TMXTiledMap::create("Map/Endless/Endless.tmx");
	this->addChild(m_map);
}

void Endless::loadToolBar(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocostudio::SceneReader* s = cocostudio::SceneReader::getInstance();
	Node* node = s->createNodeWithSceneFile("UI/GameMenu/GMenu.json");
	node->setPosition(Vec2(node->getPositionX(), origin.y + visibleSize.height - 80));
	this->addChild(node, ZORDER_MENU);
	Node* toolBar = node->getChildByTag(300);
	m_pauseBtn = toolBar->getChildByTag(301);
	m_replayBtn = toolBar->getChildByTag(302);
	m_backBtn = toolBar->getChildByTag(303);
	m_playBtn = toolBar->getChildByTag(304);
	m_playBtn->setVisible(false);

	auto component = (cocostudio::ComRender*)(m_pauseBtn->getComponent("pause"));
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
			auto scene = Endless::createScene();
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

			auto scene = IHomeMenu::createScene();
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
	auto str = String::createWithFormat("Section%d-%d    %d/MAX", m_section, m_id+1, 1);
	m_labelSection = Label::createWithTTF(config, str->getCString());
	auto labelsection = node->getChildByTag(306);
	labelsection->addChild(m_labelSection);
}

void Endless::loadMousePosition(){
	TMXObjectGroup* roadObjectGroup = m_map->getObjectGroup("shrewmouse");	//读取对象层“地鼠”
	ValueVector roadObjects = roadObjectGroup->getObjects();	//获得“地鼠”对象层里面的所有对象
	for (ValueVector::iterator it = roadObjects.begin(); it != roadObjects.end(); it++)//对“地鼠”层里的每一个对象
	{
		ValueMap mouseObject = it->asValueMap();	//得到这个对象的属性
		auto mouse = Mouse::create();
		mouse->setPosition(Vec2(objPosX(mouseObject), objPosY(mouseObject)));
		this->addChild(mouse, ZORDER_TOWER);
		m_mouses.pushBack(mouse);
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(Endless::mouseTouchCallback, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mouse);
	}
}

void Endless::loadEquipmentSlot()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto equipmentslot = GUIReader::getInstance()->widgetFromJsonFile("UI/equipmentSlot_3/equipmentSlot_3.ExportJson");
	this->addChild(equipmentslot,ZORDER_TOWER);


	auto rHpPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_RESTOREHP));
	auto sdPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_SLOWDOWN));
	auto sgPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_SAFEGUARD));
	auto lmPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_LANDMINE));
	auto trapPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_TRAP));
	auto atPos = static_cast<Button*>(Helper::seekWidgetByTag(equipmentslot,UI_POSITION_ASSISTGUARD));

	PropsRestoreHp* restoreHpProp =  PropsRestoreHp::createWithBaby(m_baby,MODE_ENDLESS);
	restoreHpProp->setPosition(rHpPos->getPosition());
	restoreHpProp->m_position = Rect(restoreHpProp->getPositionX() - 40, restoreHpProp->getPositionY() - 40, 80, 80);
	restoreHpProp->setTag(TYPE_PROP_RESTOREHP);
	this->addChild(restoreHpProp,ZORDER_TOWER + 1);

	PropsSlowdown* slowdownProp = PropsSlowdown::createWithTargets(m_enemies,MODE_ENDLESS);
	slowdownProp->setPosition(sdPos->getPosition());
	slowdownProp->m_position = Rect(slowdownProp->getPositionX() - 40, slowdownProp->getPositionY() - 40, 80, 80);
	slowdownProp->setTag(TYPE_PROP_SLOWDOWN);
	this->addChild(slowdownProp, ZORDER_TOWER + 1);


	PropsSafetyGuard* safetyGuardProp = PropsSafetyGuard::createWithBaby(m_baby,MODE_ENDLESS);
	safetyGuardProp->setPosition(sgPos->getPosition());
	safetyGuardProp->m_position = Rect(safetyGuardProp->getPositionX() - 40, safetyGuardProp->getPositionY() - 40, 80, 80);
	safetyGuardProp->setTag(TYPE_PROP_SAFETYGUARD);
	safetyGuardProp->m_safeGRect = Rect(m_baby->getPositionX() - safetyGuardProp->getSafeGuradSize().width /2 ,
		m_baby->getPositionY() - safetyGuardProp->getSafeGuradSize().height / 2,
		safetyGuardProp->getSafeGuradSize().width  ,
		safetyGuardProp->getSafeGuradSize().height );
	this->addChild(safetyGuardProp,ZORDER_TOWER + 1);

	PropsLandmine* landmineProp = PropsLandmine::createWithRoads(m_roads,MODE_ENDLESS);
	landmineProp->setPosition(lmPos->getPosition());
	landmineProp->m_position = Rect(landmineProp->getPositionX() - 40, landmineProp->getPositionY() - 40, 80 ,80);
	landmineProp->setTag(TYPE_PROP_LANDMIND);
	this->addChild(landmineProp, ZORDER_TOWER + 1);

	PropsTrap* trapProp = PropsTrap::createWithRoads(m_roads,MODE_ENDLESS);
	trapProp->setPosition(trapPos->getPosition());
	trapProp->m_position = Rect(trapProp->getPositionX() - 40, trapProp->getPositionY() - 40, 80, 80);
	trapProp->setTag(TYPE_PROP_TRAP);
	this->addChild(trapProp,ZORDER_TOWER + 1);

	PropsAssistGuard* assistGuardProp = PropsAssistGuard::create(m_assistPosition,MODE_ENDLESS);
	assistGuardProp->setPosition(atPos->getPosition());
	assistGuardProp->m_position = Rect(assistGuardProp->getPositionX() - 40, assistGuardProp->getPositionY() - 40, 80, 80);
	assistGuardProp->setTag(TYPE_PROP_ASSISTGUARD);
	this->addChild(assistGuardProp, ZORDER_TOWER + 1);
	
}

void Endless::addEnemy(float dt)
{
	if (!m_isGameOver){ //如果游戏还没结束
		if (m_isWaiting){	//如果在倒计时状态
			if (m_curRound != 0){	//如果不是刚进入游戏（刚进入游戏需要倒数3秒）
				m_elapsedTimeRound += dt;
				if (m_elapsedTimeRound > m_timeBetweenRound){
					m_elapsedTimeRound = 0;
					m_curRound++;
					if (m_curRound >= 0xffffffff)
						m_curRound = 1;
					m_isWaiting = false;
					auto str = String::createWithFormat("Section%d-%d    %d/MAX", m_section, m_id+1, m_curRound);
					m_labelSection->setString(str->getCString());
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
						enemy = Enemy::create(row, m_curRound, true);
					} else if (rate < m_deltaMonsterGenerateRate + 0.02f)
					{
						int row = rand() % (m_numBigBoss) + m_numMonster + m_numLittleBoss;
						enemy = Enemy::create(row, m_curRound, true);
					}					
					else
					{
						int row = rand() % (m_numLittleBoss) + m_numMonster;
						enemy = Enemy::create(row, m_curRound, true);
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
				m_curNumInRound = 0;
				m_isWaiting = true;
			}
		}
	}
}

void Endless::showMouse(float dt){
	if (!m_isGameOver){
//		if (!m_isWaiting){
			m_elapsedTimeMouse += dt;
			if (m_elapsedTimeMouse > INTERVAL_MOUSE)
			{
				m_elapsedTimeMouse -= INTERVAL_MOUSE;
				int idx = rand() % m_mouses.size();
				auto mouse = m_mouses.at(idx);	//生成地鼠的位置
				mouse->goUp();
			}
//		}
	}
}

bool Endless::mouseTouchCallback(Touch* touch, Event* event){
	Mouse* mouse = static_cast<Mouse*>(event->getCurrentTarget());
	Vec2 pos = mouse->convertTouchToNodeSpace(touch);
	Rect rect = Rect(-TILESIZE/2, -TILESIZE/2, TILESIZE, TILESIZE);
	if (rect.containsPoint(pos) && mouse->isUp())
	{
		mouse->killed();
		//TODO 得到道具
		int tag = rand() % 6;
		auto prop = (Props*)this->getChildByTag(TYPE_PROPS + tag + 1);
		prop->AndEndlessNumber();
		return true;
	}
	return false;
}

void Endless::winGame()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto failUI = GUIReader::getInstance()->widgetFromJsonFile("UI/gomeOver_Endless_1/gomeOver_Endless_1.ExportJson");
	this->addChild(failUI,ZORDER_MENU);
	auto action = EaseBounceOut::create(MoveTo::create(0.3, origin));
	failUI->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	failUI->runAction(action);

	auto failSprite = Sprite::create();
	auto failAction = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMAITON_WIN)));
	failSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /2 + 45);
	failSprite->runAction(failAction);
	this->addChild(failSprite,ZORDER_TEXT);

	auto label = LabelBMFont::create(itos(m_curRound - 1), FONT_GOLD);
	label->setPosition(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 - 90);
	this->addChild(label,ZORDER_TEXT);

	auto returnButton = static_cast<Button*>(Helper::seekWidgetByTag(failUI,UI_BUTTON_ENDLESS_RETURN));
	auto replayButton = static_cast<Button*>(Helper::seekWidgetByTag(failUI,UI_BUTTON_ENDLESS_REPLAY));
	returnButton->addTouchEventListener(this, toucheventselector(Endless::onTouchPage));
	replayButton->addTouchEventListener(this, toucheventselector(Endless::onTouchPage));
}

void Endless::failGame()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto failUI = GUIReader::getInstance()->widgetFromJsonFile("UI/gomeOver_Endless_1/gomeOver_Endless_1.ExportJson");
	this->addChild(failUI,ZORDER_MENU);
	auto action = EaseBounceOut::create(MoveTo::create(0.3, origin));
	failUI->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	failUI->runAction(action);

	auto failSprite = Sprite::create();
	auto failAction = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(ANIMATION_FAIL)));
	failSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /2 + 45);
	failSprite->runAction(failAction);
	this->addChild(failSprite,ZORDER_TEXT);

	auto label = LabelBMFont::create(itos(m_curRound - 1), FONT_GOLD);
	label->setPosition(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 - 90);
	this->addChild(label,ZORDER_TEXT);

	auto returnButton = static_cast<Button*>(Helper::seekWidgetByTag(failUI,UI_BUTTON_ENDLESS_RETURN));
	auto replayButton = static_cast<Button*>(Helper::seekWidgetByTag(failUI,UI_BUTTON_ENDLESS_REPLAY));
	returnButton->addTouchEventListener(this, toucheventselector(Endless::onTouchPage));
	replayButton->addTouchEventListener(this, toucheventselector(Endless::onTouchPage));
}

void Endless::onTouchPage(Object* pSender, TouchEventType type)
{
	int tag = (static_cast<Button*>(pSender))->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		switch (tag)
		{
		case UI_BUTTON_ENDLESS_RETURN:
			{
				auto scene = IHomeMenu::createScene();
				Director::getInstance()->replaceScene(scene);
				Director::getInstance()->resume();
				break;
			}
		case UI_BUTTON_ENDLESS_REPLAY:
			{
				auto scene = Endless::createScene();
				Director::getInstance()->replaceScene(scene);
				Director::getInstance()->resume();
				break;
			}
		default:
			break;
		}
	default:
		break;
	}
}