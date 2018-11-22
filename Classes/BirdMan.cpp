#include "BirdMan.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



BirdMan::~BirdMan()
{

}

BirdMan::BirdMan()
{
}



void BirdMan::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("BirdMan_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);//1:12

	Animate* animate = Animate::create(animation);
	_EnemySprite->runAction(RepeatForever::create(animate));
}

bool BirdMan::init()
{
	if (!Node::init())
		return false;

	//Set sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BirdMan.plist", "BirdMan.png");
	_EnemySprite = Sprite::createWithSpriteFrameName("BirdMan_Defence_1.png");
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

void BirdMan::Jump()
{
	_EnemySprite->setSpriteFrame("BirdMan_Defence_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);
}

void BirdMan::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("BirdMan_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BirdMan_Defence_1.png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(animate);

}

void BirdMan::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("BirdMan_Walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(_WalkAction);
}

void BirdMan::StopAction()
{
	_EnemySprite->stopAllActions();
	_EnemySprite->setSpriteFrame("BirdMan_Defence_1.png");
}

void BirdMan::onContactBeganWith(GameObject * obj)
{
}

void BirdMan::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void BirdMan::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void BirdMan::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}
