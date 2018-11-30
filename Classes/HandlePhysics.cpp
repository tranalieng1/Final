#include "HandlePhysics.h"
#include "GameObject.h"
HandlePhysics::HandlePhysics()
{
}

HandlePhysics::~HandlePhysics()
{
}

bool HandlePhysics::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	// Cach 2
	auto obj1 = dynamic_cast<GameObject*>(bodyA->getNode());
	auto obj2 = dynamic_cast<GameObject*>(bodyB->getNode());

	if (obj1 && obj2)
	{
		obj1->onContactBeganWith(obj2);
		obj2->onContactBeganWith(obj1);
	}
	//
	// Cach 1
	//auto userDataA = static_cast<Node*>(bodyA->GetUserData());
	//auto userDataB = static_cast<Node*>(bodyB->GetUserData());
	//if (userDataA->getTag() == (int)ObjectTAG::TAG_CHARACTER)
	//{
	//	//
	//}
	//else if (userDataB->getTag() == (int)ObjectTAG::TAG_CHARACTER)
	//{
	//	//
	//}
	// 
	//auto castobj = static_cast<MainCharacter*>(bodyA->GetUserData());
	//if (castobj) // A la character
	//{
	//	castobj->jump();
	//	auto platform = static_cast<Platform*>(bodyB->GetUserData());
	//	platform->fallDown();
	//}
	//else // B la character
	//{
	//	auto body = static_cast<MainCharacter*>(bodyB->GetUserData());
	//	body->jump();
	//	auto platform = static_cast<Platform*>(bodyA->GetUserData());
	//	platform->fallDown();
	//}
	
	return true;
}

void HandlePhysics::onContactSeperated(cocos2d::PhysicsContact & contact)
{
	//auto bodyA = contact.getShapeA()->getBody();
	//auto bodyB = contact.getShapeB()->getBody();

	//// Cach 2
	//auto obj1 = dynamic_cast<GameObject*>(bodyA->getNode());
	//auto obj2 = dynamic_cast<GameObject*>(bodyB->getNode());

	//if (obj1 && obj2)
	//{
	//	obj1->onContactSeparateWith(obj2,contact);
	//	obj2->onContactSeparateWith(obj1, contact);
	//}
}

bool HandlePhysics::onContactPreSolve(cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	// Cach 2
	auto obj1 = dynamic_cast<GameObject*>(bodyA->getNode());
	auto obj2 = dynamic_cast<GameObject*>(bodyB->getNode());

	if (obj1 && obj2)
	{
		obj1->onContactPreSolveWith(obj2, contact, solve);
		obj2->onContactPreSolveWith(obj1, contact, solve);
	}
	return true;
}

void HandlePhysics::onContactPostSolve(cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}
