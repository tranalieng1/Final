#include "GameScene_1.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Defnition.h"
#include "Arthur_1.h"
#include "Percival.h"
#include "MoonBlade.h"
#include "BirdMan.h"
#include <string>
#include "Wall.h"
#include "SKeyboard.h"
#include "UIGameScene.h"
#include "HandlePhysics.h"
#include "PoolMoonBlade.h"
#include "Secret.h"
#include "EndScene.h"
#include "AudioEngine.h"
#include "SwordMan.h"
#include "Garibaldi.h"
#include "UIPause.h"

//#define schedule_selector CC_SCHEDULE_SELECTOR
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector

GameScene_1::GameScene_1()
{
	_poolMoonBlade = new PoolMoonBlade();
	lock1 = false;
	lock2 = false;
	check1 = false;
	check2 = false;
	lockkey = false;
	_checkPause = false;
	checkenemy = 0;
}
GameScene_1::~GameScene_1()
{
	CC_SAFE_DELETE(_poolMoonBlade);
}

Scene* GameScene_1::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = GameScene_1::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());


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
	experimental::AudioEngine::stopAll();
	_musicGame = experimental::AudioEngine::play2d("Sound/nhacgame.mp3", true, 3.0f);
	
	
	
	

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist", "sprites.png");
	/////////////////////////////
	
	
	//cam->setAnchorPoint(Vec2(campos.x*POSITION_BEGIN_WIDTH, campos.y*POSITION_BEGIN_HEIGHT));
	_Arthur = Arthur_1::create();
	//_Arthur->setPosition(Vec2(6000, 100));
	_Arthur->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH,visibleSize.height*POSITION_BEGIN_HEIGHT));
	this->addChild(_Arthur, 2);
	/*_Percival = Percival::create();
	_Percival->setPosition(Vec2(4000 + 100, 100));
	this->addChild(_Percival, 2);*/
	//Map

	_tileMap = TMXTiledMap::create("Game_1_1.tmx");
	
	_tileMap->setScale(SCALE_MAP);
	addChild(_tileMap,0,99);
	float x = _tileMap->getContentSize().width;
	float y = _tileMap->getContentSize().height;
	auto ObjectWall = _tileMap->getObjectGroup("Wall");
	auto Wall = ObjectWall->getObjects();

	for (int i = 0; i < Wall.size(); i++)
	{
		auto objInfo = Wall.at(i).asValueMap();
		int type = objInfo.at("type").asInt();
		if (type == 1)
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();

			auto wall = Wall::create();
			this->addChild(wall);
			wall->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			wall->setPosition(SCALE_MAP*(x+width*0.5f), SCALE_MAP*(y+height*0.5f));

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(SCALE_MAP*width, SCALE_MAP*height), PhysicsMaterial(100.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);  
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
		
			
			tilePhysics->setCategoryBitmask(WALL_CATE);
			tilePhysics->setCollisionBitmask(WALL_COLL);
			tilePhysics->setContactTestBitmask(WALL_COLL);
			wall->setPhysicsBody(tilePhysics);

			//auto node = Node::create();
			//this->addChild(node);
			//node->setPosition(x, y);

			//PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(1.0f, 0.0f, 0.0f));
			//tilePhysics->setDynamic(false);   //static is good enough for walls
			//tilePhysics->setGravityEnable(false);
			//tilePhysics->setRotationEnable(false);
			//node->setPhysicsBody(tilePhysics);
		}
		if (type == 2)
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();
			auto pipe = Sprite::create("Pipe.png");
			this->addChild(pipe, 10);
			pipe->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			pipe->setPosition(SCALE_MAP*(x + width * 0.5f), SCALE_MAP*(y + height * 0.5f));
			pipe->setScale(SCALE_MAP);
			
		}
		if (type == 3)//them secret
		{
			int x = objInfo.at("x").asInt();
			int y = objInfo.at("y").asInt();
			int width = objInfo.at("width").asInt();
			int height = objInfo.at("height").asInt();
			auto secret = Secret::create();
			secret->setPlayer(_Arthur, _Arthur);
			this->addChild(secret,1);
			secret->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			secret->setPosition(SCALE_MAP*(x + width * 0.5f), SCALE_MAP*(y + height * 0.5f));
			//secret->setScale(SCALE_MAP);
		}
		if (type == 10)//them secret
		{
			//int x = objInfo.at("x").asInt();
			//int y = objInfo.at("y").asInt();
			//int width = objInfo.at("width").asInt();
			//int height = objInfo.at("height").asInt();

			//

			//auto secret = FanMan::create();
			//secret->enalbeAI(_Arthur);
			////FanMan->setPlayer(_Arthur, _Arthur);
			//this->addChild(secret, 1);
			//secret->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			//secret->setPosition(SCALE_MAP*(x + width * 0.5f), SCALE_MAP*(y + height * 0.5f));
			////secret->setScale(SCALE_MAP);
		}
	}
	//Physic handler
	_physichandler = new HandlePhysics();
	//UIScene
	_UIGameScene = UIGameScene::create();
	//_UIGameScene->setPosition(Vec2(visibleSize.width*0.0f,visibleSize.height*0.0f));

	this->addChild(_UIGameScene,50);
	//Set uipause
	_uiPause = UIPause::create();
	this->addChild(_uiPause, 90);
	_uiPause->setVisible(false);
	//secret
	//auto secret = Secret::create();
	//secret->setPosition(Vec2(3000, 100));
	//this->addChild(secret);
	//_Arthur
	

	

	//Percival
	/*_Percival = Percival::create();

	_Percival->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH - 50, visibleSize.height*POSITION_BEGIN_HEIGHT - 50));
	this->addChild(_Percival, 2);*/


	//FanMan
	/*_FanMan = FanMan::create();
	_FanMan->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH+200, visibleSize.height*POSITION_BEGIN_HEIGHT));
	_FanMan->enalbeAI(_Arthur);
	_FanMan->setscene(this);
	this->addChild(_FanMan,1);*/

	_Boss = Garibaldi::create();
	_Boss->setPosition(Vec2(7400, 100));
	//sw->enalbeAI(_Arthur);
	_Boss->setScene(this);
	this->addChild(_Boss, 1);

	//_BirdMan
	/*_BirdMan = BirdMan::create();
	_BirdMan->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH - 100, visibleSize.height*POSITION_BEGIN_HEIGHT));
	_BirdMan->enalbeAI(_Arthur);
	_BirdMan->setscene(this);
	this->addChild(_BirdMan, 1);*/
	auto sw = SwordMan::create();
	sw->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH - 100, visibleSize.height*POSITION_BEGIN_HEIGHT));
	sw->enalbeAI(_Arthur);
	sw->setscene(this);
	this->addChild(sw, 1); 
	// dunglq3
	// IMPORTANT: The scheduleUpdate must be called right before this->addChild(SKeyboard::get()),
	// or the SKeyboard::getEvents always return a vector of nothing because of SKeyboard::update
	scheduleUpdate();
	this->addChild(SKeyboard::get());
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene_1::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene_1::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	// set listener vat ly
	auto ePhysics = EventListenerPhysicsContact::create();
	ePhysics->onContactBegin = CC_CALLBACK_1(HandlePhysics::onContactBegin, _physichandler);
	ePhysics->onContactPostSolve = CC_CALLBACK_2(HandlePhysics::onContactPostSolve, _physichandler);
	ePhysics->onContactPreSolve = CC_CALLBACK_2(HandlePhysics::onContactPreSolve, _physichandler);
	ePhysics->onContactSeparate = CC_CALLBACK_1(HandlePhysics::onContactSeperated, _physichandler);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ePhysics, this);


	

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
	if (kc == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
	
		if (Director::getInstance()->isPaused() == false)
		{
			Director::getInstance()->pause();
			experimental::AudioEngine::pause(_musicGame);
			lockkey = true;
			_uiPause->setVisible(true);

		}
		else 
		{
			Director::getInstance()->resume();
			experimental::AudioEngine::resume(_musicGame);
			lockkey = false;
			_uiPause->setVisible(false);
		}
		
	}
	else if (kc == EventKeyboard::KeyCode::KEY_F2)
	{
		Director::getInstance()->resume();
		//this->resumeRecursiveAllChildren(this);
		lockkey = false;
	}
	if (lockkey == false)
	{
		/*_Percival->onKeyPressed(kc, event);*/
		_Arthur->onKeyPressed(kc, event);

		if (kc == EventKeyboard::KeyCode::KEY_J)
		{
			/*if (_Arthur->getScaleX() > 0)
			{
				_MBlade->setScaleX(2.7f);
			}
			else
			{
				_MBlade->setScaleX(-2.7f);
			}*/
			/*_MBlade->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY()));
			_MBlade->flySkill();*/
			auto mb = _poolMoonBlade->createMB();

			if (mb)
			{

				if (_Arthur->addMana(mb->getMana()))
				{
					if (_Arthur->getScaleX() > 0)
					{
						mb->setScaleX(2.7f);
					}
					else
					{
						mb->setScaleX(-2.7f);
					}
					this->addChild(mb);
					mb->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY()));
					mb->flySkill();
				}
			}

			/*_FlameSkill->setPosition(_Arthur->getPosition());
			_FlameSkill->active();*/

			/*if (_Percival->getScaleX() > 0)
			{
				_MBlade2->setScaleX(2.7f);
			}
			else
			{
				_MBlade2->setScaleX(-2.7f);
			}
			_MBlade2->setPosition(Vec2(_Percival->getPositionX(), _Percival->getPositionY()));
			_MBlade2->flySkill();*/
		}
	}
	else if (kc == EventKeyboard::KeyCode::KEY_9)
	{
		this->goToEndScene();
	}
	




}

