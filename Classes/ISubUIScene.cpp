#include "ISubUIScene.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "EndlessGameScene.h"
#include "ResourceManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int UI_BUTTON_GROWUP_MODE = 5;
const int UI_BUTTON_DOCTOR_MODE = 6;
const int UI_BUTTON_CLOSESELECTOR = 10;
const int UI_CHECKBOX_BACKGROUND_MUSIC = 11;
const int UI_CHECKBOX_SOUND_EFFECT = 12;
const int UI_BUTTON_CLOSESETTER = 18;
const int UI_BUTTON_RETURN = 6;
const int UI_BUTTON_SHOP = 7;
const int UI_BUTTON_HEALTH = 8;
const int UI_BUTTON_HOME = 8;
//Tags for select mode UI
const int UI_SECTIONSELECT = 60;
const int UI_BUTTON_SELECT_BABY = 61;
const int UI_BUTTON_SELECT_KID = 62;
const int UI_BUTTON_SELECT_CHILD = 63;
const int UI_BUTTON_SELECT_YOUTH =64;
// Tags for shop UI 
const int UI_BUTTON_CLOSESHOP=29;
const int UI_ICON_RESTOREHP = 30;
const int UI_ICON_SLOWDOWM = 35;
const int UI_ICON_SAFEGUARD = 43;
const int UI_ICON_LANDMINE = 47;
const int UI_ICON_TRAP = 49;
const int UI_ICON_ASSIST = 98;
const int UI_NOTE_NUM_RESTOREHP = 75;
const int UI_NOTE_NUM_SLOWDOWN = 78;
const int UI_NOTE_NUM_SAFEGUARD = 80;
const int UI_NOTE_NUM_LANDMINE = 81;
const int UI_NOTE_NUM_TRAP = 82;
const int UI_NOTE_NUM_ASSIST = 99;
const int UI_LOCK_SLOWDOWN = 104;
const int UI_LOCK_SAFEGUARD = 105;
const int UI_LOCK_LANDMINE = 106;
const int UI_LOCK_TRAP = 107;
const int UI_LOCK_ASSIST = 108;
const int UI_BUTTON_BUY_RESTOREHP = 32;
const int UI_BUTTON_BUY_SLOWDOWN = 36;
const int UI_BUTTON_BUY_SAFEGUARD = 44;
const int UI_BUTTON_BUY_LANDMINE = 48;
const int UI_BUTTON_BUY_TRAP = 101;
const int UI_BUTTON_BUY_ASSIST = 50;
const int UI_MONEYTEXT = 54;
const int UI_BUTTON_ADDMONEY = 110;



TTFConfig configShop("fonts/cardFont.ttf",24);

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
			{
				auto gameScene = Endless::createScene();
				Director::getInstance()->replaceScene(gameScene);
			}
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
	
	//musicCheckBox->setSelectedState(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying());
	musicCheckBox->setSelectedState(ResourceManager::getInstance()->isBackgroundMusicAllow());
	effectCheckBox->setSelectedState(ResourceManager::getInstance()->isEffectMusicAllow());
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
				ResourceManager::getInstance()->setBackgroundMusic(false);
				break;
	case CHECKBOX_STATE_EVENT_SELECTED:
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/MenuBackgroundMusic.mp3",true);
				//CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
				ResourceManager::getInstance()->setBackgroundMusic(true);
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
			//CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
			ResourceManager::getInstance()->setEffectMusic(false);
			break;
	case  CHECKBOX_STATE_EVENT_SELECTED:
			//CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
			ResourceManager::getInstance()->setEffectMusic(true);
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
	this->addChild(sectionSelector);

	auto babyButton = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_BABY));
	auto kidButtion = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_KID));
	auto childButton = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_CHILD));
	auto youthButton = static_cast<Button*>(Helper::seekWidgetByTag(sectionSelector,UI_BUTTON_SELECT_YOUTH));
	babyButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	kidButtion->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	childButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	youthButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));

	auto menuBar = GUIReader::getInstance()->widgetFromJsonFile("UI/chooseBar_1/chooseBar_1.ExportJson");
	this->addChild(menuBar);
	auto returnButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_RETURN));
	auto shopButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_SHOP));
	auto healthButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_HEALTH));
	returnButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchBar));
	shopButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchBar));
	healthButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchBar));
	
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

