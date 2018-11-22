#include "MainMenuScene.h"
#include"GameScene_1.h"
#include"GameOptions.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector
bool checksound = true;
bool checksound_2 = true;
Scene*GameOptions::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOptions::create();

	scene->addChild(layer);
	return scene;
}
bool GameOptions::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bgOptions = Sprite::create("bgOptions.jpg");
	//bgMenu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bgOptions);
	bgOptions->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bgOptions->setPosition(this->getContentSize() * 0.5f);
	float scaleX = winSize.width*1.0 / (bgOptions->getContentSize().width);
	float scaleY = winSize.height*1.0 / (bgOptions->getContentSize().height);
	bgOptions->setScaleX(scaleX);
	bgOptions->setScaleY(scaleY);
	if (checksound == true)
	{
		soundbutton = cocos2d::ui::Button::create("Sound_On.png", "Sound_On_Click.png");
	}
	else
	{
		soundbutton = cocos2d::ui::Button::create("Sound_Off.png", "Sound_Off_Click.png");
	}
	//soundbutton = cocos2d::ui::Button::create("Sound_On.png", "Sound_On_Click.png");
	soundbutton->setPosition(Vec2(visibleSize.width*0.85f, visibleSize.width*0.15f));
	soundbutton->setScale(0.35f);

	//if (checksound_2 == true)
	//{
	//	musicbutton = cocos2d::ui::Button::create("Sound_On_2.png", "Sound_On_Click_2.png");
	//}
	//else
	//{
	//	musicbutton = cocos2d::ui::Button::create("Sound_Off_2.png", "Sound_Off_Click_2.png");
	//}

	//musicbutton->setPosition(Vec2(visibleSize.width*0.65f, visibleSize.width*0.15f));
	//musicbutton->setScale(0.25f);


	this->addChild(soundbutton, 2);
	//this->addChild(musicbutton, 2);

	//musicbutton->addTouchEventListener(CC_CALLBACK_2(GameMenuScene::onTouchBegan_2, this));
	soundbutton->addTouchEventListener(CC_CALLBACK_2(GameOptions::onTouchBegan, this));




	auto playbutton = MenuItemImage::create("Comback.png", "Comback_click.png", CC_CALLBACK_1(GameOptions::CombackMainMenuScene, this));
	playbutton->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
	auto menu = Menu::create(playbutton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	// add a "close" icon to exit the progress. it's an autorelease object

	return true;
}
void GameOptions::onTouchBegan(Ref * senser, cocos2d::ui::Widget::TouchEventType type)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		if (checksound == true)
		{
			audio->pauseBackgroundMusic();
			checksound = false;
			soundbutton->loadTextures("Sound_Off.png", "Sound_Off_Click.png");
		}
		else
		{
			audio->resumeBackgroundMusic();
			checksound = true;
			soundbutton->loadTextures("Sound_On.png", "Sound_On_Click.png");
		}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:

		break;
	default:
		break;
	}
}

//void GameOptions::onTouchBegan_2(Ref * senser, cocos2d::ui::Widget::TouchEventType type)
//{
//	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
//	switch (type)
//	{
//	case cocos2d::ui::Widget::TouchEventType::BEGAN:
//		if (checksound_2 == true)
//		{
//			audio->setEffectsVolume(0);
//			checksound_2 = false;
//			musicbutton->loadTextures("Sound_Off_2.png", "Sound_Off_Click_2.png");
//		}
//		else
//		{
//			audio->setEffectsVolume(0);
//
//			checksound_2 = true;
//			musicbutton->loadTextures("Sound_On_2.png", "Sound_On_Click_2.png");
//		}
//	case cocos2d::ui::Widget::TouchEventType::CANCELED:
//
//		break;
//	default:
//		break;
//	}
//}

void GameOptions::CombackMainMenuScene(cocos2d::Ref * sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene( scene);
}