void GameScene_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	_Arthur->onKeyReleased(kc, event);
	/*_Percival->onKeyReleased(kc, event);*/

}

void GameScene_1::update(float dt)
{
	cam = Camera::getDefaultCamera();

	campos = cam->getPosition3D();
	lockcamera();
	if (lock1 == false&& lock2 == false)
	{
		if (_Arthur->getPositionX() <= visibleSize.width / 2)//lock ben trai
		{
			campos.x = visibleSize.width / 2;
		}
		else if (_Arthur->getPositionX() >= MAP_WIDTH - visibleSize.width / 2 - 2 * _Arthur->getContentSize().width)//lock ben phai
		{
			campos.x = MAP_WIDTH - visibleSize.width / 2 - 2 * _Arthur->getContentSize().width;
		}
	
		else // lock theo nhan vat
			campos.x = _Arthur->getPositionX();
	}
	else
	{
		//campos.x = 2000;
	}
	campos.y = this->getContentSize().height/2;
	cam->setPosition3D(campos);
	lockcamera();
	//_UIGameScene->setPosition(Vec2(visibleSize.width*0.0f, visibleSize.height*0.0f));
	////Set UI Gamescene
	if (_Arthur->getPositionX()  <= campos.x-400+ _Arthur->getContentSize().width)
	{
		_Arthur->setPositionX(campos.x-400+_Arthur->getContentSize().width);
	}
	else if (_Arthur->getPositionX() >= campos.x + 400 - _Arthur->getContentSize().width)
	{
		_Arthur->setPositionX(campos.x + 400 - _Arthur->getContentSize().width);
	}
	
	_UIGameScene->setPosition(Vec2(campos.x-visibleSize.width/2,0));
	_uiPause->setPosition(Vec2(campos.x - visibleSize.width / 2, 0));
	_UIGameScene->updatePlayer(_Arthur);
	if (checkenemy == 4)
	{
		lock1 = false;
	}
	
}

