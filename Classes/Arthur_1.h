#ifndef __ARTHUR_1_H__
#define __ARTHUR_1_H__
#include "cocos2d.h"
#include "Player.h"

class Arthur_1: public Player
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
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event);
	CREATE_FUNC(Arthur_1);
private:
	

};
#endif //