void ISectionSelector::onTouchBar(Object* pSender, TouchEventType type)
{
	int tag = (static_cast<Button*>(pSender))->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		switch (tag)
		{
		case UI_BUTTON_RETURN:{
			auto homescene = IHomeMenu::createScene();
			Director::getInstance()->replaceScene(homescene);
			break;
							  }
		case UI_BUTTON_SHOP:{
			auto shopUI = IShop::create();
			this->addChild(shopUI);
			break;
							}
		default:
			break;
		}
		break;
	default:
		break;
	}
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

	auto bgimg = Sprite::create("UI/sectionSelect_1/sectionSelect0.png", Rect(0, 0, 1280, 720));
	bgimg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(bgimg, 0);

	/*auto returnItem = MenuItemImage::create("back.png","back.png",CC_CALLBACK_1(IGameLevelSelector::menuReturnCallback,this));
	returnItem->setPosition(Vec2(origin.x + visibleSize.width - returnItem->getContentSize().width / 2, origin.y + returnItem->getContentSize().height /2));
	auto menu = Menu::create(returnItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, ZORDER_MENU);	*/

	auto menuBar = GUIReader::getInstance()->widgetFromJsonFile("UI/chooseBar_2/chooseBar_2.ExportJson");
	this->addChild(menuBar);
	auto returnButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_RETURN));
	auto shopButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_SHOP));
	auto homeButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_HOME));
	returnButton->addTouchEventListener(this,toucheventselector(IGameLevelSelector::ontouchBar));
	shopButton->addTouchEventListener(this,toucheventselector(IGameLevelSelector::ontouchBar));
	homeButton->addTouchEventListener(this,toucheventselector(IGameLevelSelector::ontouchBar));

	TableView* tableView = TableView::create(this,visibleSize);      // 创建一个tableView
	tableView->setDirection(TableView::Direction::HORIZONTAL);   // 设置方向
	tableView->setPosition(origin.x, origin.y + 200);      //设置位置
	tableView->setDelegate(this);  //该步骤非常关键，把tableView和当前类绑定在一起，故后面后面调用的主体是tableView
	this->addChild(tableView,0);
	tableView->reloadData();  

	return true;
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
	auto gamescene1 = Game::createScene(m_section, i);
	Director::getInstance()->replaceScene(gamescene1);
}

Size IGameLevelSelector::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	return Size(860,400);
}

//设置数据源tableCellAtIndex
TableViewCell* IGameLevelSelector::tableCellAtIndex(TableView* table, ssize_t idx)
{
//	String* string = String::createWithFormat("%d", idx);
	TableViewCell* cell = table->dequeueCell();

	if (!cell)
	{
		//创建单元，如果自定义单元效果，需要继承tableViewCell, 并且重载draw
		cell = TableViewCell::create();
//		cell->autorelease();
		idx++;
		auto str = String::createWithFormat("Map/Section%d/%d/%d.png", m_section, idx, idx);
		Sprite* sprite = Sprite::create(str->getCString());
		auto cellSize = tableCellSizeForIndex(table, idx);
		sprite->setScale(0.5f);
		sprite->setPosition(Vec2(cellSize.width/2,cellSize.height/2));
		cell->addChild(sprite);

// 		auto label = LabelTTF::create(string->getCString(),"Helvetica",20.0);
// 		label->setPosition(Vec2(cellSize.width/2 -10,200));
// 		label->setTag(456);
// 		cell->addChild(label);
	}
// 	else
// 	{
// 		auto label = (LabelTTF*)cell->getChildByTag(456);
// 		label->setString(string->getCString());
// 	}

	return cell;
}

ssize_t IGameLevelSelector::numberOfCellsInTableView(TableView* table)
{
	//Manager控制个数
	int ret = ResourceManager::getInstance()->sections[m_section-1].getRows();
	return ret;
}


