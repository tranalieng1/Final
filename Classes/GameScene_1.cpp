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
//#define schedule_selector CC_SCHEDULE_SELECTOR
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector

GameScene_1::GameScene_1()
{
	_poolMoonBlade = new PoolMoonBlade();
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

	
	
	
	

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist", "sprites.png");
	/////////////////////////////
	
	
	//cam->setAnchorPoint(Vec2(campos.x*POSITION_BEGIN_WIDTH, campos.y*POSITION_BEGIN_HEIGHT));
	_Arthur = Arthur_1::create();
	_Arthur->setPosition(Vec2(4000, 100));
	this->addChild(_Arthur, 2);
	//Map

	auto _tileMap = TMXTiledMap::create("Game_1_1.tmx");
	
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
	}
	//Physic handler
	_physichandler = new HandlePhysics();
	//UIScene
	_UIGameScene = UIGameScene::create();
	//_UIGameScene->setPosition(Vec2(visibleSize.width*0.0f,visibleSize.height*0.0f));

	this->addChild(_UIGameScene,99);

	//secret
	//auto secret = Secret::create();
	//secret->setPosition(Vec2(3000, 100));
	//this->addChild(secret);
	//_Arthur
	
	//_Arthur->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH,visibleSize.height*POSITION_BEGIN_HEIGHT));
	

	//Percival
	/*_Percival = Percival::create();

	_Percival->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH - 50, visibleSize.height*POSITION_BEGIN_HEIGHT - 50));
	this->addChild(_Percival, 2);*/


	//FanMan
	_FanMan = FanMan::create();
	_FanMan->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH+200, visibleSize.height*POSITION_BEGIN_HEIGHT));
	_FanMan->enalbeAI(_Arthur);
	this->addChild(_FanMan,1);



	//_BirdMan
	/*_BirdMan = BirdMan::create();
	_BirdMan->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH - 100, visibleSize.height*POSITION_BEGIN_HEIGHT));
	_BirdMan->enalbeAI(_Arthur);
	this->addChild(_BirdMan, 1);
*/

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


	//Set skill
	_MBlade = MoonBlade::create();
	_MBlade->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY()));
	this->addChild(_MBlade);
	_FlameSkill = Flame::create();
	_MBlade->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY()));
	this->addChild(_FlameSkill);
	/*_MBlade2 = MoonBlade::create();
	_MBlade2->setPosition(Vec2(_Percival->getPositionX(), _Percival->getPositionY()));
	this->addChild(_MBlade2);
*/
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
	/*_Percival->onKeyPressed(kc, event);*/
	_Arthur->onKeyPressed(kc, event);
	
	if (kc == EventKeyboard::KeyCode::KEY_J)
	{
		if (_Arthur->getScaleX() > 0)
		{
			_MBlade->setScaleX(2.7f);
		}
		else
		{
			_MBlade->setScaleX(-2.7f);
		}
		/*_MBlade->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY()));
		_MBlade->flySkill();*/
		auto mb = _poolMoonBlade->createMB();
		if (mb)
		{
			this->addChild(mb);
			mb->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY()));
			mb->flySkill();
		}
		_FlameSkill->setPosition(_Arthur->getPosition());
		_FlameSkill->active();

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

void GameScene_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	_Arthur->onKeyReleased(kc, event);
	/*_Percival->onKeyReleased(kc, event);*/

}

