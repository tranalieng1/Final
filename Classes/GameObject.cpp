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


