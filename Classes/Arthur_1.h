#ifndef __ARTHUR_1_H__
#define __ARTHUR_1_H__
#include "cocos2d.h"
enum _State
{
	STATE_ATTACKING,
	STATE_JUMPING,
	STATE_STANDING,
	STATE_WALKING
};
class Arthur_1: public cocos2d::Node
{

public:
	Arthur_1();
	~Arthur_1();



	void Attack();
	virtual bool init();
	void Jump();
	void Attack1Animation();
	void WalkAnimation();
	void StopAction();
	_State GetState();
	void SetState(_State state);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event);
	CREATE_FUNC(Arthur_1);
private:
	_State _state;
	cocos2d::Sprite* _ArthurSprite;
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy* _Jump;
	int _checkwalk;

	bool moveup;
	bool movedown;
	bool moveleft;
	bool moveright;

};
#endif //