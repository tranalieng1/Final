#ifndef __GARIBALDI_H__
#define __GARIBALDI_H__
#include "cocos2d.h"
#include"Boss.h"
#include "GameScene_1.h"
//class GameScene_1;
class Garibaldi : public Boss
{
public:
	Garibaldi();
	~Garibaldi();
	void Attack() override;
	virtual bool init() override;
	void Jump() override;
	void Attack1Animation() override;
	void WalkAnimation() override;
	void StopAction() override;

	void onContactBeganWith(GameObject* obj) override;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;

	virtual void takeDamage(float dmg, int temp) override;
	void PlayAnimation(AnimationType type);
	void SetState(_State state) override;
	void onFinishAnimation();
	
	static std::map<AnimationType, AnimationInfo> s_mapAnimations;
	virtual void scheduleUpdateAI(float delta) override;

	void update(float delta);
	CREATE_FUNC(Garibaldi);
private:

	void chasePlayer();
	float attackdelay;

};
#endif //