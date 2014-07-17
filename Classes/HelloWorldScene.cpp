#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	Node* m_node = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("UI/publish/Start.json");
	if (m_node)
	{
		this->addChild(m_node);
	}


	auto render = static_cast<cocostudio::ComRender*>(m_node->getChildByTag(10006)->getComponent("menu"));
	auto widget = static_cast<cocos2d::ui::Widget*>(render->getNode());
	
	cocos2d::ui::Button* playgame = static_cast<cocos2d::ui::Button*>(widget->getChildByName("PlayGame"));
	cocos2d::ui::Button* setup = static_cast<cocos2d::ui::Button*>(widget->getChildByName("Setup"));
	cocos2d::ui::Button* quit = static_cast<cocos2d::ui::Button*>(widget->getChildByName("Quit"));

	//°ó¶¨ÊÂ¼þ¼àÌý
	playgame->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchButton, this));
	setup->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchButton, this));
	quit->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchButton, this));
    return true;
}



void HelloWorld::touchButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	auto button = static_cast<cocos2d::ui::Button*>(pSender);

	std::string name = button->getName();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (name == "PlayGame")
		{
			
			auto s1 = Game::createScene();


			//auto ss = TransitionFade::create(0.1,s1);
			Director::getInstance()->replaceScene(s1);
		} 
		else if(name == "Setup")
		{
			auto s2 = SetScene::createScene();
			//auto ss = TransitionFade::create(0.1,s2);
			Director::getInstance()->replaceScene(s2);
		}
		else if(name == "Quit")
		{
			 Director::getInstance()->end();
		}
		break;		
	default:
		break;
	}
}
