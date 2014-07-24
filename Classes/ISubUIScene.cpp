#include "ISubUIScene.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "ResourceManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int UI_BUTTON_GROWUP_MODE = 5;
const int UI_BUTTON_DOCTOR_MODE = 6;
const int UI_BUTTON_CLOSESELECTOR = 10;
const int UI_CHECKBOX_BACKGROUND_MUSIC = 11;
const int UI_CHECKBOX_SOUND_EFFECT = 12;
const int UI_BUTTON_CLOSESETTER = 18;
const int UI_BUTTON_CLOSESHOP=29;
const int UI_BUTTON_BUY_ITEM1=32;
const int UI_BUTTON_BUY_ITEM2=36;
const int UI_BUTTON_BUY_ITEM3=44;
const int UI_BUTTON_BUY_ITEM4=48;
const int UI_BUTTON_BUY_ITEM5=50;
const int UI_SECTIONSELECT = 60;
const int UI_BUTTON_SELECT_BABY = 61;
const int UI_BUTTON_SELECT_KID = 62;
const int UI_BUTTON_SELECT_CHILD = 63;
const int UI_BUTTON_SELECT_YOUTH =64;

//////////////////////////////////////////////////////////////////////////////
Scene* IModeSelector::createScene()
{
	auto scene = Scene::create();
	auto layer = IModeSelector::create();
	scene->addChild(layer);
	return scene;
}

bool IModeSelector::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto selectModeUI = GUIReader::getInstance()->widgetFromJsonFile("UI/selectMode_1/selectMode_1.ExportJson");
	this->addChild(selectModeUI);

	auto growupModeButton = static_cast<Button*>(Helper::seekWidgetByTag(selectModeUI,UI_BUTTON_GROWUP_MODE));
	auto doctorModeButton = static_cast<Button*>(Helper::seekWidgetByTag(selectModeUI,UI_BUTTON_DOCTOR_MODE));
	auto closeItem = static_cast<Button*>(Helper::seekWidgetByTag(selectModeUI,UI_BUTTON_CLOSESELECTOR));

	growupModeButton->addTouchEventListener(this,toucheventselector(IModeSelector::onTouchSelectButton));
	doctorModeButton->addTouchEventListener(this,toucheventselector(IModeSelector::onTouchSelectButton));
	closeItem->addTouchEventListener(this,toucheventselector(IModeSelector::onTouchSelectButton));

	return true;
}

void IModeSelector::onTouchSelectButton(Object* pSender, TouchEventType type)
{
	int tag = (static_cast<Button*>(pSender))->getTag();

	switch (type)
	{
	case  TOUCH_EVENT_ENDED:
		switch (tag)
		{
		case UI_BUTTON_GROWUP_MODE:
			{
				auto sectionLevelSelector = ISectionSelector::createScene();
				Director::getInstance()->replaceScene(sectionLevelSelector);
			}						
			break;
		case UI_BUTTON_DOCTOR_MODE:
			break;
		case UI_BUTTON_CLOSESELECTOR:
			this->removeFromParentAndCleanup(true);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene* IBGMusicSetter::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = IBGMusicSetter::create();
	scene->addChild(layer);
	return scene;
}

bool IBGMusicSetter::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto setterUI = GUIReader::getInstance()->widgetFromJsonFile("UI/setup_1/setup_1.ExportJson");
	this->addChild(setterUI);
	
	auto musicCheckBox = static_cast<CheckBox*>(Helper::seekWidgetByTag(setterUI,UI_CHECKBOX_BACKGROUND_MUSIC));
	auto effectCheckBox = static_cast<CheckBox*>(Helper::seekWidgetByTag(setterUI,UI_CHECKBOX_SOUND_EFFECT));
	auto closeItem = static_cast<Button*>(Helper::seekWidgetByTag(setterUI,UI_BUTTON_CLOSESETTER));

	musicCheckBox->addEventListenerCheckBox(this,checkboxselectedeventselector(IBGMusicSetter::onSelectedBGMusic));
	effectCheckBox->addEventListenerCheckBox(this,checkboxselectedeventselector(IBGMusicSetter::onSelectedSoundEffects));
	closeItem->addTouchEventListener(this,toucheventselector(IBGMusicSetter::onTouchCloseItem));
	
	musicCheckBox->setSelectedState(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying());
	//if(SimpleAudioEngine::getInstance()->
	//effectCheckBox->setSelectedState(true);
	
	return true;
}

void IBGMusicSetter::onSelectedBGMusic(Object* pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_UNSELECTED:
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				break;
	case CHECKBOX_STATE_EVENT_SELECTED:
				CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
				//SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
				break;
	default:
			break;
	}
}

