#include "GameScene_1.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Defnition.h"
#include "Arthur_1.h"
//#define schedule_selector CC_SCHEDULE_SELECTOR
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector



Scene* GameScene_1::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene_1::create();

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
bool GameScene_1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_state = STATE_STANDING;
	_checkwalk = 0;

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist", "sprites.png");
	/////////////////////////////
	
	
	//cam->setAnchorPoint(Vec2(campos.x*POSITION_BEGIN_WIDTH, campos.y*POSITION_BEGIN_HEIGHT));

	
	auto _tileMap = TMXTiledMap::create("Game_1_1.tmx");
	_tileMap->setScale(3.0f);
	addChild(_tileMap,0,99);
	
	_Arthur = Arthur_1::create();
	_Arthur->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_Arthur->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH,visibleSize.height*POSITION_BEGIN_HEIGHT));
	
	this->addChild(_Arthur);
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene_1::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene_1::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();

	/*listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			
	
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:

			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:

			break;
		}
	};*/
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	//auto _ArthurSprite = Sprite::createWithSpriteFrameName("Arthur_0_stand_1.png");
	//_ArthurSprite->setPosition(visibleSize*0.5);
	//this->addChild(_ArthurSprite,2);
	// add a "close" icon to exit the progress. it's an autorelease object

	return true;


}





void GameScene_1::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	
}
void GameScene_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		
		//_Arthur->setScaleX(2.0f);
		if(_checkwalk==0)
		_Arthur->WalkAnimation();
		moveright = true;
		
		_checkwalk++;
	}
	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		//_Arthur->setScaleX(-2.0f);
		
		moveleft = true;
		if (_checkwalk == 0)
		_Arthur->WalkAnimation();
		_checkwalk++;
	}
	if (kc == EventKeyboard::KeyCode::KEY_S)
	{
		movedown = true;
		if (_checkwalk == 0)
		_Arthur->WalkAnimation();
		_checkwalk++;
	}
	if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		moveup = true;
		if (_checkwalk == 0)
		_Arthur->WalkAnimation();
		_checkwalk++;
	}
	if (kc == EventKeyboard::KeyCode::KEY_K)
	{
		
		_Arthur->Attack1Animation();
		_state = STATE_ATTACKING;
		//_Arthur->StopAction();
	}
	if (kc ==  EventKeyboard::KeyCode::KEY_L)
	{
		_Arthur->Jump();
	}
}

void GameScene_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		
		moveright = false;
		_checkwalk--;
		if(_checkwalk==0)
		_Arthur->StopAction();
		
	}
	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		
		moveleft = false;
		_checkwalk--;
		if (_checkwalk == 0)
		_Arthur->StopAction();
	}
	if (kc == EventKeyboard::KeyCode::KEY_S)
	{
		movedown = false;
		_checkwalk--;
		if (_checkwalk == 0)
		_Arthur->StopAction();
	}
	if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		moveup = false;
		_checkwalk--;
		if (_checkwalk == 0)
		_Arthur->StopAction();
	}
	if (kc == EventKeyboard::KeyCode::KEY_K)
	{
		_state = STATE_STANDING;
	}
}

void GameScene_1::update(float dt)
{
	cam = Camera::getDefaultCamera();

	campos = cam->getPosition3D();
	if (_Arthur->getPositionX() > visibleSize.width / 2)
		campos.x = _Arthur->getPositionX();
	else
		campos.x = visibleSize.width / 2;
	campos.y = this->getContentSize().height/2;
	cam->setPosition3D(campos);
	if (_state == STATE_STANDING)
	{
		if (moveright == true)
		{
			_Arthur->setScaleX(2.0f);
			_Arthur->setPosition(Vec2(_Arthur->getPositionX() + visibleSize.width*SPEED_MOVE_HORIZONTAL, _Arthur->getPositionY()));
		}
		if (moveleft == true)
		{
			_Arthur->setScaleX(-2.0f);
			if (_Arthur->getPositionX() - _Arthur->getContentSize().width / 2 > 0)
			{
				_Arthur->setPosition(Vec2(_Arthur->getPositionX() - visibleSize.width*SPEED_MOVE_HORIZONTAL, _Arthur->getPositionY()));
			}
			else
				_Arthur->setPosition(Vec2(0 + _Arthur->getContentSize().width / 2, _Arthur->getPositionY()));

		}
		if (moveup == true)
		{
			_Arthur->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY() + visibleSize.height*SPEED_MOVE_VERTICAL));
		}
		if (movedown == true)
		{
			if (_Arthur->getPositionY() > 0)
				_Arthur->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY() - visibleSize.height*SPEED_MOVE_VERTICAL));
			else
				_Arthur->setPosition(Vec2(_Arthur->getPositionX(), 0));
		}
	}
	
}

