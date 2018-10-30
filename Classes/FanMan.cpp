#include "FanMan.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



FanMan::~FanMan()
{

}

FanMan::FanMan()
{
}



void FanMan::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("FatMan_attack1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);//1:12

	Animate* animate = Animate::create(animation);
	_FanManSprite->runAction(RepeatForever::create(animate));
}

bool FanMan::init()
{
	if (!Node::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FatMan.plist", "FatMan.png");
	_FanManSprite = Sprite::createWithSpriteFrameName("FatMan_stand_1.png");
	this->addChild(_FanManSprite);
	_FanManSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(_FanManSprite->getContentSize());
	//this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_FanManSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	return true;
}

void FanMan::Jump()
{
	_FanManSprite->setSpriteFrame("FatMan_stand_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*ARTHUR_JUMP, 1);
	this->runAction(_Jump);
}

void FanMan::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("FatMan_attack1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("FatMan_stand_1.png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_FanManSprite->runAction(animate);

}

void FanMan::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("FatMan_walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_FanManSprite->runAction(_WalkAction);
}

void FanMan::StopAction()
{
	_FanManSprite->stopAllActions();
	_FanManSprite->setSpriteFrame("FatMan_stand_1.png");
}
