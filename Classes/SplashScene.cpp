#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Defnition.h"
//#define schedule_selector CC_SCHEDULE_SELECTOR
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector



Scene* SplashScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SplashScene::create();

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
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist", "sprites.png");
	/////////////////////////////
	this->scheduleOnce(schedule_selector(SplashScene::GotoMainMenuScene), DISPLAY_SPLASH_SCENE);
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	auto backgound = Sprite::create("Background.png");
	backgound->setPosition(visibleSize / 2);
	this->addChild(backgound);
	// add a "close" icon to exit the progress. it's an autorelease object

	return true;

}





void SplashScene::menuCloseCallback(Ref* pSender)
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

void SplashScene::GotoMainMenuScene(float dt)
{
	/*auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITTION_TIME, scene));*/

	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITTION_TIME, scene));
}
