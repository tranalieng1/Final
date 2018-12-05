#include "Player.h"


Player::Player()
{
	_score = 0.f;
	/*_state.resize(2);
	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);*/
	movedown = false;
	moveup = false;
	moveright = false;
	moveleft = false;
	_checkwalk = 0;
	_Health =1;

	_Mana=2;

	_MaxHealth=2;
	_MaxMana=1;

	_score = 0;
	_Level = 1;
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

float Player::getHealth()
{
	return (_Health / _MaxHealth)*100;
}

bool Player::addMana(float temp)
{
	if (temp < 0)
	{
		if (abs(temp) > _Mana)
			return false;
		else
		{
			_Mana = _Mana + temp;
			return true;
		}
	}
	else
	{
		_Mana = _Mana + temp;
		if (_Mana > _MaxMana)
			_Mana = _MaxMana;
	}
	return true;
}

float Player::getMana()
{
	return (_Mana/_MaxMana)*100;
}

void Player::setLevel(int temp)
{
	_Level = temp;
}

int Player::getLevel()
{
	return _Level;
}

void Player::LevelUp()
{
	_Level++;
	_damage += 10;
	_Health += 10;
}

