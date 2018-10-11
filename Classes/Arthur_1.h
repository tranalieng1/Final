#ifndef __ARTHUR_1_H__
#define __ARTHUR_1_H__
#include "cocos2d.h"

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
	CREATE_FUNC(Arthur_1);
private:
	
	cocos2d::Sprite* _ArthurSprite;
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy* _Jump;

};
#endif //