#include "GameScene_1.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Defnition.h"
#include "Arthur_1.h"
#include "MoonBlade.h"
#include <string>
#include "Wall.h"
//#define schedule_selector CC_SCHEDULE_SELECTOR
USING_NS_CC;
using namespace cocos2d;
//#define schedule_selector



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

	//Map

	auto _tileMap = TMXTiledMap::create("Game_1_1.tmx");
	
	_tileMap->setScale(3.0f);
	addChild(_tileMap,0,99);
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
			wall->setPosition(x, y);

			PhysicsBody* tilePhysics = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(100.0f, 0.0f, 0.0f));
			tilePhysics->setDynamic(false);  
			tilePhysics->setGravityEnable(false);
			tilePhysics->setRotationEnable(false);
			tilePhysics->setCategoryBitmask(WALL_CATEGORY_BITMASK);
			tilePhysics->setCollisionBitmask(WALL_COLLISION_AND_CONTACT_TEST_BIT_MASK);
			tilePhysics->setContactTestBitmask(WALL_COLLISION_AND_CONTACT_TEST_BIT_MASK);
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
	}

	//_Arthur
	_Arthur = Arthur_1::create();

	_Arthur->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH,visibleSize.height*POSITION_BEGIN_HEIGHT));
	this->addChild(_Arthur,2);
	//FanMan
	_FanMan = FanMan::create();

	_FanMan->setPosition(Vec2(visibleSize.width*POSITION_BEGIN_WIDTH+200, visibleSize.height*POSITION_BEGIN_HEIGHT));
	this->addChild(_FanMan,1);
	//_nodeposplayer

	_nodePosPlayer = Sprite::create("Skill_MoonBlade.png");
	_nodePosPlayer->setPosition(_Arthur->getPosition());
	_nodePosPlayer->setContentSize(Size(30,40));
	
	addChild(_nodePosPlayer,22);
	// create skill moonblade
	moonblade = MoonBlade::create();
	
	moonblade->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	this->addChild(moonblade);
	moonblade->setVisible(false);



	
	
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
	_Arthur->onKeyPressed(kc, event);
	//
	//if (_Arthur->GetState() == STATE_STANDING)
	//{
	//	if (kc == EventKeyboard::KeyCode::KEY_D)
	//	{

	//		//_Arthur->setScaleX(2.0f);
	//		if (_checkwalk == 0)
	//			_Arthur->WalkAnimation();
	//		moveright = true;

	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_A)
	//	{
	//		//_Arthur->setScaleX(-2.0f);

	//		moveleft = true;
	//		if (_checkwalk == 0)
	//			_Arthur->WalkAnimation();
	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_S)
	//	{
	//		movedown = true;
	//		if (_checkwalk == 0)
	//			_Arthur->WalkAnimation();
	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_W)
	//	{
	//		moveup = true;
	//		if (_checkwalk == 0)
	//			_Arthur->WalkAnimation();
	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_L)
	//	{
	//		if (CheckJump(_Arthur, _nodePosPlayer) == true)
	//		{
	//			_Arthur->Jump();
	//			_Arthur->SetState(STATE_JUMPING);
	//		}


	//	}
	//}
	//	if (kc == EventKeyboard::KeyCode::KEY_K)
	//	{
	//		_Arthur->Attack1Animation();
	//		_Arthur->SetState(STATE_ATTACKING);
	//		//_Arthur->StopAction();
	//	}
	//
	//	if (kc == EventKeyboard::KeyCode::KEY_J)
	//	{
	//		moonblade->setPosition(Vec2(_Arthur->getPositionX() + _Arthur->getContentSize().width / 2 + 20, _Arthur->getPositionY() + +10));
	//		moonblade->setVisible(true);
	//		moonblade->flySkill();
	//	}
	
}

void GameScene_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	_Arthur->onKeyReleased(kc, event);
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
	cocos2d::log("%f-%f //   %f-%f",(float)_Arthur->getPositionX(), (float)_Arthur->getPositionY()
									,(float)_nodePosPlayer->getPositionX(), (float)_nodePosPlayer->getPositionY());
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

