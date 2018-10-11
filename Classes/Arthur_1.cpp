#include "Arthur_1.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



Arthur_1::~Arthur_1()
{

}

Arthur_1::Arthur_1()
{
}



void Arthur_1::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Arthur_0_attack_d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_ArthurSprite->runAction(RepeatForever::create(animate));
}

bool Arthur_1::init()
{
	if (!Node::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	_ArthurSprite = Sprite::createWithSpriteFrameName("Arthur_0_stand_1.png");
	this->addChild(_ArthurSprite);
	_ArthurSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_ArthurSprite->getContentSize());
	//this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_ArthurSprite->setPosition(this->getContentSize() * 0.0f);
	this->setScale(2.0);

	return true;
}

void Arthur_1::Jump()
{
	_ArthurSprite->setSpriteFrame("Arthur_0_stand_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f,0.0f),  this->getContentSize().height*ARTHUR_JUMP, 1);
	this->runAction(_Jump);
}

void Arthur_1::Attack1Animation()
{
	
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Arthur_0_attack_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Arthur_0_stand_1.png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_ArthurSprite->runAction(animate);
	
}

void Arthur_1::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Arthur_0_walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_ArthurSprite->runAction(_WalkAction);
}

void Arthur_1::StopAction()
{
	_ArthurSprite->stopAllActions();
	_ArthurSprite->setSpriteFrame("Arthur_0_stand_1.png");
}
