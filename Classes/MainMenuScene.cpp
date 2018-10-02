#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene_1.h"
#include "Defnition.h"
//#define schedule_selector CC_SCHEDULE_SELECTOR
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenuScene::create();

	scene->addChild(layer);
	return scene;

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	



	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	 _Playgame_button = MenuItemImage::create("playbutton.png","playbutton_Clicked.png",CC_CALLBACK_1(MainMenuScene::GotoGameScene,this));
	_Playgame_button->setPosition(visibleSize*0.5);
	 menu = Menu::create(_Playgame_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist", "sprites.png");
	/////////////////////////////
	
	// add a "close" icon to exit the progress. it's an autorelease object

	return true;

}
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

//void MainMenuScene::onTouchBegan_PlayButton(Ref * sender, cocos2d::ui::Widget::TouchEventType * type)
//{
//	
//}

void MainMenuScene::GotoGameScene(Ref * sender)
{
	auto scene = GameScene_1::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITTION_TIME, scene));
}
