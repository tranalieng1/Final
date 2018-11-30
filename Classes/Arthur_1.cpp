#include "Arthur_1.h"
#include "cocos2d.h"
#include"Defnition.h"
#include "SKeyboard.h"
USING_NS_CC;


std::map<AnimationType, AnimationInfo> Arthur_1::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "Arthur_0_walk_%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(4, "Arthur_0_attack_%d.png", 1.0f / 12.0f, 1) },
};

Arthur_1::~Arthur_1()
{

}

Arthur_1::Arthur_1()
{
	//_state.resize(2);
	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);
	_checkwalk = 0;
	_velocityX = 0;
	_velocityY = 0;
	_horizonDirection = Direction::RIGHT;
	_verticalDirection = Direction::TOP;
	_left = false;
	_right = true;

	_MaxHealth = 100;
	_MaxMana = 100;
	_Health = _MaxHealth;
	_Mana = _MaxMana;


}





void Arthur_1::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Arthur_0_attack_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12);

	Animate* animate = Animate::create(animation);
	_PlayerSprite->runAction(RepeatForever::create(animate));
}

bool Arthur_1::init()
{

	if (!Node::init())
		return false;
	//_state = STATE_STANDING;
	_checkwalk = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	_PlayerSprite = Sprite::createWithSpriteFrameName("Arthur_0_stand_1.png");
	//Set sprite
	this->addChild(_PlayerSprite);
	_PlayerSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_PlayerSprite->getContentSize().width, _PlayerSprite->getContentSize().height - 30));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_PlayerSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	this->setTag(TAG_ARTHUR);
	//Setbody
	_Physicbody = cocos2d::PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_Physicbody);
	_Physicbody->setDynamic(false);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);
	_Physicbody->setCategoryBitmask(ARTHUR_CATEGORY_BITMASK);
	_Physicbody->setCollisionBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
	_Physicbody->setContactTestBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);



	//Node attack physic body
	//_PhysicbodyAttack = cocos2d::PhysicsBody::createBox(_NodeAttack->getContentSize());
	//_NodeAttack->setPhysicsBody(_PhysicbodyAttack);
	//_PhysicbodyAttack->setDynamic(false);
	//_PhysicbodyAttack->setGravityEnable(false);
	//_PhysicbodyAttack->setRotationEnable(false);
	//_PhysicbodyAttack->setCategoryBitmask(ARTHUR_CATEGORY_BITMASK);
	//_PhysicbodyAttack->setCollisionBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
	//_PhysicbodyAttack->setContactTestBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
	//_NodeAttack->setVisible(true);
	//_NodeAttack->setTag(TAG_ATTACK);
	//scheduleUpdate();
	//Sethit


	
	
	return true;
}

void Arthur_1::Jump()
{
	//_ArthurSprite->setSpriteFrame("Arthur_0_stand_1.png");
	_PlayerSprite->stopAllActions();
	_PlayerSprite->setSpriteFrame("Arthur_0_jump_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);

}





void Arthur_1::StopAction()
{
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);

	_PlayerSprite->setSpriteFrame("Arthur_0_stand_1.png");
}

void Arthur_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{



	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		if (_checkwalk == 0)
		{
			SetState(_State::STATE_WALKING);
		}
		_left = true;
		_checkwalk++;
		_velocityX -= VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		this->setScaleX(-2.0f);
		//if(_checkwalk==0)
		//	this->WalkAnimation();
		//_checkwalk++;
		//_velocityX -= VELOCITY_VALUE_X;
		//this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{
		if (_checkwalk == 0)
		{
			SetState(_State::STATE_WALKING);
		}
		_velocityY -= VELOCITY_VALUE_Y;
		/*	if (_checkwalk == 0)
				this->WalkAnimation();*/
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
		/*if (_checkwalk == 0)*/
			/*this->WalkAnimation();*/
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
		/*if (_checkwalk == 0)
			this->WalkAnimation();*/
		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_K)
	{
		SetState(_State::STATE_ATTACKING);

	}
	else if (kc == EventKeyboard::KeyCode::KEY_J)
	{
		//SetState(_State::STATE_ATTACKING);
		//_MBlade->setPosition(Vec2(this->getContentSize().width, this->getContentSize().height * 0.0f));
		

	}

}

void Arthur_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		_left = false;
		if (_right == true)
			this->setScaleX(2.0f);
		_velocityX += VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			SetState(_State::STATE_STANDING);


	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{

		_velocityY += VELOCITY_VALUE_Y;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			SetState(_State::STATE_STANDING);

	}
	else if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		_right = false;
		if (_left == true)
			this->setScaleX(-2.0f);
		_velocityX -= VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			SetState(_State::STATE_STANDING);

	}
	else if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		_velocityY -= VELOCITY_VALUE_Y;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			SetState(_State::STATE_STANDING);
	}
}

void Arthur_1::onContactBeganWith(GameObject * obj)
{

}

