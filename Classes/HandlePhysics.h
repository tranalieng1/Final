#ifndef __HANDLE_PHYSICS_H__
#define __HANDLE_PHYSICS_H__
#include "cocos2d.h"
class HandlePhysics
{
public:
	HandlePhysics();
	~HandlePhysics();
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact);

	virtual void onContactSeperated(cocos2d::PhysicsContact& contact);

	virtual bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);

	virtual void onContactPostSolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
private:

};


#endif // !__HANDLE_PHYSICS_H__

