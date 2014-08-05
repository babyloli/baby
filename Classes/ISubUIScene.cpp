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
const int UI_BUTTON_RETURN = 13;
const int UI_BUTTON_SHOP = 14;
const int UI_BUTTON_HEALTH = 15;
const int UI_BUTTON_HOME = 15;
//Tags for select mode UI
const int UI_SECTIONSELECT = 60;
const int UI_BUTTON_SELECT_BABY = 61;
const int UI_BUTTON_SELECT_KID = 62;
const int UI_BUTTON_SELECT_CHILD = 63;
const int UI_BUTTON_SELECT_YOUTH =64;
const int UI_LOCK_KID = 65;
const int UI_LOCK_CHILD = 66;
const int UI_LOCK_YOUTH = 67;
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
const int UI_BUTTON_SUCCESS_RETURN = 6;   
const int UI_BUTTON_SUCCESS_YES = 5;
//TAGs for Intro page
const int UI_BUTTON_INTRO_G1 = 1001;
const int UI_BUTTON_INTRO_G2 = 1002;
const int UI_BUTTON_INTRO_G3 = 1003;
const int UI_BUTTON_INTRO_G4 = 1004;
const int UI_BUTTON_INTRO_G5 = 1005;
const int UI_BUTTON_INTRO_G6 = 1006;
const int UI_BUTTON_INTRO_G7 = 1007;
const int UI_BUTTON_INTRO_G8 = 1008;
const int UI_BUTTON_INTRO_G9 = 1009;
const int UI_BUTTON_INTRO_G10 = 1010;
const int UI_BUTTON_INTRO_G11 = 1011;
const int UI_BUTTON_INTRO_G12 = 1012;
const int UI_DISPLAY_INTRO_G1 = 1013;
const int UI_DISPLAY_INTRO_G2 = 1014;
const int UI_DISPLAY_INTRO_G3 = 1015;
const int UI_DISPLAY_INTRO_G4 = 1016;
const int UI_DISPLAY_INTRO_G5 = 1017;
const int UI_DISPLAY_INTRO_G6 = 1018;
const int UI_DISPLAY_INTRO_G7 = 1019;
const int UI_DISPLAY_INTRO_G8 = 1020;
const int UI_DISPLAY_INTRO_G9 = 1021;
const int UI_DISPLAY_INTRO_G10 = 1022;
const int UI_DISPLAY_INTRO_G11 = 1023;
const int UI_DISPLAY_INTRO_G12 = 1024;
const int UI_DISPLAY_INTRO_FIR = 1025;
const int UI_INTRO_CLOSE = 1026;



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
	auto lockKid = Helper::seekWidgetByTag(sectionSelector,UI_LOCK_KID);
	auto lockChild = Helper::seekWidgetByTag(sectionSelector,UI_LOCK_CHILD);
	auto lockYouth = Helper::seekWidgetByTag(sectionSelector,UI_LOCK_YOUTH);
	babyButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	kidButtion->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	childButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));
	youthButton->addTouchEventListener(this,toucheventselector(ISectionSelector::onTouchSelected));

	int section = UserDefault::sharedUserDefault()->getIntegerForKey("Section");
	switch (section)
	{
	case 0:
	case 1:
		{
			kidButtion->setTouchEnabled(false);
			kidButtion->setVisible(false);
			childButton->setTouchEnabled(false);
			childButton->setVisible(false);
			youthButton->setTouchEnabled(false);
			youthButton->setVisible(false);
			break;
		}
	case 2:
		{
			lockKid->setVisible(false);
			childButton->setTouchEnabled(false);
			childButton->setVisible(false);
			youthButton->setTouchEnabled(false);
			youthButton->setVisible(false);
			break;
		}
	case 3:
		{
			lockKid->setVisible(false);
			lockChild->setVisible(false);
			youthButton->setTouchEnabled(false);
			youthButton->setVisible(false);
			break;
		}
	case 4:
		{
			lockKid->setVisible(false);
			lockChild->setVisible(false);
			lockYouth->setVisible(false);
			break;
		}
	default:
		{
			lockKid->setVisible(false);
			lockChild->setVisible(false);
			lockYouth->setVisible(false);
		}
		break;
	}

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
		case UI_BUTTON_HEALTH:{
			auto healthUI=IHealth::create();
			this->addChild(healthUI);
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

	auto menuBar = GUIReader::getInstance()->widgetFromJsonFile("UI/chooseBar_2/chooseBar_2.ExportJson");
	this->addChild(menuBar);
	auto returnButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_RETURN));
	auto shopButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_SHOP));
	auto homeButton = static_cast<Button*>(Helper::seekWidgetByTag(menuBar,UI_BUTTON_HOME));
	returnButton->addTouchEventListener(this,toucheventselector(IGameLevelSelector::ontouchBar));
	shopButton->addTouchEventListener(this,toucheventselector(IGameLevelSelector::ontouchBar));
	homeButton->addTouchEventListener(this,toucheventselector(IGameLevelSelector::ontouchBar));

	TableView* tableView = TableView::create(this,Size(1280, 360));      // 创建一个tableView
	tableView->setDirection(TableView::Direction::HORIZONTAL);   // 设置方向
	tableView->setPosition(origin.x, origin.y + 180);      //设置位置
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
	return Size(860,360);
}