void IBGMusicSetter::onSelectedSoundEffects(Object* pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_UNSELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
			break;
	case  CHECKBOX_STATE_EVENT_SELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
			break;
	default:
			break;
	}
}

void IBGMusicSetter::onTouchCloseItem(Object* pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		this->removeFromParentAndCleanup(true);
		break;
	default:
		break;
	}
}




//////////////////////////////////////////////////////////////////////////
Scene* ISectionSelector::createScene()
{
	auto scene = Scene::create();
	auto layer = ISectionSelector::create();
	scene->addChild(layer);
	return scene;
}

bool ISectionSelector::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	
	auto sectionSelector = GUIReader::getInstance()->widgetFromJsonFile("UI/sectionSelect_1/sectionSelect_1.ExportJson");
	if (!sectionSelector)
	{
		CCLOG("NULL");
	}
	this->addChild(sectionSelector);

	auto babyButton = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_BABY));
	auto kidButtion = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_KID));
	auto childButton = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_CHILD));
	auto youthButton = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_YOUTH));
	babyButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	kidButtion->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	childButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	youthButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));

	auto returnItem = MenuItemImage::create("back.png","back.png",CC_CALLBACK_1(ISectionSelector::onTouchReternItem,this));
	returnItem->setPosition(Vec2(origin.x + visibleSize.width - returnItem->getContentSize().width / 2, origin.y + returnItem->getContentSize().height /2));
	auto menu = Menu::create(returnItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, ZORDER_MENU);
	
	return true;
}

void ISectionSelector::onTouchSelected(Object* pSender, TouchEventType type)
{
	int tag = static_cast<Button*>(pSender)->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		if (tag <= 64 && tag > 60)
		{
			auto gs = IGameLevelSelector::createScene(tag - UI_SECTIONSELECT);
			Director::getInstance()->replaceScene(gs);
		}
		break;
	default:
		break;
	}
}

void ISectionSelector::onTouchReternItem(Ref* pSender)
{
	auto homescene = IHomeMenu::createScene();
	Director::getInstance()->replaceScene(homescene);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene* IGameLevelSelector::createScene(int section)
{
	auto scene = Scene::create();
	auto layer = IGameLevelSelector::create(section);
	scene->addChild(layer);
	return scene;
}

IGameLevelSelector* IGameLevelSelector::create(int section){
	IGameLevelSelector *pRet = new IGameLevelSelector(); 
	if (pRet && pRet->init(section)) 
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

bool IGameLevelSelector::init(int section)
{
	if (!Layer::init())
	{
		return false;
	}
	m_section = section;
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bgimg = Sprite::create("UI/bg.png");
	bgimg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(bgimg, 0);

	auto returnItem = MenuItemImage::create("back.png","back.png",CC_CALLBACK_1(IGameLevelSelector::menuReturnCallback,this));
	returnItem->setPosition(Vec2(origin.x + visibleSize.width - returnItem->getContentSize().width / 2, origin.y + returnItem->getContentSize().height /2));
	auto menu = Menu::create(returnItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, ZORDER_MENU);	

	TableView* tableView = TableView::create(this,visibleSize);      // 创建一个tableView
	tableView->setDirection(TableView::Direction::HORIZONTAL);   // 设置方向
	tableView->setPosition(Vec2::ZERO);      //设置位置
	tableView->setDelegate(this);  //该步骤非常关键，把tableView和当前类绑定在一起，故后面后面调用的主体是tableView
	this->addChild(tableView,0);
	tableView->reloadData();  

	return true;
}

void IGameLevelSelector::menuReturnCallback(Ref* pSender)
{
	auto back = ISectionSelector::createScene();
	Director::getInstance()->replaceScene(back);
}

void IGameLevelSelector::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
}

void IGameLevelSelector::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
}

void IGameLevelSelector::tableCellTouched(cocos2d::extension::TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
	int i = cell->getIdx();
	if (i == 0)
	{
		auto gamescene1 = Game::createScene(m_section, i);
		Director::getInstance()->replaceScene(gamescene1);
	}
}

