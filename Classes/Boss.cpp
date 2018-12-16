#include "Boss.h"
#include "Defnition.h"
Boss::Boss()
{
	_Arthurptr = nullptr;
	_timeUpdateAI = 0.0f;
	_Percialptr = nullptr;

}

Boss::~Boss()
{
}

bool Boss::init()
{
	if (!cocos2d::Node::init())
		return false;
	return true;
}

void Boss::takeDamage(float dmg,int temp)
{
}

void Boss::SetState(_State state)
{
}

void Boss::setDeathLess(bool temp)
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

void Boss::enalbeAI(Player * player)
{
	this->_Arthurptr = player;
	this->schedule(CC_SCHEDULE_SELECTOR(Boss::scheduleUpdateAI), _timeUpdateAI, CC_REPEAT_FOREVER, 0.0f);
}

void Boss::scheduleUpdateAI(float delta)
{
}

void Boss::update(float delta)
{
}

void Boss::setScene(GameScene_1 * temp)
{
	scene = temp;
}