//设置数据源tableCellAtIndex
TableViewCell* IGameLevelSelector::tableCellAtIndex(TableView* table, ssize_t idx)
{
	idx++;
	String* string = String::createWithFormat("%d", idx);
	TableViewCell* cell = table->dequeueCell();
	
	auto str = String::createWithFormat("Map/Section%d/%d/m%d.png", m_section, idx, idx);
	if (!cell)
	{
		//创建单元，如果自定义单元效果，需要继承tableViewCell, 并且重载draw
		cell = TableViewCell::create();
//		cell = new TableViewCell();
//		cell->autorelease();	
		
		Sprite* sprite = Sprite::create(str->getCString());
		auto cellSize = tableCellSizeForIndex(table, idx);
		//sprite->setScale(0.5f);
		sprite->setTag(123);
		sprite->setPosition(Vec2(cellSize.width/2,cellSize.height/2));
		cell->addChild(sprite);

// 		auto label = LabelTTF::create(string->getCString(),"Helvetica",60.0);
// 		label->setColor(Color3B(255, 0, 0));
		auto label = LabelBMFont::create(string->getCString(),FONT_GOLD);
		label->setScale(1.5f);
		label->setPosition(Vec2(cellSize.width/2 -10,200));
		label->setTag(456);
		cell->addChild(label);
	}
	else
	{
		Texture2D* texture = TextureCache::getInstance()->addImage(str->getCString());
		Sprite* sprite = (Sprite*)cell->getChildByTag(123);
		sprite->setTexture(texture);

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
	auto Money_text=(Text*)(ShopUI->getChildByTag(UI_MONEYTEXT));
	Money_text->setVisible(false);
	////////////////////////////////////////////////////////////////////////////
	ResourceManager* instance=ResourceManager::getInstance();
	HCSVFile* data = instance->propsData;
 
	for(int i = 0 ;i<=5;i++){
		price[i]=atoi(data->getData(i,2));
	}

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

	coins = UserDefault::sharedUserDefault()->getIntegerForKey("myGold");
	moneylabel = Label::createWithTTF(configShop,itos(coins));
	moneylabel->setPosition(Money_text->getPosition());
	this->addChild(moneylabel);

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
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(0,1)) + 1;
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(0,1),n);
					coins=coins-price[0];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					moneylabel->setString(itos(coins));
					item1_num->setTitleText(itos(n));
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
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(1,1))+1;
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(1,1),n);
					coins=coins-price[1];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					moneylabel->setString(itos(coins));
					item2_num->setTitleText(itos(n));
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
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(2,1)) + 1;
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(2,1),n);
					coins=coins-price[2];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					moneylabel->setString(itos(coins));
					item3_num->setTitleText(itos(n));
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
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(3,1))+1;
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(3,1),n);
					coins=coins-price[3];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					moneylabel->setString(itos(coins));
					item4_num->setTitleText(itos(n));
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
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(4,1)) + 1;
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(4,1),n);
					coins=coins-price[4];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					moneylabel->setString(itos(coins));
					item5_num->setTitleText(itos(n));
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
					int n=UserDefault::sharedUserDefault()->getIntegerForKey(data->getData(5,1))+1;
					UserDefault::sharedUserDefault()->setIntegerForKey(data->getData(5,1),n);
					coins=coins-price[5];
					UserDefault::sharedUserDefault()->setIntegerForKey("myGold",coins);
					moneylabel->setString(itos(coins));
					item6_num->setTitleText(itos(n));
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






//////////////////////////////////////////////////////////////////////////
Scene* ISuccessPage::createScene()
{
	auto scene = Scene::create();
	auto layer = ISuccessPage::create();
	scene->addChild(layer);
	return scene;
}

bool ISuccessPage::init()
{
	if(!Layer::init()){
		return false;
	}

	auto page = GUIReader::getInstance()->widgetFromJsonFile("UI/Final_1/Final_1.ExportJson");
	this->addChild(page);

	auto yesButton = static_cast<Button*>(Helper::seekWidgetByTag(page,UI_BUTTON_SUCCESS_YES));
	auto returnButton = static_cast<Button*>(Helper::seekWidgetByTag(page,UI_BUTTON_SUCCESS_RETURN));
	yesButton->addTouchEventListener(this,toucheventselector(ISuccessPage::ontouchButton));
	returnButton->addTouchEventListener(this,toucheventselector(ISuccessPage::ontouchButton));

	return true;
}

void ISuccessPage::ontouchButton(Object* pSender, TouchEventType type)
{
	switch (type)
	{
	case  TOUCH_EVENT_ENDED:
		{
			auto scene = IHomeMenu::createScene();
			Director::getInstance()->replaceScene(scene);
			Director::getInstance()->resume();
			break;
		}
	default:
		break;
	}
}






