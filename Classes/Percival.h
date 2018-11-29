#ifndef __PERCIVAL_H__
#define __PERCIVAL_H__
#include "cocos2d.h"
#include "Player.h"

class Percival : public Player
{

public:
	Percival();
	~Percival();



	void Attack();
	virtual bool init();
	void Jump();
	void Attack1Animation();
	void WalkAnimation();
	void StopAction();
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) override;
	void onContactBeganWith(GameObject* obj) override;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void takeDamage() override;
	CREATE_FUNC(Percival);
private:


};
#endif //