#include "Hit.h"
#include "Defnition.h"
Hit::Hit()
{
}

Hit::~Hit()
{
}

bool Hit::init()
{
	if (!cocos2d::Node::init())
		return false;
	
	
	this->setContentSize(cocos2d::Size(20, 20));
	_Physicbody = cocos2d::PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_Physicbody);
	_Physicbody->setDynamic(false);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);
	_Physicbody->setCategoryBitmask(PLAYER_CATE);
	_Physicbody->setCollisionBitmask(PLAYER_COLL);
	_Physicbody->setContactTestBitmask(PLAYER_COLL);

	_Physicbody2 = _Physicbody;

	return true;
}

void Hit::onContactBeganWith(GameObject * obj)
{
	///chem enemy
	if (obj->getTag() == TAG_CREEP&& this->getTag()== TAG_ATTACK_ARTHUR)
	{
		obj->takeDamage(_damage, TAG_ATTACK_ARTHUR);
	}
	else if (obj->getTag() == TAG_CREEP && this->getTag() == TAG_ATTACK_PERCIVAL)
	{
		obj->takeDamage(_damage, TAG_ATTACK_PERCIVAL);
	}
	//// enemy chem player
	else if (obj->getTag() == TAG_PLAYER && this->getTag() == TAG_ATTACK_ENEMY)
	{
		obj->takeDamage(_damage, TAG_ATTACK_ENEMY);
	}
	//player chem Secret
	else if (obj->getTag() == TAG_SECRET && this->getTag() == TAG_ATTACK_ARTHUR)
	{
		obj->takeDamage(_damage, TAG_ATTACK_ARTHUR);
	}
	else if (obj->getTag() == TAG_SECRET && this->getTag() == TAG_ATTACK_PERCIVAL)
	{
		obj->takeDamage(_damage, TAG_ATTACK_PERCIVAL);
	}
	
}

void Hit::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
	
}

void Hit::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
	solve.ignore();
}

void Hit::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Hit::setSize_body(cocos2d::Size temp)
{
	this->setContentSize(temp);
}

void Hit::setcatory(int temp)
{
	_physicsBody->setCategoryBitmask(temp);
}

void Hit::setcollisin(int temp)
{
	_physicsBody->setCollisionBitmask(temp);
	_physicsBody->setContactTestBitmask(temp);
}

void Hit::takeDamage(float dmg,int temp)
{

}

