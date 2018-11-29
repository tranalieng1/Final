#include "Garibaldi.h"

USING_NS_CC;

Garibaldi::Garibaldi()
{
}

Garibaldi::~Garibaldi()
{
}

void Garibaldi::Attack()
{
}

bool Garibaldi::init()
{
	if (!cocos2d::Node::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Garibaldi.plist", "Garibaldi.png");
	_BossSprite = Sprite::createWithSpriteFrameName("Garibaldi_stand_1.png");
	this->addChild(_BossSprite);
	_BossSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_BossSprite->getContentSize().width-20, _BossSprite->getContentSize().height - 20));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_BossSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);
	//Set physicbody
	_physicsBody = PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_physicsBody);
	_physicsBody->setGravityEnable(false);
	_physicsBody->setDynamic(false);

	return true;
}

void Garibaldi::Jump()
{

}

void Garibaldi::Attack1Animation()
{
}

void Garibaldi::WalkAnimation()
{
}

void Garibaldi::StopAction()
{
}

void Garibaldi::onContactBeganWith(GameObject * obj)
{
}

void Garibaldi::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Garibaldi::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Garibaldi::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Garibaldi::takeDamage()
{
}
