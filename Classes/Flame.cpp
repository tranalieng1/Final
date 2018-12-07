#include "Flame.h"
#include "Defnition.h"
USING_NS_CC;
Flame::Flame()
{
	
}
#define SKILL_DELAY 1.0f/14.0f
Flame::~Flame()
{
}

bool Flame::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/Flame.plist", "Skill/Flame.png");
	if (!GameObject::init())
		return false;
	_Flame1 = Sprite::createWithSpriteFrameName("Flame_1.png");
	_Flame2 = Sprite::createWithSpriteFrameName("Flame_1.png");
	_Flame1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_Flame2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	
	this->setContentSize(Size(_Flame1->getContentSize().width*2+50, _Flame1->getContentSize().width));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_Flame1->setPosition(Vec2(25, 0));
	_Flame2->setPosition(Vec2(_Flame1->getContentSize().width*2 +25 , 0));
	
	this->addChild(_Flame1);
	this->addChild(_Flame2);
	this->setScale(1.3f);
	
	
	this->setTag(TAG_SKILL_FLAME);

	this->setVisible(false);
	return true;
}

void Flame::onContactBeganWith(GameObject * obj)
{

}

void Flame::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Flame::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Flame::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Flame::takeDamage(float dmg)
{
}

void Flame::active()
{
	
	_Physicbody = cocos2d::PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_Physicbody);
	_Physicbody->setDynamic(false);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);
	_Physicbody->setCategoryBitmask(FATMAN_CATEGORY_BITMASK);
	_Physicbody->setCollisionBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
	_Physicbody->setContactTestBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);


	this->setVisible(true);
	auto seq = Sequence::create( CallFunc::create([=]()
	{

		/*_Physicbody->setCategoryBitmask(FATMAN_CATEGORY_BITMASK);
		_Physicbody->setCollisionBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
		_Physicbody->setContactTestBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
		this->setVisible(false);*/
		this->playanimation();
	}), DelayTime::create(0.5), CallFunc::create([=]()
	{
		this->getPhysicsBody()->removeFromWorld();
	}), DelayTime::create(0.5), CallFunc::create([=]()
	{
		
		this->setVisible(false);
	}),NULL);
	this->runAction(seq);

}

void Flame::playanimation()
{
	
	Animation* animation = Animation::create();
	Animation* animation2 = Animation::create();

	for (int i = 1; i <= 14; i++)
	{
		std::string name = StringUtils::format("Flame_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(SKILL_DELAY);
	animation2->setDelayPerUnit(SKILL_DELAY);
	Animate* animate = Animate::create(animation);
	Animate* animate2 = Animate::create(animation2);
	/*auto seq = Sequence::create(Repeat::create(animate, 1), CallFunc::create([=]()
	{

		this->onFinishAnimation();
	}), NULL);*/

	//seq->setTag(TAG_ANIMATION);
	//_Flame1->stopActionByTag(TAG_ANIMATION);
	this->_Flame1->runAction(Repeat::create(animate, 1));
	this->_Flame2->runAction(Repeat::create(animate2, 1));
}