void IGameLevelSelector::ontouchBar(Object* pSender, TouchEventType type)
{
	int tag = (static_cast<Button*>(pSender))->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		switch (tag)
		{
		case UI_BUTTON_RETURN:{
			auto sectionScene = ISectionSelector::createScene();
			Director::getInstance()->replaceScene(sectionScene);
			break;
							  }
		case UI_BUTTON_SHOP:{
			auto shopUI = IShop::create();
			this->addChild(shopUI);
			break;
							}
		case UI_BUTTON_HOME:{
			auto homescene = IHomeMenu::createScene();
			Director::getInstance()->replaceScene(homescene);
			break;
							}
		default:
			break;
		}
		break;
	default:
		break;
	}
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

	auto ShopUI = GUIReader::getInstance()->widgetFromJsonFile("UI/store_1/store_1.ExportJson");
	this->addChild(ShopUI);
	auto QuitButton= static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_CLOSESHOP));
	auto BuyItemButtonRHP=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_RESTOREHP));
	auto BuyItemButtonSD=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_SLOWDOWN));
	auto BuyItemButtonSG=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_SAFEGUARD));
	auto BuyItemButtonLM=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_LANDMINE));
	auto BuyItemButtonTP=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_TRAP));
	auto BuyItemButtonAS=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_BUTTON_BUY_ASSIST));
	auto IconRhp = static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_ICON_RESTOREHP));
	auto IconSD = static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_ICON_SLOWDOWM));
	auto IconSG = static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_ICON_SAFEGUARD));
	auto IconLM = static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_ICON_LANDMINE));
	auto IconTP = static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_ICON_TRAP));
	auto IconAS = static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_ICON_ASSIST));
	QuitButton->addTouchEventListener(this,toucheventselector(IShop::onTouchCloseItem));
	BuyItemButtonRHP->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButtonSD->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButtonSG->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButtonLM->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButtonTP->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	BuyItemButtonAS->addTouchEventListener(this,toucheventselector(IShop::onTouchBuyButton));
	item1_num=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_NOTE_NUM_RESTOREHP));
	item2_num=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_NOTE_NUM_SLOWDOWN));
	item3_num=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_NOTE_NUM_SAFEGUARD));
	item4_num=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_NOTE_NUM_LANDMINE));
	item5_num=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_NOTE_NUM_TRAP));
	item6_num=static_cast<Button*>(Helper::seekWidgetByTag(ShopUI,UI_NOTE_NUM_ASSIST));
	auto LockItemSD = Helper::seekWidgetByTag(ShopUI,UI_LOCK_SLOWDOWN);
	auto LockItemSG = Helper::seekWidgetByTag(ShopUI,UI_LOCK_SAFEGUARD);
	auto LockItemLM = Helper::seekWidgetByTag(ShopUI,UI_LOCK_LANDMINE);
	auto LockItemTrap = Helper::seekWidgetByTag(ShopUI,UI_LOCK_TRAP);
	auto LockItemAS = Helper::seekWidgetByTag(ShopUI,UI_LOCK_ASSIST);
	Money_text=(Text*)(ShopUI->getChildByTag(UI_MONEYTEXT));
	////////////////////////////////////////////////////////////////////////////
	ResourceManager* instance=ResourceManager::getInstance();
	HCSVFile* data = instance->propsData;
 
	for(int i = 0 ;i<=5;i++){
		price[i]=atoi(data->getData(i,2));
	}

	//auto priceLabel1 = Label::createWithTTF(configShop,std::to_string(1));
	Label* priceLabeRHP = Label::createWithTTF(configShop,data->getData(0,2));
	priceLabeRHP->setPosition(ccpAdd(BuyItemButtonRHP->getPosition(),Vec2(8,0)));
	this->addChild(priceLabeRHP);
	int num = UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(0,1));
	if(num<=0){
		item1_num->setVisible(false);
	}
	else{
		std::stringstream ss;
		ss<<num;
		std::string s1=ss.str();
		item1_num->setTitleText(s1);
	}

	int health = UserDefault::sharedUserDefault()->getIntegerForKey("Health");
	int section = UserDefault::sharedUserDefault()->getIntegerForKey("Section");
	
	if(health <= 0){
		BuyItemButtonSD->setTouchEnabled(false);
		BuyItemButtonSD->setVisible(false);
		BuyItemButtonSG->setTouchEnabled(false);
		BuyItemButtonSG->setVisible(false);
		BuyItemButtonLM->setTouchEnabled(false);
		BuyItemButtonLM->setVisible(false);
		BuyItemButtonTP->setTouchEnabled(false);
		BuyItemButtonTP->setVisible(false);
		BuyItemButtonAS->setTouchEnabled(false);
		BuyItemButtonAS->setVisible(false);
		IconSD->setVisible(false);
		IconSG->setVisible(false);
		IconLM->setVisible(false);
		IconTP->setVisible(false);
		IconAS->setVisible(false);
	}
	else{
		LockItemSD->setVisible(false);
		Label* priceLabeSD = Label::createWithTTF(configShop,data->getData(1,2));
		priceLabeSD->setPosition(ccpAdd(BuyItemButtonSD->getPosition(),Vec2(8,0)));
		this->addChild(priceLabeSD);
		num=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(1,1));
		if(num<=0){
			item2_num->setVisible(false);
		}
		else{
			std::stringstream ss;
			ss<<num;
			std::string s1=ss.str();
			item2_num->setTitleText(s1);
		}

		if(section < 2){
			BuyItemButtonSG->setTouchEnabled(false);
			BuyItemButtonSG->setVisible(false);
			BuyItemButtonLM->setTouchEnabled(false);
			BuyItemButtonLM->setVisible(false);
			BuyItemButtonTP->setTouchEnabled(false);
			BuyItemButtonTP->setVisible(false);
			BuyItemButtonAS->setTouchEnabled(false);
			BuyItemButtonAS->setVisible(false);
			IconSG->setVisible(false);
			IconLM->setVisible(false);
			IconTP->setVisible(false);
			IconAS->setVisible(false);
		}
		else{
			LockItemSG->setVisible(false);
			Label* priceLabeSG = Label::createWithTTF(configShop,data->getData(2,2));
			priceLabeSG->setPosition(ccpAdd(BuyItemButtonSG->getPosition(),Vec2(8,0)));
			this->addChild(priceLabeSG);
			num=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(2,1));
			if(num<=0){
				item3_num->setVisible(false);
			}
			else{
				std::stringstream ss;
				ss<<num;
				std::string s1=ss.str();
				item3_num->setTitleText(s1);
			}
			LockItemLM->setVisible(false);
			Label* priceLabeLM = Label::createWithTTF(configShop,data->getData(3,2));
			priceLabeLM->setPosition(ccpAdd(BuyItemButtonLM->getPosition(),Vec2(8,0)));
			this->addChild(priceLabeLM);
			num=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(3,1));
			if(num<=0){
				item4_num->setVisible(false);
			}
			else{
				std::stringstream ss;
				ss<<num;
				std::string s1=ss.str();
				item4_num->setTitleText(s1);
			}
		}
		if(section < 3){
			BuyItemButtonTP->setTouchEnabled(false);
			BuyItemButtonTP->setVisible(false);
			BuyItemButtonAS->setTouchEnabled(false);
			BuyItemButtonAS->setVisible(false);
			IconTP->setVisible(false);
			IconAS->setVisible(false);
		}
		else{
			LockItemTrap->setVisible(false);
			Label* priceLabeTP = Label::createWithTTF(configShop,data->getData(4,2));
			priceLabeTP->setPosition(ccpAdd(BuyItemButtonTP->getPosition(),Vec2(8,0)));
			this->addChild(priceLabeTP);
			num=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(4,1));
			if(num<=0){
				item5_num->setVisible(false);
			}
			else{
				std::stringstream ss;
				ss<<num;
				std::string s1=ss.str();
				item5_num->setTitleText(s1);
			}
			LockItemAS->setVisible(false);
			Label* priceLabeAS = Label::createWithTTF(configShop,data->getData(5,2));
			priceLabeAS->setPosition(ccpAdd(BuyItemButtonAS->getPosition(),Vec2(8,0)));
			this->addChild(priceLabeAS);
			num=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(5,1));
			if(num<=0){
				item6_num->setVisible(false);
			}
			else{
				std::stringstream ss;
				ss<<num;
				std::string s1=ss.str();
				item6_num->setTitleText(s1);
			}
		}
	}

	std::string money;
	int m=UserDefault::sharedUserDefault()->getIntegerForKey("myGold");
	coins=m;
	std::stringstream ss;
	ss<<m;
	std::string s1=ss.str();
	Money_text->setString(s1); 
	return true;
}

