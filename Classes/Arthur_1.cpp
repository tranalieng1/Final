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
		std::string name = StringUtils::format("Arthur_0_attack_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);

	Animate* animate = Animate::create(animation);
	_ArthurSprite->runAction(RepeatForever::create(animate));
}

bool Arthur_1::init()
{
	if (!Node::init())
		return false;
	_state = STATE_STANDING;
	_checkwalk = 0;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	_ArthurSprite = Sprite::createWithSpriteFrameName("Arthur_0_stand_1.png");
	this->addChild(_ArthurSprite);
	_ArthurSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(_ArthurSprite->getContentSize());
	//this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_ArthurSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	return true;
}

void Arthur_1::Jump()
{
	//_ArthurSprite->setSpriteFrame("Arthur_0_stand_1.png");
	_ArthurSprite->stopAllActions();
	_ArthurSprite->setSpriteFrame("Arthur_0_jump_1.png");
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
	animation->setDelayPerUnit(1/12.0f );

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
	_ArthurSprite->stopAction(_WalkAction);
	
	_ArthurSprite->setSpriteFrame("Arthur_0_stand_1.png");
}

_State Arthur_1::GetState()
{
	return this->_state;
}

void Arthur_1::SetState(_State state)
{
	this->_state = state;
}

void Arthur_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
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

