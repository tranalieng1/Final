#ifndef __ARTHUR_1_H__
#define __ARTHUR_1_H__
#include "cocos2d.h"
#include "Player.h"
#include "Hit.h"
#include "MoonBlade.h"
class Arthur_1: public Player
{
	enum class Direction
	{
		TOP,
		LEFT,
		RIGHT,
		BOT
	};

public:
	static std::map<AnimationType, AnimationInfo>s_mapAnimations;

	Arthur_1();
	~Arthur_1();


	CREATE_FUNC(Arthur_1);

	void Attack();
	virtual bool init();
	void Jump();
	void Attack1Animation();
	void WalkAnimation();
	void StopAction();
	void PlayAnimation(AnimationType type);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) override;

	void onContactBeganWith(GameObject* obj) override;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void SetState(_State state) override;
	void update(float delta);
	/*void processInput();
	void releaseInput();*/
private:
	int _checkwalk;
	int _velocityX;
	int _velocityY;
	Direction _horizonDirection;
	Direction _verticalDirection;
	bool _right;
	bool _left;

	Hit *_hit;
	MoonBlade *_MBlade;
	void onFinishAnimation();
protected:
	float getDamage() override;

};
#endif //