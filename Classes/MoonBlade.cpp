#include"MoonBlade.h"
#include"Defnition.h"
#include"cocos2d.h"
USING_NS_CC;

MoonBlade::MoonBlade() : _willBeDestroy(false)
{
	_damage = 100.0f;
	_ManaR = -20.0f;
}

MoonBlade::~MoonBlade()
{

}

bool MoonBlade::init()
{
	if (!GameObject::init())
		return false;
	_MBSprite1 = Sprite::create("Skill_MoonBlade.png");
	_MBSprite2 = Sprite::create("Skill_MoonBlade.png");
	_MBSprite3 = Sprite::create("Skill_MoonBlade.png");
	this->addChild(_MBSprite1,1);
	this->addChild(_MBSprite2,2);
	this->addChild(_MBSprite3,3);
	_MBSprite1->setFlippedX(true);
	_MBSprite2->setFlippedX(true);
	_MBSprite3->setFlippedX(true);
	_MBSprite1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_MBSprite2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_MBSprite3->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(_MBSprite1->getContentSize());
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_MBSprite1->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	_MBSprite2->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	_MBSprite3->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.7f);
	
	_Physicbody = cocos2d::PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_Physicbody);
	_Physicbody->setDynamic(false);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);
	_Physicbody->setCategoryBitmask(HIT_PLAYER_CATE);
	_Physicbody->setCollisionBitmask(0);
	_Physicbody->setContactTestBitmask(0);
	this->setTag(TAG_ATTACK_ARTHUR);

	this->setVisible(false);
	scheduleUpdate();
	return true;
}

void MoonBlade::flySkill()
{
	if (this->getScaleX() > 0)
	{
		temp = -0.7f;
	}
	else
	{
		temp = +0.7f;
	}

	this->setVisible(true);
	this->scheduleUpdate();
	//_Physicbody->setCategoryBitmask(PLAYER_CATE);
	_Physicbody->setCollisionBitmask(HIT_PLAYER_COLL);
	_Physicbody->setContactTestBitmask(HIT_PLAYER_COLL);
	
	_MBSprite1->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	_MBSprite2->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	_MBSprite3->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	_MBSprite2->runAction(MoveBy::create(0.5, Vec2(_MBSprite1->getContentSize().width* temp, 0)));
	_MBSprite3->runAction(MoveBy::create(0.5, Vec2(_MBSprite1->getContentSize().width* (2*temp), 0)));
	if (this->getScaleX() > 0)
	{
		temp = 1000.0f;
	}
	else
	{
		temp = -1000.0f;
	}
	auto action = MoveBy::create(1, Vec2(temp, 0));
	auto seq = Sequence::create(action, CallFunc::create([=]()
	{
		this->_willBeDestroy = true;
	}), NULL);
	this->runAction(seq);
}

void MoonBlade::onContactBeganWith(GameObject * obj)
{
	if (obj->getTag() == TAG_CREEP)
	{
		auto objPos = obj->convertToNodeSpaceAR(Vec2::ZERO);
		auto thisPos = this->convertToNodeSpaceAR(Vec2::ZERO);
		objPos.y;
			//objPos.x
		thisPos.y;
		if (abs(objPos.y +15 - thisPos.y) <= 15)
		
			obj->takeDamage(_damage, TAG_ATTACK_ARTHUR );
		//obj->setVisible(false);
	}
}

void MoonBlade::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void MoonBlade::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
	solve.ignore();
}

void MoonBlade::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void MoonBlade::takeDamage(float dmg, int temp)
{
}

void MoonBlade::setOnDestroyCallback(OnHitDestroyCallback callback)
{
	_onHitDestroyCallback = callback;
}

void MoonBlade::update(float delta)
{
	if (_willBeDestroy)
	{
		//_Physicbody->setCategoryBitmask(ENEMY_CATE);
		_Physicbody->setCollisionBitmask(0);
		_Physicbody->setContactTestBitmask(0);
		this->setVisible(false);
		if (_onHitDestroyCallback)
		{
			_onHitDestroyCallback(this);
		}
		this->removeFromParent();
		this->_willBeDestroy = false;
	}
}

float MoonBlade::getMana()
{
	return _ManaR;
}
