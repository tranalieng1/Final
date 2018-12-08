
#ifndef __WALL_H__
#define __WALL_H__
#include"cocos2d.h"
#include "GameObject.h"
class Wall :public GameObject
{
public:
	Wall();
	~Wall();

 void onContactBeganWith(GameObject* obj) override;
 void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
 void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
 void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
 bool init() override;
 virtual void takeDamage(float dmg) override;
 CREATE_FUNC(Wall);
private:

};


#endif // !__WALL_H__