//////////////////////////////////////////////////////////////////////////
Scene* IIntroPage::createScene()
{
	auto scene = Scene::create();
	auto layer = IIntroPage::create();
	scene->addChild(layer);
	return scene;
}

bool IIntroPage::init()
{
	if(!Layer::init()){
		return false;
	}

	auto introPage = GUIReader::getInstance()->widgetFromJsonFile("UI/Intro_1/Intro_1.ExportJson");
	this->addChild(introPage);

	auto g1_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G1));
	auto g2_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G2));
	auto g3_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G3));
	auto g4_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G4));
	auto g5_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G5));
	auto g6_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G6));
	auto g7_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G7));
	auto g8_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G8));
	auto g9_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G9));
	auto g10_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G10));
	auto g11_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G11));
	auto g12_Button = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_BUTTON_INTRO_G12));
	auto closeButton = static_cast<Button*>(Helper::seekWidgetByTag(introPage,UI_INTRO_CLOSE));
	g1_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g2_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g3_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g4_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g5_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g6_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g7_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g8_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g9_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g10_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g11_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	g12_Button->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));
	closeButton->addTouchEventListener(this,toucheventselector(IIntroPage::ontouchButton));

	intro_g1 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G1);
	intro_g2 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G2);
	intro_g3 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G3);
	intro_g4 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G4);
	intro_g5 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G5);
	intro_g6 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G6);
	intro_g7 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G7);
	intro_g8 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G8);
	intro_g9 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G9);
	intro_g10 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G10);
	intro_g11 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G11);
	intro_g12 = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_G12);
	intro_first = Helper::seekWidgetByTag(introPage,UI_DISPLAY_INTRO_FIR);
	intro_g1->setVisible(false);
	intro_g2->setVisible(false);
	intro_g3->setVisible(false);
	intro_g4->setVisible(false);
	intro_g5->setVisible(false);
	intro_g6->setVisible(false);
	intro_g7->setVisible(false);
	intro_g8->setVisible(false);
	intro_g9->setVisible(false);
	intro_g10->setVisible(false);
	intro_g11->setVisible(false);
	intro_g12->setVisible(false);
	intro_first->setVisible(true);
	return true;
}

void IIntroPage::ontouchButton(Object* pSender, TouchEventType type)
{
	int tag = (static_cast<Button*>(pSender))->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		switch(tag){
		case UI_BUTTON_INTRO_G1:
			{
				intro_g1->setVisible(true);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G2:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(true);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G3:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(true);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G4:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(true);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G5:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(true);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G6:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(true);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G7:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(true);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G8:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(true);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G9:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(true);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G10:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(true);
				intro_g11->setVisible(false);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G11:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(true);
				intro_g12->setVisible(false);
				intro_first->setVisible(false);
				break;
			}
		case UI_BUTTON_INTRO_G12:
			{
				intro_g1->setVisible(false);
				intro_g2->setVisible(false);
				intro_g3->setVisible(false);
				intro_g4->setVisible(false);
				intro_g5->setVisible(false);
				intro_g6->setVisible(false);
				intro_g7->setVisible(false);
				intro_g8->setVisible(false);
				intro_g9->setVisible(false);
				intro_g10->setVisible(false);
				intro_g11->setVisible(false);
				intro_g12->setVisible(true);
				intro_first->setVisible(false);
				break;
			}
		case UI_INTRO_CLOSE:
			this->removeFromParentAndCleanup(true);
			break;
		}
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////
Scene* IHealth::createScene()
{
	auto scene = Scene::create();
	auto layer = IHealth::create();
	scene->addChild(layer);
	return scene;
}

bool IHealth::init()
{
	if(!Layer::init()){
		return false;
	}

	auto healthpage = GUIReader::getInstance()->widgetFromJsonFile("UI/HealthUi_1/HealthUi_1.ExportJson");
	this->addChild(healthpage);
	health1=(TextAtlas*)Helper::seekWidgetByTag(healthpage,11);
	health2=(TextAtlas*)Helper::seekWidgetByTag(healthpage,9);
	int health=UserDefault::getInstance()->getIntegerForKey("Health");
	health1->setStringValue(itos(health));
	int health3=(UserDefault::getInstance()->getIntegerForKey("Section"))*16-health;
	if(health3<=0||UserDefault::getInstance()->getIntegerForKey("Section")==4){
		health3=0;
	}
	health2->setString(itos(health3));
	auto back_Button = static_cast<Button*>(Helper::seekWidgetByTag(healthpage,14));
	back_Button->addTouchEventListener(this,toucheventselector(IHealth::ontouchButton));
	return true;
}

void IHealth::ontouchButton(Object* pSender, TouchEventType type){
	int tag = (static_cast<Button*>(pSender))->getTag();
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		switch(tag){
		case 14:{
			this->removeFromParentAndCleanup(true);
			break;
				}
		default:{
			break;
				}
		}
	}
}