#include "Percival.h"
#include "cocos2d.h"
#include"Defnition.h"
#include "SKeyboard.h"
USING_NS_CC;


std::map<AnimationType, AnimationInfo> Percival::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "Percival_1_walk_%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(4, "Percival_1_comboattack1_%d.png", 1.0f / 12.0f, 1) },
	{ AnimationType::JUMPING, AnimationInfo(4, "Percival_1_jump_%d.png", 1.0f / 4.0f, 1) },
	{ AnimationType::HITTED, AnimationInfo(1, "Percival_1_getdown_%d.png", 1.0f / 4.0f, 1) },
	{AnimationType::FALLING, AnimationInfo(5, "Percival_1_getdown_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::GETUP, AnimationInfo(1, "Percival_1_win_%d.png", 1.0f / 4.0f, 1)},
};

Percival::~Percival()
{

}

Percival::Percival()
{

	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);
	_checkwalk = 0;
	_velocityX = 0;
	_velocityY = 0;
	_horizonDirection = Direction::RIGHT;
	_verticalDirection = Direction::TOP;
	_left = false;
	_right = false;

	_MaxHealth = 1000;
	_MaxMana = 100;
	_Health = _MaxHealth;
	_Mana = _MaxMana;
	_damage = 20;
	_score =0.f;
}





void Percival::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Percival_1_comboattack1_%d.png", i);
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
	//_state = STATE_STANDING;
	_checkwalk = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl1.plist", "PercivalLvl1.png");
	_PlayerSprite = Sprite::createWithSpriteFrameName("Percival_1_ default_1.png");


	//Set sprite
	this->addChild(_PlayerSprite);
	_PlayerSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_PlayerSprite->getContentSize().width , _PlayerSprite->getContentSize().height -20));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_PlayerSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	this->setTag(TAG_PERCIVAL);

	//Setbody
	_Physicbody = cocos2d::PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_Physicbody);
	_Physicbody->setDynamic(false);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);
	_Physicbody->setCategoryBitmask(PERCIVAL_CATEGORY_BITMASK);
	_Physicbody->setCollisionBitmask(PERCIVAL_COLLISION_AND_CONTACT_TEST_BITMASK);
	_Physicbody->setContactTestBitmask(PERCIVAL_COLLISION_AND_CONTACT_TEST_BITMASK);




	return true;
}

void Percival::Jump()
{

	_PlayerSprite->stopAllActions();
	_PlayerSprite->setSpriteFrame("Percival_1_jump_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);

}





void Percival::StopAction()
{
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);

	_PlayerSprite->setSpriteFrame("Percival_1_ default_1.png");
}

void Percival::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{



	if (kc == EventKeyboard::KeyCode::KEY_A)
	{

		this->setScaleX(-2.0f);

		if (_checkwalk == 0)
		{
			SetState(_State::STATE_WALKING);
		}
		_left = true;
		_checkwalk++;
		_velocityX -= VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));

		
	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{
		if (_checkwalk == 0)
		{
			SetState(_State::STATE_WALKING);
		}
		_velocityY -= VELOCITY_VALUE_Y;

		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		_right = true;
		if (_checkwalk == 0)
		{
			SetState(_State::STATE_WALKING);
		}
		this->setScaleX(2.0f);
		_velocityX += VELOCITY_VALUE_X;

		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		if (_checkwalk == 0)
		{
			SetState(_State::STATE_WALKING);
		}
		_velocityY += VELOCITY_VALUE_Y;

		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_K)
	{
		SetState(_State::STATE_ATTACKING);

	}
	else if (kc == EventKeyboard::KeyCode::KEY_J)
	{
		
	}
	else if (kc == EventKeyboard::KeyCode::KEY_L)
	{
		SetState(_State::STATE_JUMPING);
	}

}

void Percival::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		_left = false;
		if (_right == true)
			this->setScaleX(2.0f);
		_velocityX += VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0 && _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
		{
			SetState(_State::STATE_STANDING);
		}


	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{

		_velocityY += VELOCITY_VALUE_Y;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0 && _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
		{
			SetState(_State::STATE_STANDING);
		}

	}
	else if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		_right = false;
		if (_left == true)
			this->setScaleX(-2.0f);
		_velocityX -= VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0 && _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
		{
			SetState(_State::STATE_STANDING);
		}

	}
	else if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		_velocityY -= VELOCITY_VALUE_Y;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0 && _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
		{
			SetState(_State::STATE_STANDING);
		}
	}
}

