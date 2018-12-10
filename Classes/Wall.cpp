#include "Wall.h"
#include"Defnition.h"
Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::onContactBeganWith(GameObject * obj)
{
}

void Wall::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Wall::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Wall::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

bool Wall::init()
{
	if (!cocos2d::Node::init())
		return false;
	this->setTag(TAG_WALL);
	return true;

}

void Wall::takeDamage(float dmg, int temp)
{
}
