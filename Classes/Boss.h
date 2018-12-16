#ifndef __BOSS_H__
#define __BOSS_H__
#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"
#include "ui/CocosGUI.h"
class GameScene_1;
class Boss : public GameObject
{

public:
	Boss();
	~Boss();



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

	virtual void takeDamage(float dmg,int temp) override;

	virtual void SetState(_State state);
	void setDeathLess(bool temp);
	virtual void enalbeAI(Player* player);
	virtual void scheduleUpdateAI(float delta);
	virtual void update(float delta);
	void setScene(GameScene_1 *temp);

protected:

	cocos2d::Sprite *_BossSprite;
	Player* _Arthurptr;
	Player* _Percialptr;
	
	cocos2d::Action *_WalkAction;
	cocos2d::JumpBy *_Jump;
	int _checkwalk;

	float _timeUpdateAI;
	cocos2d::PhysicsBody *_Physicbody;

	float _Health;
	float _Strenght;

	float _MaxHealth;
	cocos2d::ui::LoadingBar* _HealthBar;
	float _jumph;
	std::vector<_State> _state;
	float _score;
	GameScene_1 *scene;
};
#endif //