Size IGameLevelSelector::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	//return Size(500,400);
	return Size(600,720);
}

//设置数据源tableCellAtIndex
TableViewCell* IGameLevelSelector::tableCellAtIndex(TableView* table, ssize_t idx)
{
	String* string = String::createWithFormat("%d", idx);
	TableViewCell* cell = table->dequeueCell();

	if (!cell)
	{
		//创建单元，如果自定义单元效果，需要继承tableViewCell, 并且重载draw
		cell = new TableViewCell();
		cell->autorelease();
		Sprite* sprite = Sprite::create("HelloWorld.png");
		auto cellSize = tableCellSizeForIndex(table, idx);
		sprite->setPosition(Vec2(cellSize.width/2,cellSize.height/2));
		cell->addChild(sprite);

		auto label = LabelTTF::create(string->getCString(),"Helvetica",20.0);
		label->setPosition(Vec2(cellSize.width/2 -10,200));
		label->setTag(456);
		cell->addChild(label);
	}
	else
	{
		auto label = (LabelTTF*)cell->getChildByTag(456);
		label->setString(string->getCString());
	}

	return cell;
}

ssize_t IGameLevelSelector::numberOfCellsInTableView(TableView* table)
{
	//Manager控制个数
	int ret = ResourceManager::getInstance()->sections[m_section-1].getRows();
	return ret;
}




/////////////////////////////////////////////////////////////////////////////////////
Scene* IShop::createScene()
{
	auto scene = Scene::create();
	auto layer = IShop::create();
	scene->addChild(layer);
	return scene;
}

bool IShop::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto ShopUI = GUIReader::getInstance()->widgetFromJsonFile("store_1/store_1.ExportJson");
	this->addChild(ShopUI);
	
	
	auto QuitButton= static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_CLOSESHOP));
	auto BuyItemButton1=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_ITEM1));
	auto BuyItemButton2=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_ITEM2));
	auto BuyItemButton3=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_ITEM3));
	auto BuyItemButton4=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_ITEM4));
	auto BuyItemButton5=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_ITEM5));
	QuitButton->addTouchEventListener(this,toucheventselector(IShop::onTouchCloseItem));
	BuyItemButton1->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButton2->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButton3->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButton4->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButton5->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	
	Text* Money_text=(Text*)(ShopUI->getChildByTag(54));
	std::string money;
	//Get gold coins from  user default database
	int m=UserDefault::sharedUserDefault()->getIntegerForKey("myGold");
	coins = m;
	//Display the number of coins
	std::stringstream ss;
	ss << m;
	std::string s1=ss.str();
	Money_text->setString(s1);

	return true;
}

void IShop::onTouchCloseItem(Object* pSender, TouchEventType type){
	this->removeFromParentAndCleanup(true);
}

void IShop::onTouchBuyButton(Object* pSender, TouchEventType type){
	int tag = (static_cast<Button*>(pSender))->getTag();

	switch (type)
	{
	case  TOUCH_EVENT_ENDED:
		switch (tag)
		{
		case UI_BUTTON_BUY_ITEM1:
			{
				int n=UserDefault::sharedUserDefault()->getIntegerForKey("Item1");
				UserDefault::sharedUserDefault()->setIntegerForKey("Item1",++n);
			}
			break;
		case UI_BUTTON_BUY_ITEM2:
			{
				int n=UserDefault::sharedUserDefault()->getIntegerForKey("Item2");
				UserDefault::sharedUserDefault()->setIntegerForKey("Item2",++n);
			}
			break;
		case UI_BUTTON_BUY_ITEM3:
			{
				int n=UserDefault::sharedUserDefault()->getIntegerForKey("Item3");
				UserDefault::sharedUserDefault()->setIntegerForKey("Item3",++n);
			}
			break;
		case UI_BUTTON_BUY_ITEM4:
			{
				int n=UserDefault::sharedUserDefault()->getIntegerForKey("Item4");
				UserDefault::sharedUserDefault()->setIntegerForKey("Item4",++n);
			}
			break;
		case UI_BUTTON_BUY_ITEM5:
			{
				int n=UserDefault::sharedUserDefault()->getIntegerForKey("Item5");
				UserDefault::sharedUserDefault()->setIntegerForKey("Item5",++n);
			}
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}