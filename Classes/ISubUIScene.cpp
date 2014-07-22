#include "ISubUIScene.h"
#include "AppDelegate.h"
#include "GameScene.h"


USING_NS_CC;
USING_NS_CC_EXT;

const int UI_BUTTON_GROWUP_MODE = 5;
const int UI_BUTTON_DOCTOR_MODE = 6;
const int UI_BUTTON_CLOSESELECTOR = 10;
const int UI_CHECKBOX_BACKGROUND_MUSIC = 11;
const int UI_CHECKBOX_SOUND_EFFECT = 12;
const int UI_BUTTON_CLOSESETTER = 18;


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
				auto gameLevelSelector = IGameLevelSelector::createScene();
				Director::getInstance()->replaceScene(gameLevelSelector);
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
	
	musicCheckBox->setSelectedState(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying());
	//if(SimpleAudioEngine::getInstance()->
	//effectCheckBox->setSelectedState(true);
	
	return true;
}

void IBGMusicSetter::onSelectedBGMusic(Object* pSender, CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_UNSELECTED:
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				break;
	case CHECKBOX_STATE_EVENT_SELECTED:
				CocosDenshion::SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
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
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
			break;
	case  CHECKBOX_STATE_EVENT_SELECTED:
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
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




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene* IGameLevelSelector::createScene()
{
	auto scene = Scene::create();
	auto layer = IGameLevelSelector::create();
	scene->addChild(layer);
	return scene;
}

bool IGameLevelSelector::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::sharedDirector()->getWinSize();
	/*
	auto returnItem = MenuItemImage::create("CloseNormol.png","CloseSelected.png",CC_CALLBACK_1(IGameLevelSelector::menuReturnCallback,this));
	//returnItem->setPosition(Vec2(winSize.width - returnItem->getContentSize().width / 2, returnItem->getContentSize().height /2));
	auto menu = Menu::create(returnItem,NULL);
	//menu->setPosition(Vec2(0,winSize.height - returnItem->getContentSize().height));
	//menu->setPosition(Vec2(300,300));
	this->addChild(menu);
	*/
	/*
	auto bgimg = Sprite::create("bg.png");
	this->addChild(bgimg);
	*/

	TableView* tableView = TableView::create(this,winSize);      //����һ��tableView
	//tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	//tableView->setDirection(HORIZONTAL);
	tableView->setDirection(TableView::Direction::HORIZONTAL);   //���÷���
	//tableView->setPosition(Vec2(20,winSize.height/2 - 200));      //����λ��
	tableView->setPosition(Vec2(0,0));      //����λ��
	tableView->setDelegate(this);  //�ò���ǳ��ؼ�����tableView�͵�ǰ�����һ�𣬹ʺ��������õ�������tableView
	this->addChild(tableView,0);
	tableView->reloadData();  //
	
	return true;
}

void IGameLevelSelector::menuReturnCallback(Ref* pSender)
{
	auto homeMenu = IHomeMenu::createScene();
	Director::getInstance()->replaceScene(homeMenu);
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
	if (i == 1)
	{
		auto gamescene1 = Game::createScene();
		Director::getInstance()->replaceScene(gamescene1);
	}
}

Size IGameLevelSelector::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	//return Size(500,400);
	return Size(600,720);
}

//��������ԴtableCellAtIndex
TableViewCell* IGameLevelSelector::tableCellAtIndex(TableView* table, ssize_t idx)
{
	String* string = String::createWithFormat("%d", idx);
	TableViewCell* cell = table->dequeueCell();

	if (!cell)
	{
		//������Ԫ������Զ��嵥ԪЧ������Ҫ�̳�tableViewCell, ��������draw
		cell = new TableViewCell();
		cell->autorelease();
		Sprite* sprite = Sprite::create("HelloWorld.png");
		auto cellSize = tableCellSizeForIndex(table, idx);
		sprite->setPosition(Vec2(cellSize.width/2,cellSize.height/2));
		//sprite->setTag(123);
		cell->addChild(sprite);

		auto label = LabelTTF::create(string->getCString(),"Helvetica",20.0);
		label->setPosition(Vec2(cellSize.width/2 -10,200));
		//label->setAnchorPoint(Vec2::ZERO);
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
	return 10;
}