void GameScene_1::goToEndScene()
{
	auto scene = EndScene::createScene();
	Director::getInstance()->replaceScene(/*TransitionFade::create(1.5, */scene);
}

void GameScene_1::goToEndScene2(float delta)
{
	auto scene = EndScene::createScene();
	Director::getInstance()->replaceScene(/*TransitionFade::create(1.5, */scene);
}

void GameScene_1::SetPhysicsWorld(cocos2d::PhysicsWorld * world)
{
	sceneWorld = world;
}

void GameScene_1::lockcamera()
{
	if (campos.x > 2000 && check1 == false)
	{

		//campos.x = 2000;
		//lock1 = true;
		//check1 = true;
		//auto ObjectEnemy = _tileMap->getObjectGroup("Enemy");
		//auto Wall = ObjectEnemy->getObjects();
		//for (int i = 0; i < Wall.size(); i++)
		//{
		//	auto objInfo = Wall.at(i).asValueMap();
		//	int type = objInfo.at("type").asInt();
		//	if (type == 1)
		//	{
		//		int x = objInfo.at("x").asInt();
		//		int y = objInfo.at("y").asInt();
		//		int width = objInfo.at("width").asInt();
		//		int height = objInfo.at("height").asInt();

		//	

		//		auto secret = FanMan::create();
		//		secret->setscene(this);
		//		secret->enalbeAI(_Arthur);
		//		//FanMan->setPlayer(_Arthur, _Arthur);
		//		this->addChild(secret, 1);
		//		secret->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		//		secret->setPosition(SCALE_MAP*(x + width * 0.5f), SCALE_MAP*(y + height * 0.5f));
		//		//secret->setScale(SCALE_MAP);
		//	}
		//	else if (type == 2)
		//	{
		//		int x = objInfo.at("x").asInt();
		//		int y = objInfo.at("y").asInt();
		//		int width = objInfo.at("width").asInt();
		//		int height = objInfo.at("height").asInt();



		//		auto secret = SwordMan::create();
		//		secret->setscene(this);
		//		secret->enalbeAI(_Arthur);
		//		//FanMan->setPlayer(_Arthur, _Arthur);
		//		this->addChild(secret, 1);
		//		secret->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		//		secret->setPosition(SCALE_MAP*(x + width * 0.5f), SCALE_MAP*(y + height * 0.5f));
		//		//secret->setScale(SCALE_MAP);
		//	}
		//	else if (type == 3)
		//	{
		//		int x = objInfo.at("x").asInt();
		//		int y = objInfo.at("y").asInt();
		//		int width = objInfo.at("width").asInt();
		//		int height = objInfo.at("height").asInt();



		//		auto secret = BirdMan::create();
		//		secret->setscene(this);
		//		secret->enalbeAI(_Arthur);
		//		//FanMan->setPlayer(_Arthur, _Arthur);
		//		this->addChild(secret, 1);
		//		secret->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		//		secret->setPosition(SCALE_MAP*(x + width * 0.5f), SCALE_MAP*(y + height * 0.5f));
		//	}


		//}
	}
	else if (campos.x > 7000 && check2 == false)
	{
		/*_Boss->enalbeAI(_Arthur);
		campos.x = 7000;
		lock2 = true;
		check2 = true;*/
	}
	
}

void GameScene_1::setlockey()
{
	lockkey = true;
}

void GameScene_1::dieenemy()
{
	/*this->checkenemy =0;
	this->checkenemy;*/
	this->checkenemy++;
}

bool GameScene_1::CheckJump(cocos2d::Node * v1, cocos2d::Node * v2)
{
	if ((v1->getPositionX() - v2->getPositionX() < 0.1 && v1->getPositionX() - v2->getPositionX() > -0.001) &&
		(v1->getPositionY() - v2->getPositionY() < 0.1 && v1->getPositionY() - v2->getPositionY() > -0.001))
		return true;
	else
		return false;
}
void GameScene_1::pauseRecursiveAllChildren(Node *pNode)
{
	pNode->pause();
	for (const auto &child : pNode->getChildren())
	{
		this->pauseRecursiveAllChildren(child);
	}

	
}
void GameScene_1::resumeRecursiveAllChildren(Node *pNode)
{
	pNode->resume();
	for (const auto &child : pNode->getChildren())
	{
		this->resumeRecursiveAllChildren(child);
	}
}

