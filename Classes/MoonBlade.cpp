#include"MoonBlade.h"
#include"Defnition.h"
#include"cocos2d.h"
USING_NS_CC;
MoonBlade::MoonBlade()
{
}

MoonBlade::~MoonBlade()
{

}

bool MoonBlade::init()
{
	if (!Node::init())
		return false;
	_MBSprite1 = Sprite::create("Skill_MoonBlade.png");
	_MBSprite2 = Sprite::create("Skill_MoonBlade.png");
	_MBSprite3 = Sprite::create("Skill_MoonBlade.png");
	this->addChild(_MBSprite1,0);
	this->addChild(_MBSprite2,0);
	this->addChild(_MBSprite3,0);
	_MBSprite1->setFlippedX(true);
	_MBSprite2->setFlippedX(true);
	_MBSprite3->setFlippedX(true);
	_MBSprite1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_MBSprite2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_MBSprite3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setContentSize(_MBSprite1->getContentSize());
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_MBSprite1->setPosition(this->getContentSize()*0.5);
	_MBSprite2->setPosition(this->getContentSize()*0.5);
	_MBSprite3->setPosition(this->getContentSize()*0.5);
	this->setScale(2.0);
	return true;
}

void MoonBlade::flySkill()
{
	_MBSprite1->setPosition(this->getContentSize()*0.5);
	_MBSprite2->setPosition(this->getContentSize()*0.5);
	_MBSprite3->setPosition(this->getContentSize()*0.5);
	_MBSprite2->runAction(MoveBy::create(0.5, Vec2(_MBSprite1->getContentSize().width*-0.7, 0)));
	_MBSprite3->runAction(MoveBy::create(0.5, Vec2(_MBSprite1->getContentSize().width*-1.4, 0)));
	this->runAction(MoveBy::create(0.8, Vec2(900, 0)));
	
	
}
