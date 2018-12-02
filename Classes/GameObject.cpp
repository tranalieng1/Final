#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

bool GameObject::init()
{
	if(!cocos2d::Node::init())
		return false;
	return true;
}

float GameObject::getDamage()
{
	return 0.0f;

}

void GameObject::setDamage(float temp)
{
	this->_damage = temp;
}

//void GameObject::enalbeAI(GameObject* player)
//{
//
//}

