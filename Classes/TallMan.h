#ifndef __TALLMAN_H__
#define __TALLMAN_H__
#include "cocos2d.h"
#include"Enemy.h"

class TallMan : public Enemy
{
public:
	TallMan();
	~TallMan();

	virtual bool init() override;
	void Jump() override;
	void Attack1Animation() override;
	void WalkAnimation() override;
	void StopAction() override;

	void onContactBeganWith(GameObject* obj) override ;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;

	static std::map<AnimationType, AnimationInfo>s_mapAnimations;
	virtual void takeDamage(float dmg) override;

	CREATE_FUNC(TallMan);
private:

	

};
#endif //