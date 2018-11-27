#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "cocos2d.h"
class GameObject: public cocos2d::Node
{
public:
	GameObject();
	~GameObject();

	virtual void onContactBeganWith(GameObject* obj) = 0;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) = 0;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) = 0;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) = 0;
	virtual bool init() override;
	float getDamage();
	void setDamage(float temp);
private:
protected:
	float _damage;
	
};


#endif // !__GAMEOBJECT_H__

