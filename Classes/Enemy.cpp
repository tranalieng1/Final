#include "Enemy.h"
#include "Defnition.h"
Enemy::Enemy()
{
	_Arthurptr = nullptr;
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



void Enemy::takeDamage(float dmg, int temp)
{
}

void Enemy::attack(float delta)
{
	this->SetState(STATE_ATTACKING);
}

void Enemy::SetState(_State state)
{
	
}

void Enemy::setDeathLess(bool temp)
{
	if (temp == true)
	{
		//this->getPhysicsBody()->setCategoryBitmask(PLAYER_CATE);
		this->getPhysicsBody()->setCollisionBitmask(PLAYER_COLL);
		this->getPhysicsBody()->setContactTestBitmask(PLAYER_COLL);
	
	}
	else
	{
		//this->getPhysicsBody()->setCategoryBitmask(ENEMY_CATE);
		this->getPhysicsBody()->setCollisionBitmask(ENEMY_COLL);
		this->getPhysicsBody()->setContactTestBitmask(ENEMY_COLL);
	}
}

void Enemy::scheduleUpdateAI(float delta)
{
	
}

void Enemy::enalbeAI(Player* player)
{
	this->_Arthurptr = player;
	this->schedule(CC_SCHEDULE_SELECTOR(Enemy::scheduleUpdateAI), _timeUpdateAI, CC_REPEAT_FOREVER,0.0f);
}

void Enemy::update(float delta)
{
}

void Enemy::setscene(GameScene_1 * Scene)
{
	scene = Scene;
}
