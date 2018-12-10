#include "Secret.h"
#include "Defnition.h"
USING_NS_CC;
Secret::Secret()
{
	_score = 3000;
}

Secret::~Secret()
{
}

void Secret::takeDamage(float dmg, int temp)
{
	if (temp == TAG_ATTACK_ARTHUR)
		_arthurPtr->addScore(_score);
	else if(temp == TAG_ATTACK_PERCIVAL)
		_percivalPtr->addScore(_score);
	this->runAction(RemoveSelf::create());
}

bool Secret::init()
{
	if (!GameObject::init())
		return false;
	sprnode = Node::create();
	sprnode->setContentSize(Size(50, 50));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprnode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(sprnode);
	this->setContentSize(sprnode->getContentSize());
	sprnode->setPosition(Vec2(this->getContentSize().width, this->getContentSize().height));

	_physicsBody = PhysicsBody::createBox(Size(this->getContentSize()));
	this->setPhysicsBody(_physicsBody);
	_physicsBody->setGravityEnable(false);
	_physicsBody->setDynamic(false);
	_physicsBody->setRotationEnable(false);
	_physicsBody->setCategoryBitmask(SECRET_CATE);
	_physicsBody->setCollisionBitmask(SECRET_COLL);
	_physicsBody->setContactTestBitmask(SECRET_COLL);
	this->setTag(TAG_SECRET);
	return true;
}

void Secret::onContactBeganWith(GameObject * obj)
{
}

void Secret::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Secret::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Secret::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Secret::setPlayer(Player * temp1, Player * temp2)
{
	_arthurPtr = temp1;
	_percivalPtr = temp2;
}
