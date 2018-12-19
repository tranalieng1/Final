#ifndef __GAMESCENE1_H__
#define __GAMESCENE1_H__
#include"Arthur_1.h"
#include "MoonBlade.h"
#include "cocos2d.h"
#include "MoonBlade.h"
#include "FanMan.h"
#include "Player.h"
#include "UIGameScene.h"
#include "score.h"
#include "Flame.h"

class UIGameScene;
class HandlePhysics;
class PoolMoonBlade;
class Garibaldi;
class GameScene_1 : public cocos2d::Layer
{
public:
	int			_musicGame;
	GameScene_1();
	~GameScene_1();
	static cocos2d::Scene *createScene();
	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event* event);
	CREATE_FUNC(GameScene_1);
	void update(float dt);
	void goToEndScene();
	void goToEndScene2(float delta);
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world);
	void lockcamera();
	void setlockey();
	void dieenemy();
	void pauseRecursiveAllChildren(Node *pNode);
	void resumeRecursiveAllChildren(Node *pNode);
private:
	cocos2d::Size visibleSize;
	cocos2d::TMXTiledMap *_tileMap;
	Player *_Arthur;
	Player *_Percival;
	Enemy *_FanMan;
	Enemy *_BirdMan;
	Enemy *_BusterS;
	Enemy *_TallMan;
	Enemy *_SwordMan;
	cocos2d::PhysicsWorld *sceneWorld;

	
	cocos2d::Camera *cam;
	cocos2d::Vec3 campos;
	
	UIGameScene *_UIGameScene;
	HandlePhysics* _physichandler;

	/*MoonBlade *_MBlade;
	MoonBlade *_MBlade2;*/

	Flame *_FlameSkill;

	PoolMoonBlade *_poolMoonBlade;

	bool CheckJump(cocos2d::Node *v1,cocos2d::Node *v2);

	bool lock1;
	bool lock2;

	bool check1;
	bool check2;
	bool lockkey;
	Garibaldi *_Boss;
	int checkenemy;

	bool _checkPause;
};


#endif //G__GAMESCENE1_H__