void GameScene_1::update(float dt)
{
	cam = Camera::getDefaultCamera();

	campos = cam->getPosition3D();
	if (_Arthur->getPositionX() <= visibleSize.width / 2)//lock ben trai
		
		campos.x = visibleSize.width / 2;
	else if (_Arthur->getPositionX() >= MAP_WIDTH - visibleSize.width / 2 - 2*_Arthur->getContentSize().width)//lock ben phai
	{
		campos.x = MAP_WIDTH - visibleSize.width / 2 - 2*_Arthur->getContentSize().width;
	}
	else // lock theo nhan vat
		campos.x = _Arthur->getPositionX();
	campos.y = this->getContentSize().height/2;
	cam->setPosition3D(campos);
	//_UIGameScene->setPosition(Vec2(visibleSize.width*0.0f, visibleSize.height*0.0f));
	////Set UI Gamescene
	if (_Arthur->getPositionX()  <= campos.x-400+ _Arthur->getContentSize().width)
	{
		_Arthur->setPositionX(campos.x-400+_Arthur->getContentSize().width);
	}
	/*if (_Arthur->getPositionY() >= 220)
	{
		_Arthur->setPositionY(220);
			
	}*/
	/*if (_Arthur->getPositionX() >= campos.x - 400 + _Arthur->getContentSize().width)
	{
		_Arthur->setPositionX(campos.x - 400 + _Arthur->getContentSize().width);
	}*/
	_UIGameScene->setPosition(Vec2(campos.x-visibleSize.width/2,0));
	//_UIGameScene->setScore(_Arthur->getScore());
	_UIGameScene->updatePlayer(_Arthur);
	//if (_Arthur->GetState() == STATE_STANDING)
	//{
	//	if (moveright == true)
	//	{
	//		_Arthur->setScaleX(2.0f);
	//		_nodePosPlayer->setPosition(Vec2(_nodePosPlayer->getPositionX() + visibleSize.width*SPEED_MOVE_HORIZONTAL, _nodePosPlayer->getPositionY()));
	//		_Arthur->setPosition(Vec2(_Arthur->getPositionX() + visibleSize.width*SPEED_MOVE_HORIZONTAL, _Arthur->getPositionY()));
	//		
	//	}
	//	if (moveleft == true)
	//	{
	//		_Arthur->setScaleX(-2.0f);
	//		if (_Arthur->getPositionX() - _Arthur->getContentSize().width / 2 > 0)
	//		{
	//			_nodePosPlayer->setPosition(Vec2(_nodePosPlayer->getPositionX() - visibleSize.width*SPEED_MOVE_HORIZONTAL, _nodePosPlayer->getPositionY()));

	//			_Arthur->setPosition(Vec2(_Arthur->getPositionX() - visibleSize.width*SPEED_MOVE_HORIZONTAL, _Arthur->getPositionY()));
	//		}
	//			
	//		else
	//		{
	//			_nodePosPlayer->setPosition(Vec2(0 + _Arthur->getContentSize().width / 2, _nodePosPlayer->getPositionY()));
	//			_Arthur->setPosition(Vec2(0 + _Arthur->getContentSize().width / 2, _Arthur->getPositionY()));
	//			
	//		}

	//	}
	//	if (moveup == true)
	//	{
	//		_nodePosPlayer->setPosition(Vec2(_nodePosPlayer->getPositionX(), _nodePosPlayer->getPositionY() + visibleSize.height*SPEED_MOVE_VERTICAL));
	//		_Arthur->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY() + visibleSize.height*SPEED_MOVE_VERTICAL));
	//		
	//	}
	//	if (movedown == true)
	//	{
	//		if (_Arthur->getPositionY() > 0)
	//		{
	//			_nodePosPlayer->setPosition(Vec2(_nodePosPlayer->getPositionX(), _nodePosPlayer->getPositionY() - visibleSize.height*SPEED_MOVE_VERTICAL));
	//			_Arthur->setPosition(Vec2(_Arthur->getPositionX(), _Arthur->getPositionY() - visibleSize.height*SPEED_MOVE_VERTICAL));
	//			
	//		}
	//		else
	//		{
	//			_nodePosPlayer->setPosition(Vec2(_nodePosPlayer->getPositionX(), 0));
	//			_Arthur->setPosition(Vec2(_Arthur->getPositionX(), 0));
	//			
	//		}
	//	}
	//}
	/////--------------------------
	/*if (_Arthur->getPosition() == _nodePosPlayer->getPosition())
	{
		_Arthur->SetState(STATE_STANDING);
	}
	else
	{
		_Arthur->SetState(STATE_JUMPING);
	}*/
	
	
	
	//
	//_nodePosPlayer->setPosition(_Arthur->getPosition());
	//if (CheckJump(_Arthur,_nodePosPlayer)==true)
	//{
	//	cocos2d::log("1");
	//}
	//else
	//{
	//	cocos2d::log("0");
	//}
	//cocos2d::log("%d  -   %d",_Arthur->getPositionX(),_nodePosPlayer->getPositionX());
	/*cocos2d::log("%f-%f //   %f-%f",(float)_Arthur->getPositionX(), (float)_Arthur->getPositionY()
									,(float)_nodePosPlayer->getPositionX(), (float)_nodePosPlayer->getPositionY());*/
	//cocos2d::log("%d ", _state);

}

void GameScene_1::SetPhysicsWorld(cocos2d::PhysicsWorld * world)
{
	sceneWorld = world;
}

bool GameScene_1::CheckJump(cocos2d::Node * v1, cocos2d::Node * v2)
{
	if ((v1->getPositionX() - v2->getPositionX() < 0.1 && v1->getPositionX() - v2->getPositionX() > -0.001) &&
		(v1->getPositionY() - v2->getPositionY() < 0.1 && v1->getPositionY() - v2->getPositionY() > -0.001))
		return true;
	else
		return false;
}

