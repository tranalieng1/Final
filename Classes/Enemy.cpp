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
