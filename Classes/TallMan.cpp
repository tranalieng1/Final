#include "TallMan.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



TallMan::~TallMan()
{

}

TallMan::TallMan()
{
}



void TallMan::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 2; i++)
	{
		std::string name = StringUtils::format("TallMan_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);//1:12

	Animate* animate = Animate::create(animation);
	_EnemySprite->runAction(RepeatForever::create(animate));
}

bool TallMan::init()
{
	if (!Node::init())
		return false;

	//Set sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TallMan.plist", "TallMan.png");
	_EnemySprite = Sprite::createWithSpriteFrameName("TallMan_Stand_1 .png");
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

void TallMan::Jump()
{
	_EnemySprite->setSpriteFrame("TallMan_Stand_1 .png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);
}

void TallMan::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 2; i++)
	{
		std::string name = StringUtils::format("TallMan_Attack_1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("TallMan_Stand_1 .png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(animate);

}

void TallMan::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("TallMan_Walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(_WalkAction);
}

void TallMan::StopAction()
{
	_EnemySprite->stopAllActions();
	_EnemySprite->setSpriteFrame("TallMan_Stand_1 .png");
}

void TallMan::onContactBeganWith(GameObject * obj)
{
}

void TallMan::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void TallMan::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void TallMan::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void TallMan::takeDamage(float dmg)
{
}
