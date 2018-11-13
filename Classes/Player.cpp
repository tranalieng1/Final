#include "Player.h"

Player::Player()
{
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
	return _state;
}

void Player::SetState(_State state)
{
	this->_state = state;
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
}
