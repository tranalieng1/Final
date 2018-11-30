#ifndef __SWORDMAN_H__
#define __SWORDMAN_H__
#include "cocos2d.h"
#include"Enemy.h"

class SwordMan : public Enemy
{
public:
	SwordMan();
	~SwordMan();
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


	virtual void takeDamage(float dmg) override;

	CREATE_FUNC(SwordMan);
private:

	

};
#endif //