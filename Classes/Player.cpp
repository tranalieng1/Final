#include "Player.h"


Player::Player()
{
	_score = 0.f;
	/*_state.resize(2);
	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);*/
}

Player::~Player()
{
}

//void Player::Attack()
//{
//}

bool Player::init()
{
	if (!cocos2d::Node::init())
		return false;
	return true;
}

//void Player::Jump()
//{
//}
//
//void Player::Attack1Animation()
//{
//}
//
//void Player::WalkAnimation()
//{
//}
//
//void Player::StopAction()
//{
//}

_State Player::GetState()
{
	return _state[2];
}

void Player::SetState(_State state)
{
	_state[1] = _state[2];

	this->_state[2] = state;
}

float Player::getDamage()
{
	return 0.0f;
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
}

void Player::takeDamage(float dmg)
{
}

void Player::addScore(float temp)
{
	_score += temp;
}

float Player::getScore()
{
	return _score;
}
