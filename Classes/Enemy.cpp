#include "Enemy.h"
#include "Defnition.h"
Enemy::Enemy()
{
	_playerPtr = nullptr;
	_timeUpdateAI = 0.0f;
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



void Enemy::takeDamage(float dmg)
{
}

void Enemy::SetState(_State state)
{
	
}

void Enemy::setDeathLess(bool temp)
{
	if (temp == true)
	{
		this->getPhysicsBody()->setCategoryBitmask(ARTHUR_CATEGORY_BITMASK);
		this->getPhysicsBody()->setCollisionBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
		this->getPhysicsBody()->setContactTestBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
	
	}
	else
	{
		this->getPhysicsBody()->setCategoryBitmask(FATMAN_CATEGORY_BITMASK);
		this->getPhysicsBody()->setCollisionBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
		this->getPhysicsBody()->setContactTestBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
	}
}

void Enemy::scheduleUpdateAI(float delta)
{
	
}

void Enemy::enalbeAI(Player* player)
{
	this->_playerPtr = player;
	this->schedule(CC_SCHEDULE_SELECTOR(Enemy::scheduleUpdateAI), _timeUpdateAI, CC_REPEAT_FOREVER, 0.0f);
}

void Enemy::update(float delta)
{
}
