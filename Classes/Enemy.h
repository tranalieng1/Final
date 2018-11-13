#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"

class Enemy : public cocos2d::Node
{

public:
	Enemy();
	~Enemy();



	//virtual void Attack();
	virtual bool init();
	//virtual void Jump();
	//virtual void Attack1Animation();
	//virtual void WalkAnimation();
	//virtual void StopAction();

	virtual void onContactBeganWith(Enemy* obj) = 0;
	virtual void onContactPostSolveWith(Enemy* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) = 0;
	virtual void onContactPreSolveWith(Enemy* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) = 0;
	virtual void onContactSeparateWith(Enemy* obj, cocos2d::PhysicsContact& contact) = 0;


	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) = 0;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) = 0;

protected:
	
	cocos2d::Sprite *_EnemySprite;
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy *_Jump;
	int _checkwalk;

	
	cocos2d::PhysicsBody *_Physicbody;

	int _Health;
	int _Strenght;
	int _Mana;
	
};
#endif //