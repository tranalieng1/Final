#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"
class Enemy : public GameObject
{

public:
	Enemy();
	~Enemy();

	static std::map<AnimationType, AnimationInfo>s_mapAnimations;

	virtual void Attack() = 0;
	virtual bool init()  override;
	virtual void Jump() = 0;
	virtual void Attack1Animation() = 0;
	virtual void WalkAnimation() = 0;
	virtual void StopAction() = 0;
	
	virtual void onContactBeganWith(GameObject* obj) = 0;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) = 0;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) = 0;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) = 0;

	virtual void SetState(_State state);

	virtual void takeDamage(float dmg) override ;
protected:
	
	cocos2d::Sprite *_EnemySprite;
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy *_Jump;
	int _checkwalk;

	
	cocos2d::PhysicsBody *_Physicbody;

	float _Health;
	float _Strenght;

	float _MaxHealth;
	_State GetState();
	
	cocos2d::ui::LoadingBar* _HealthBar;
	
	std::vector<_State> _state;
	
};
#endif //