void IShop::onTouchCloseItem(Object* pSender, TouchEventType type){
	this->removeFromParentAndCleanup(true);
}

void IShop::onTouchBuyButton(Object* pSender, TouchEventType type){
	int tag = (static_cast<Button*>(pSender))->getTag();
	HCSVFile* data = ResourceManager::getInstance()->propsData;
	switch (type)
	{
	case  TOUCH_EVENT_ENDED:
		switch (tag)
		{
		case UI_BUTTON_BUY_RESTOREHP:
			{
				if(coins>=price[0]){
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(0,1));
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(0,1),++n);
					coins=coins-price[0];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					std::stringstream ss;
					ss<<coins;
					std::string s1=ss.str();
					Money_text->setString(s1);
					std::stringstream ss2;
					ss2<<n;
					s1=ss2.str();
					item1_num->setTitleText(s1);
					item1_num->setVisible(true);
				}
				else
				{
					CCLog("购买失败");
				}
			}
			break;
		case UI_BUTTON_BUY_SLOWDOWN:
			{
				if(coins>=price[1]){
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(1,1));
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(1,1),++n);
					coins=coins-price[1];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					std::stringstream ss;
					ss<<coins;
					std::string s1=ss.str();
					Money_text->setString(s1);
					std::stringstream ss2;
					ss2<<n;
					s1=ss2.str();
					item2_num->setTitleText(s1);
					item2_num->setVisible(true);
				}
				else
				{
					CCLog("购买失败");
				}
			}
			break;
		case UI_BUTTON_BUY_SAFEGUARD:
			{
				if(coins>=price[2]){
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(2,1));
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(2,1),++n);
					coins=coins-price[2];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					std::stringstream ss;
					ss<<coins;
					std::string s1=ss.str();
					Money_text->setString(s1);
					std::stringstream ss2;
					ss2<<n;
					s1=ss2.str();
					item3_num->setTitleText(s1);
					item3_num->setVisible(true);
				}
				else
				{
					CCLog("购买失败");
				}
			}
			break;
		case UI_BUTTON_BUY_LANDMINE:
			{
				if(coins>=price[3]){
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(3,1));
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(3,1),++n);
					coins=coins-price[3];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					std::stringstream ss;
					ss<<coins;
					std::string s1=ss.str();
					Money_text->setString(s1);
					std::stringstream ss2;
					ss2<<n;
					s1=ss2.str();
					item4_num->setTitleText(s1);
					item4_num->setVisible(true);
				}
				else
				{
					CCLog("购买失败");
				}
			}
			break;
		case UI_BUTTON_BUY_TRAP:
			{
				if(coins>=price[4]){
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(4,1));
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(4,1),++n);
					coins=coins-price[4];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					std::stringstream ss;
					ss<<coins;
					std::string s1=ss.str();
					Money_text->setString(s1);
					std::stringstream ss2;
					ss2<<n;
					s1=ss2.str();
					item5_num->setTitleText(s1);
					item5_num->setVisible(true);
				}
				else
				{
					CCLog("购买失败");
				}
			}
			break;
		case UI_BUTTON_BUY_ASSIST:
			{
				if(coins>=price[5]){
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(5,1));
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(5,1),++n);
					coins=coins-price[5];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					std::stringstream ss;
					ss<<coins;
					std::string s1=ss.str();
					Money_text->setString(s1);
					std::stringstream ss2;
					ss2<<n;
					s1=ss2.str();
					item6_num->setTitleText(s1);
					item6_num->setVisible(true);
				}
				else
				{
					CCLog("购买失败");
				}
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