void Percival::onContactBeganWith(GameObject * obj)
{

}

void Percival::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Percival::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Percival::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Percival::SetState(_State state)
{
	cocos2d::Spawn *spawn;
	if (_state[1] != state)
	{

		_state[0] = _state[1];
		_state[1] = state;

		switch (state)
		{
		case STATE_ATTACKING:
			this->PlayAnimation(AnimationType::ATTACKING);

			this->_Physicbody->setVelocity(Vec2(0, 0));
			
			{
				auto hit = Hit::create();
				hit->setScaleX(1.2f);
				hit->setScaleY(2.0f);
				this->addChild(hit);
				hit->setTag(TAG_ATTACK_PLAYER);
				hit->setDamage(_damage);
				hit->setPosition(Vec2(this->getContentSize().width, this->getContentSize().height * 0.5f - 10));
				hit->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([=]()
				{
					hit->removeFromParent();
				}), nullptr));
			}
			break;
		case STATE_JUMPING:
			this->runAction(JumpBy::create(1, Vec2(0, 0), 150, 1));
			this->PlayAnimation(AnimationType::JUMPING);
			break;
		case STATE_STANDING:
			this->_Physicbody->setVelocity(Vec2(0, 0));
			this->StopAction();
			break;
		case STATE_WALKING:
		{

			this->PlayAnimation(AnimationType::WALKING);
			this->_physicsBody->setVelocity(Vec2(_velocityX, _velocityY));
		}
		break;
		case STATE_HITTED:
		{
			this->PlayAnimation(AnimationType::HITTED);
		}
		break;
		case STATE_FALLING:
		{
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::FALLING);
			}), cocos2d::JumpBy::create(0.8f, Vec2(-100, 0), 50, 1), NULL);
			this->runAction(spawn);
		}
		break;
		case STATE_GETUP:
		{
			this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::GETUP);
			}), NULL));
		}
		break;
		case STATE_DEATH:
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::FALLING);
			}), cocos2d::JumpBy::create(0.8f, Vec2(-100, 0), 50, 1), cocos2d::Blink::create(1.2f, 10), NULL);

			this->runAction(Sequence::create(spawn, DelayTime::create(0.5f), CallFunc::create([=]()
			{
				this->setVisible(false);
			}), NULL));
			break;
		default:
			break;
		}
	}
}

void Percival::update(float delta)
{

}

void Percival::takeDamage(float dmg)
{
	_Health = _Health - dmg;
	
	if (this->_state[1] == STATE_HITTED)
	{

		if (_Health > 0)
		{
			this->SetState(STATE_FALLING);
		}
		else
		{
			this->SetState(STATE_DEATH);
		}
	}
	else
	{

		if (_Health > 0)
		{
			this->SetState(STATE_HITTED);
		}
		else
		{
			this->SetState(STATE_DEATH);
		}
	}
}



void Percival::onFinishAnimation()
{
	if (_state[1] == _State::STATE_ATTACKING && _checkwalk != 0)
	{
		SetState(_state[0]);
	}
	else if (_state[1] == _State::STATE_ATTACKING && _checkwalk == 0)
	{
		SetState(STATE_STANDING);
	}
	else if (_state[1] == _State::STATE_ATTACKING && _state[0] == _State::STATE_STANDING)
	{
		SetState(_state[0]);
	}


	else if (_state[1] == STATE_JUMPING && _checkwalk != 0)
	{
		SetState(_state[0]);
	}
	else if (_state[1] == STATE_JUMPING && _checkwalk == 0)
	{
		SetState(STATE_STANDING);
	}
	else if (_state[1] == STATE_HITTED)
	{
		this->SetState(STATE_STANDING);
	}
	else if (_state[1] == STATE_FALLING)
	{
		this->SetState(STATE_GETUP);
	}
	else if (_state[1] == STATE_GETUP)
	{
		this->SetState(STATE_STANDING);
	}
	else if (_state[1] == STATE_DEATH)
	{

	}
}



void Percival::PlayAnimation(AnimationType type)
{
	AnimationInfo info = s_mapAnimations.at(type);
	Animation* animation = Animation::create();

	for (int i = 1; i <= info.numFrame; i++)
	{
		std::string name = StringUtils::format(info.filePath.c_str(), i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(info.fps);

	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(Repeat::create(animate, info.loopTime), CallFunc::create([=]()
	{

		this->onFinishAnimation();
	}), NULL);

	seq->setTag(TAG_ANIMATION);
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);
	_PlayerSprite->runAction(seq);
}


