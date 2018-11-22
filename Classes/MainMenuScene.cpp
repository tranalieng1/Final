﻿#include "MainMenuScene.h"
#include "GameOptions.h"
#include "SimpleAudioEngine.h"
#include "GameScene_1.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return MainMenuScene::create();
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
	//  super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	// add BackGround
	auto bgMenu = Sprite::create("bgMenu.jpg");
	//bgMenu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bgMenu);
	bgMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bgMenu->setPosition(this->getContentSize() * 0.5f);
	float scaleX = winSize.width*1.0 / (bgMenu->getContentSize().width);
	float scaleY = winSize.height*1.0 / (bgMenu->getContentSize().height);
	bgMenu->setScaleX(scaleX);
	bgMenu->setScaleY(scaleY);

	// add Font Menu
	//auto label = Label::createWithTTF("Phu-Manh-An", "fonts/An.ttf", 65);
	//if (label == nullptr)
	//{
	//	problemLoading("'fonts/Lobster-Regular.ttf'");
	//}
	//else
	//{
	//	// position the label on the center of the screen
	//	label->setPosition(Vec2(origin.x + visibleSize.width /2,
	//		origin.y + visibleSize.height - label->getContentSize().height));

	//	// add the label as a child to this layer
	//	this->addChild(label, 1);
	//}

	// add a "close" icon to exit the progress. it's an autorelease object
	//auto closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

	//if (closeItem == nullptr ||
	//	closeItem->getContentSize().width <= 0 ||
	//	closeItem->getContentSize().height <= 0)
	//{
	//	problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	//}
	//else
	//{
	//	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	//	float y = origin.y + closeItem->getContentSize().height / 2;
	//	closeItem->setPosition(Vec2(x, y));
	//}
	//// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);


	//add button Play
	auto playImage = MenuItemImage::create(
		"NEWGAME.png",
		"FON.png",
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	playImage->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.15f));
	auto menu1 = Menu::create(playImage, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);
	//btn Option
	auto optionsImage = MenuItemImage::create(
		"OPTIONS.png",
		"OPTIONS1.png",
		CC_CALLBACK_1(MainMenuScene::GoToGameOptions, this));
	optionsImage->setPosition(visibleSize.width /2 , visibleSize.height*0.05f );
	
	auto menu2 = Menu::create(optionsImage, NULL);
	menu2->setPosition(Vec2::ZERO);

//	menu2->setPosition(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(menu2, 1);

	/////////////////////////////



	return true;
}

//out cua nut close
//void MainMenuScene::menuCloseCallback(Ref* pSender)
//{
//	//Close the cocos2d-x game scene and quit the application
//	Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
//
//	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//	////EventCustom customEndEvent("game_scene_close_event");
//	////_eventDispatcher->dispatchEvent(&customEndEvent);
//
//
//}
//Chuyen den gamescene
void MainMenuScene::GoToGameScene(cocos2d::Ref * pSender)
{
	auto game = GameScene_1::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, game));
}

void MainMenuScene::GoToGameOptions(cocos2d::Ref * pSender)
{
	auto gameoptions =GameOptions ::createScene();
	Director::getInstance()->replaceScene(gameoptions);
}
