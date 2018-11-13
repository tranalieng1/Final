#ifndef __GAMESCENE1_H__
#define __GAMESCENE1_H__
#include"Arthur_1.h"
#include "MoonBlade.h"
#include "cocos2d.h"
#include "MoonBlade.h"
#include "FanMan.h"


class GameScene_1 : public cocos2d::Layer
{
public:


	static cocos2d::Scene *createScene();
	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event* event);
	CREATE_FUNC(GameScene_1);
	void update(float dt);
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world);
	

private:
	cocos2d::Size visibleSize;
	cocos2d::TMXTiledMap *_tileMap;
	Arthur_1 *_Arthur;
	FanMan *_FanMan;
	cocos2d::PhysicsWorld *sceneWorld;
	MoonBlade *moonblade;

	cocos2d::Camera *cam;
	cocos2d::Vec3 campos;
	

	


	cocos2d::Node *_nodePosPlayer;
	bool CheckJump(cocos2d::Node *v1,cocos2d::Node *v2);
};


#endif //G__GAMESCENE1_H__

