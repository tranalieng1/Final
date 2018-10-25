#ifndef __FANMAN_H__
#define __FANMAN_H__
#include "cocos2d.h"

class FanMan : public cocos2d::Node
{
public:
	FanMan();
	~FanMan();
	void Attack();
	virtual bool init();
	void Jump();
	void Attack1Animation();
	void WalkAnimation();
	void StopAction();
	CREATE_FUNC(FanMan);
private:

	cocos2d::Sprite* _FanManSprite;
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy* _Jump;

};
#endif //