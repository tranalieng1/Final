#ifndef __PERCIVAL_H__
#define __PERCIVAL_H__
#include "cocos2d.h"
#include "Player.h"
#include "Hit.h"
#include "MoonBlade.h"
class Percival: public Player
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

	Percival();
	~Percival();


	CREATE_FUNC(Percival);

	void Attack();
	virtual bool init();
	void Jump();

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

	virtual void takeDamage(float dmg) override;
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

	
	
	void onFinishAnimation();
protected:
	

};
#endif //