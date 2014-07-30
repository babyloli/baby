#include "EndlessGameScene.h"
#include "HCSVFile.h"
#include "IHomeMenuScene.h"
#include "ResourceManager.h"

Endless::Endless()
	:Game(1, 0){}

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
					}else
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