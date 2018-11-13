#include "Percival.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



Percival::~Percival()
{

}

Percival::Percival()
{
}



void Percival::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Percival_1_attack_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12);

	Animate* animate = Animate::create(animation);
	_PlayerSprite->runAction(RepeatForever::create(animate));
}

bool Percival::init()
{
	if (!Node::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl1.plist", "PercivalLvl1.png");
	_PlayerSprite = Sprite::createWithSpriteFrameName("Percival_1_stand_1.png");
	this->addChild(_PlayerSprite);
	_PlayerSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(_PlayerSprite->getContentSize());
	//this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_PlayerSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	return true;
}

void Percival::Jump()
{
	//_PercivalSprite->setSpriteFrame("Percival_1_stand_1.png");
	_PlayerSprite->stopAllActions();
	_PlayerSprite->setSpriteFrame("Percival_1_jump_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);

}

void Percival::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Percival_1_attack_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Percival_1_stand_1.png"));
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_PlayerSprite->runAction(animate);

}

void Percival::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Percival_1_walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_PlayerSprite->runAction(_WalkAction);
}

void Percival::StopAction()
{
	_PlayerSprite->stopAction(_WalkAction);

	_PlayerSprite->setSpriteFrame("Percival_1_stand_1.png");
}

void Percival::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	switch (this->GetState())
	{
	case STATE_ATTACKING:
		break;
	case STATE_JUMPING:
		break;
	case STATE_STANDING:
		if (kc == EventKeyboard::KeyCode::KEY_D)
		{

			//_Arthur->setScaleX(2.0f);
			if (_checkwalk == 0)
				this->WalkAnimation();
			moveright = true;

			_checkwalk++;
		}
		if (kc == EventKeyboard::KeyCode::KEY_A)
		{
			//_Arthur->setScaleX(-2.0f);

			moveleft = true;
			if (_checkwalk == 0)
				this->WalkAnimation();
			_checkwalk++;
		}
		if (kc == EventKeyboard::KeyCode::KEY_S)
		{
			movedown = true;
			if (_checkwalk == 0)
				this->WalkAnimation();
			_checkwalk++;
		}
		if (kc == EventKeyboard::KeyCode::KEY_W)
		{
			moveup = true;
			if (_checkwalk == 0)
				this->WalkAnimation();
			_checkwalk++;
		}
		else if (kc == EventKeyboard::KeyCode::KEY_K)
		{

			this->Attack1Animation();
			this->SetState(STATE_ATTACKING);
			//_Arthur->StopAction();
		}
		else if (kc == EventKeyboard::KeyCode::KEY_J)
		{

			/*	moonblade->setPosition(Vec2(_Arthur->getPositionX() + _Arthur->getContentSize().width / 2 + 20, _Arthur->getPositionY() + +10));
			moonblade->setVisible(true);
			moonblade->flySkill();*/
		}
		else if (kc == EventKeyboard::KeyCode::KEY_L)
		{
			/*if (CheckJump(_Arthur, _nodePosPlayer) == true)
			{*/
			this->Jump();
			this->SetState(STATE_JUMPING);
			/*}*/
		}
		break;
	case STATE_WALKING:
		break;
	default:
		break;
	}
}

void Percival::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
}

void Percival::onContactBeganWith(Player * obj)
{
}

void Percival::onContactPostSolveWith(Player * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Percival::onContactPreSolveWith(Player * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Percival::onContactSeparateWith(Player * obj, cocos2d::PhysicsContact & contact)
{
}
