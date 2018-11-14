#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include "GameObject.h"
enum _State
{
	STATE_ATTACKING,
	STATE_JUMPING,
	STATE_STANDING,
	STATE_WALKING
};
class Player : public GameObject
{

public:
	Player();
	~Player();



	//virtual void Attack();
	virtual bool init() override;
	//virtual void Jump();
	//virtual void Attack1Animation();
	//virtual void WalkAnimation();
	//virtual void StopAction();
	
	virtual void onContactBeganWith(GameObject* obj) = 0;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) = 0;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) = 0;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) = 0;


	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)  =0;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event) =0;
	
protected:
	_State _state;
	cocos2d::Sprite* _PlayerSprite;
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy* _Jump;
	int _checkwalk;

	bool moveup;
	bool movedown;
	bool moveleft;
	bool moveright;
	cocos2d::PhysicsBody *_Physicbody;

	int _Health;
	int _Strenght;
	int _Mana;

	_State GetState();
	void SetState(_State state);
};
#endif //