//There are some UIs for the game.
#ifndef __ISUBUISCENE_H__
#define __ISUBUISCENE_H__

#include "IHomeMenuScene.h"
//#include "extensions/cocos-ext.h"

// UI for select game mode.
class IModeSelector : public cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IModeSelector);
private:
	void onTouchSelectButton(Object* pSender, TouchEventType type);
	
};



// UI for set up the background music and sound effect.
class IBGMusicSetter : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IBGMusicSetter);

private:
	void onSelectedBGMusic(Object* pSender, CheckBoxEventType type);
	void onSelectedSoundEffects(Object* pSender, CheckBoxEventType type);
	void onTouchCloseItem(Object* pSender, TouchEventType type);
};




// UI for select game section
class ISectionSelector : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ISectionSelector);
private:
	int m_section;
	void onTouchSelected(Object* pSender, TouchEventType type);
	void onTouchBar(Object* pSender, TouchEventType type);
};




// UI for select the game level
class IGameLevelSelector : public cocos2d::Layer , public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene(int section);
	bool init(int section);
	static IGameLevelSelector* create(int section);

	// 滚动时调用，空实现，（继承/因为继承了抽象类所以必须重写 ）
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
	// 缩放时调用，空实现，同上
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
	// 触摸单元时调用
	virtual void tableCellTouched(cocos2d::extension::TableView* table, TableViewCell* cell);
	// 设定单元大小
	virtual cocos2d::Size tableCellSizeForIndex(TableView* table, ssize_t idx);
	// 设定单元内容
	virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idx);
	// 返回单元的个数 类型是ssize_t
	virtual ssize_t numberOfCellsInTableView(TableView* table);

	// 按下去时就是高亮显示，该处设置高亮状态
	//virtual void tableCellHightlight(TableView* table, TableViewCell* cell);
	// 松开时取消高亮状态
	//virtual void tableCellUnhightlight(TableView* table, TableViewCell* cell);

	//void scrollBar(TableView* table);
	void ontouchBar(Object* pSender, TouchEventType type);

private:
	int m_section;
	int m_curSection;
	int m_curLevel;
	
};



// UI for shop
class IShop : public cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IShop);
	void onTouchCloseItem(Object* pSender, TouchEventType type);
	void onTouchBuyButton(Object* pSender, TouchEventType type);
	int coins;
	int price[6];
	Label* moneylabel;
	Button* item1_num;
	Button* item2_num;
	Button* item3_num;
	Button* item4_num;
	Button* item5_num;
	Button* item6_num;
private:

};



class ISuccessPage : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ISuccessPage);
	void ontouchButton(Object* pSender, TouchEventType type);
};



class IIntroPage : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IIntroPage);
	void ontouchButton(Object* pSender, TouchEventType type);
private:
	Widget* intro_g1;
	Widget* intro_g2;
	Widget* intro_g3;
	Widget* intro_g4;
	Widget* intro_g5;
	Widget* intro_g6;
	Widget* intro_g7;
	Widget* intro_g8;
	Widget* intro_g9;
	Widget* intro_g10;
	Widget* intro_g11;
	Widget* intro_g12;
	Widget* intro_first;
};

#endif