#ifndef __GAMESCENE1_H__
#define __GAMESCENE1_H__
#include"Arthur_1.h"

#include "cocos2d.h"

enum _State
{
	STATE_ATTACKING,
	STATE_JUMPING,
	STATE_STANDING,
	STATE_WALKING
};

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

private:
	cocos2d::Size visibleSize;
	cocos2d::TMXTiledMap *_tileMap;
	Arthur_1 *_Arthur;

	cocos2d::Camera *cam;
	cocos2d::Vec3 campos;
	
	_State _state;

	int _checkwalk;

	bool moveup;
	bool movedown;
	bool moveleft;
	bool moveright;
};


#endif //G__GAMESCENE1_H__

