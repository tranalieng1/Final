#include "SwordMan.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



SwordMan::~SwordMan()
{

}

SwordMan::SwordMan()
{
}



void SwordMan::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 3; i++)
	{
		std::string name = StringUtils::format("SwordMan_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);//1:12

	Animate* animate = Animate::create(animation);
	_EnemySprite->runAction(RepeatForever::create(animate));
}

bool SwordMan::init()
{
	if (!Node::init())
		return false;

	//Set sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SwordMan.plist", "SwordMan.png");
	_EnemySprite = Sprite::createWithSpriteFrameName("SwordMan_Stand_1.png");
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

void SwordMan::Jump()
{
	_EnemySprite->setSpriteFrame("SwordMan_Stand_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);
}

void SwordMan::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 3; i++)
	{
		std::string name = StringUtils::format("SwordMan_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SwordMan_Stand_1.png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(animate);

}

void SwordMan::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("SwordMan_Walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(_WalkAction);
}

void SwordMan::StopAction()
{
	_EnemySprite->stopAllActions();
	_EnemySprite->setSpriteFrame("SwordMan_Stand_1.png");
}

void SwordMan::onContactBeganWith(GameObject * obj)
{
}

void SwordMan::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void SwordMan::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void SwordMan::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void SwordMan::takeDamage()
{
}