void Arthur_1::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Arthur_1::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Arthur_1::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Arthur_1::SetState(_State state)
{
	if (_state[1] != state)
	{
		/*_hit->setVisible(false);*/
		_state[0] = _state[1];
		_state[1] = state;
		//_hit->setcollisin(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
		//_hit->setcatory(FATMAN_CATEGORY_BITMASK);
		switch (state)
		{
		case STATE_ATTACKING:
			this->PlayAnimation(AnimationType::ATTACKING);
			//this->Attack1Animation();
			this->_Physicbody->setVelocity(Vec2(0, 0));
			//_hit->setVisible(true);
			/*_hit->setcollisin(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
			_hit->setcatory(ARTHUR_CATEGORY_BITMASK);*/
		{
			auto hit = Hit::create();
			this->addChild(hit);
			hit->setTag(TAG_ATTACK_PLAYER);
			hit->setPosition(Vec2(this->getContentSize().width, this->getContentSize().height * 0.5f-10));
			hit->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([=]()
			{
				hit->removeFromParent();
			}), nullptr));
		}
			break;
		case STATE_JUMPING:
			break;
		case STATE_STANDING:
			this->_Physicbody->setVelocity(Vec2(0, 0));
			this->StopAction();
			break;
		case STATE_WALKING:
		{
			//this->WalkAnimation();
			this->PlayAnimation(AnimationType::WALKING);
			this->_physicsBody->setVelocity(Vec2(_velocityX, _velocityY));
		}
		break;
		default:
			break;
		}
	}
}

void Arthur_1::update(float delta)
{

}

void Arthur_1::takeDamage(float dmg)
{

}

//void Arthur_1::processInput()
//{
//	if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_A) == KeyState::KS_DOWN 
//		&& SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_D) == KeyState::KS_DOWN)
//	{
//		/*SetState(_State::STATE_STANDING);*/
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_A) == KeyState::KS_DOWN)
//	{
//		if (_state[2] != STATE_ATTACKING)
//		{
//			_checkwalk++;
//			_velocityX = -VELOCITY_VALUE_X;
//			this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//			this->setScaleX(-2.0f);
//			SetState(_State::STATE_WALKING);
//		}
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_D) == KeyState::KS_DOWN)
//	{
//		if (_state[2] != STATE_ATTACKING)
//		{
//			_velocityX = VELOCITY_VALUE_X;
//			this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//			_checkwalk++;
//			this->setScaleX(2.0f);
//			SetState(_State::STATE_WALKING);
//		}
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_S) == KeyState::KS_DOWN)
//	{
//		if (_state[2] != STATE_ATTACKING)
//		{
//			_velocityY = -VELOCITY_VALUE_Y;
//			this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//			_checkwalk++;
//			//this->setScaleX(2.0f);
//			SetState(_State::STATE_WALKING);
//		}
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_W) == KeyState::KS_DOWN)
//	{
//		if (_state[2] != STATE_ATTACKING)
//		{
//			_velocityY = VELOCITY_VALUE_Y;
//			this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//			_checkwalk++;
//			//this->setScaleX(2.0f);
//			SetState(_State::STATE_WALKING);
//		}
//	}
//	
//	if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_K) == KeyState::KS_PRESS)
//	{
//		SetState(_State::STATE_ATTACKING);
//	}
//}
//
//void Arthur_1::releaseInput()
//{
//	if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_A) == KeyState::KS_RELEASE)
//	{
//		_velocityX = 0;
//		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//		_checkwalk--;
//		if (_checkwalk == 0)
//			this->SetState(_State::STATE_STANDING);
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_D) == KeyState::KS_RELEASE)
//	{
//		_velocityX = 0;
//		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//		_checkwalk--;
//		if (_checkwalk == 0)
//			this->SetState(_State::STATE_STANDING);
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_S) == KeyState::KS_RELEASE)
//	{
//		_velocityY = 0;
//		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//		_checkwalk--;
//		if (_checkwalk == 0)
//			this->SetState(_State::STATE_STANDING);
//	}
//	else if (SKeyboard::getKeyState(EventKeyboard::KeyCode::KEY_W) == KeyState::KS_RELEASE)
//	{
//		_velocityY = 0;
//		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
//		_checkwalk--;
//		if (_checkwalk == 0)
//			this->SetState(_State::STATE_STANDING);
//	}
//}

void Arthur_1::onFinishAnimation()
{
	if (_state[1] == _State::STATE_ATTACKING)
	{
		SetState(_state[0]);
	}
}

float Arthur_1::getDamage()
{
	return this->_Strenght;
}

void Arthur_1::PlayAnimation(AnimationType type)
{
	AnimationInfo info = s_mapAnimations.at(type);
	Animation* animation = Animation::create();

	for (int i = 1; i < info.numFrame; i++)
	{
		std::string name = StringUtils::format(info.filePath.c_str(), i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(info.fps);

	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(Repeat::create(animate, info.loopTime), CallFunc::create([=]()
	{
		//if (type == AnimationType::ATTACKING)
		//_PlayerSprite->setSpriteFrame("Arthur_0_stand_1.png");
		this->onFinishAnimation();
	}), NULL);

	seq->setTag(TAG_ANIMATION);
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);
	_PlayerSprite->runAction(seq);
}
void Arthur_1::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Arthur_0_walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1.0f / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);

	_WalkAction->setTag(TAG_ANIMATION);
	this->stopActionByTag(TAG_ANIMATION);
	_PlayerSprite->runAction(_WalkAction);
}

void Arthur_1::Attack1Animation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("Arthur_0_attack_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	/*animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Arthur_0_stand_1.png"));*/
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(animate, CallFunc::create([=]()
	{
		this->onFinishAnimation();
	}), NULL);
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);
	seq->setTag(TAG_ANIMATION);
	_PlayerSprite->runAction(seq);
}
//tao vector state