#include "BusterS.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



BusterS::~BusterS()
{

}

BusterS::BusterS()
{
}



void BusterS::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string name = StringUtils::format("BusterS_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);//1:12

	Animate* animate = Animate::create(animation);
	_EnemySprite->runAction(RepeatForever::create(animate));
}

bool BusterS::init()
{
	if (!Node::init())
		return false;

	//Set sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BusterS.plist", "BusterS.png");
	_EnemySprite = Sprite::createWithSpriteFrameName("BusterS_Stand.png");
	this->addChild(_EnemySprite);
	_EnemySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_EnemySprite->getContentSize().width,_EnemySprite->getContentSize().height-20));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_EnemySprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	//Set physicbody
	_physicsBody = PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_physicsBody);
	_physicsBody->setGravityEnable(false);
	_physicsBody->setDynamic(false);

	return true;
}

void BusterS::Jump()
{
	_EnemySprite->setSpriteFrame("BusterS_Stand.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);
}

void BusterS::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string name = StringUtils::format("BusterS_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BusterS_Stand.png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(animate);

}

void BusterS::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("BusterS_Walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(_WalkAction);
}

void BusterS::StopAction()
{
	_EnemySprite->stopAllActions();
	_EnemySprite->setSpriteFrame("BusterS_Stand.png");
}

void BusterS::onContactBeganWith(GameObject * obj)
{
}

void BusterS::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void BusterS::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void BusterS::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}
