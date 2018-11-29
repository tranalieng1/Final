#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
}

bool Enemy::init()
{
	if(!cocos2d::Node::init())
		return false;
	return true;
}

_State Enemy::GetState()
{
	return _state[1];
}



void Enemy::takeDamage()
{
}

void Enemy::SetState(_State state)
{
	
}
