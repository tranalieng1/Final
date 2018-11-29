#ifndef __FANMAN_H__
#define __FANMAN_H__
#include "cocos2d.h"
#include"Enemy.h"

class FanMan : public Enemy
{
	
public:
	FanMan();
	~FanMan();
	void Attack() override;
	virtual bool init() override;
	void Jump() override;
	void Attack1Animation() override;
	void WalkAnimation() override;
	void StopAction() override;

	void onContactBeganWith(GameObject* obj) override ;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	void PlayAnimation(AnimationType type);
	void SetState(_State state) override;
	virtual void takeDamage() override;
	void onFinishAnimation();

	CREATE_FUNC(FanMan);
private:

	

};
#endif //