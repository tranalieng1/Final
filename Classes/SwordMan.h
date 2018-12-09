#ifndef __SWORDMAN_H__
#define __SWORDMAN_H__
#include "cocos2d.h"
#include"Enemy.h"

class SwordMan : public Enemy
{
	
public:
	SwordMan();
	~SwordMan();

	virtual bool init() override;
	void Jump() override;
	virtual void Attack1Animation() override;
	virtual void WalkAnimation() override;
	void StopAction() override;

	void onContactBeganWith(GameObject* obj) override ;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	void PlayAnimation(AnimationType type);
	void SetState(_State state) override;
	virtual void takeDamage(float dmg) override;
	void onFinishAnimation();
	static std::map<AnimationType, AnimationInfo> s_mapAnimations;
	virtual void scheduleUpdateAI(float delta) override;


	CREATE_FUNC(SwordMan);
private:
	void chasePlayer();

	

};
#endif //