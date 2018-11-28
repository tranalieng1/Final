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

void Enemy::onFinishAnimation()
{
	if (_state[2] == _State::STATE_ATTACKING)
	{
		SetState(_state[1]);
	}
}

void Enemy::SetState(_State state)
{
	if (_state[1] != state)
	{
		_state[0] = _state[1];
		_state[1] = state;
	}
}
