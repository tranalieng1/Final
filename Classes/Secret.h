#ifndef __SECRET_H__
#define __SECRET_H__
#include"GameObject.h"
#include"cocos2d.h"
#include "Player.h"

class Secret : public GameObject
{
public:
	Secret();
	~Secret();
	virtual void takeDamage(float dmg, int temp) override;
	virtual bool init()override;
	void onContactBeganWith(GameObject* obj) override;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	void setPlayer(Player* temp1, Player* temp2);
	CREATE_FUNC(Secret);
private:
	cocos2d::Node * sprnode;
	cocos2d::PhysicsBody *_physicsBody;
	Player* _arthurPtr;
	Player* _percivalPtr;
	int _score;
};


#endif // !__SECRET_H__

