#include "Arthur_1.h"
#include "cocos2d.h"
#include"Defnition.h"
#include "SKeyboard.h"
USING_NS_CC;


std::map<AnimationType, AnimationInfo> Arthur_1::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "Arthur_%d_walk_%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(3, "Arthur_%d_attack_%d.png", 1.0f / 12.0f, 1) },
	//{ AnimationType::SWAPING, AnimationInfo(1, "Arthur_0_comboattack3_%d.png", 1.0f / 4.0f, 1) },
	{ AnimationType::JUMPING, AnimationInfo(1, "Arthur_%d_jump_%d.png", 1.0f / 4.0f, 4) },
	{ AnimationType::HITTED, AnimationInfo(1, "Arthur_%d_hitted_%d.png", 1.0f / 4.0f, 1) },
	{AnimationType::FALLING, AnimationInfo(3, "Arthur_%d_fall_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::GETUP, AnimationInfo(3, "Arthur_%d_getup_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::LEVELUP, AnimationInfo(2, "Arthur_%d_win_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::STANDING, AnimationInfo(1, "Arthur_%d_stand_%d.png", 1.0f / 8.0f, 1)},

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
	_right = false;

	_MaxHealth = 1000;
	_MaxMana = 100;
	_Health = _MaxHealth;
	_Mana = _MaxMana;
	_damage = 20;
	_score =0.f;
	_Level = 1;
}





void Arthur_1::Attack()
{
	
}

bool Arthur_1::init()
{

	if (!Node::init())
		return false;
	//_state = STATE_STANDING;
	_checkwalk = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl2.plist", "ArthurLvl2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl3.plist", "ArthurLvl3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl4.plist", "ArthurLvl4.png");
	_PlayerSprite = Sprite::createWithSpriteFrameName("Arthur_1_stand_1.png");
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




	_Physicbody->setDynamic(true);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);



	int a = PLAYER_CATE;

	_Physicbody->setCategoryBitmask(PLAYER_CATE);
	_Physicbody->setCollisionBitmask(PLAYER_COLL);
	_Physicbody->setContactTestBitmask(PLAYER_COLL);



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
	

}





void Arthur_1::StopAction()
{
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);
	this->PlayAnimation(AnimationType::STANDING);
	//_PlayerSprite->setSpriteFrame("Arthur_1_stand_1.png");
}

void Arthur_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
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
	else if (kc == EventKeyboard::KeyCode::KEY_L)
	{
		SetState(_State::STATE_JUMPING);
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
	cocos2d::Spawn *spawn;
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
				hit->setScaleX(1.2f);//1.2
				hit->setScaleY(2.0f);//2.0
				this->addChild(hit);
				hit->setTag(TAG_ATTACK_PLAYER);
				hit->setcatory(HIT_PLAYER_CATE);
				hit->setcollisin(HIT_PLAYER_COLL);
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
			this->setDeathLess(false);
			this->StopAction();
			break;
		case STATE_WALKING:
		{
			//this->WalkAnimation();
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
			this->setDeathLess(true);
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::FALLING);
			}), cocos2d::JumpBy::create(3/4.0f, Vec2(-100, 0), 50, 1), NULL);
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
			this->setDeathLess(true);
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::FALLING);
			}), cocos2d::JumpBy::create(0.8f, Vec2(-100, 0), 50, 1), cocos2d::Blink::create(1.2f, 10), NULL);
			//this->runAction(jum);
			this->runAction(Sequence::create(spawn, DelayTime::create(0.5f), CallFunc::create([=]()
			{
				this->setVisible(false);
			}), NULL));
			break;
		case STATE_LEVELUP:
			this->setDeathLess(true);
			this->PlayAnimation(AnimationType::LEVELUP);
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
	//else if (_state[1] == _State::STATE_SWAPING)
	//{
	//	//SetState(_State::STATE_WALKING);
	//}
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
	else if (_state[1] == STATE_LEVELUP)
	{
		this->SetState(STATE_STANDING);
	}
}



void Arthur_1::PlayAnimation(AnimationType type)
{
	AnimationInfo info = s_mapAnimations.at(type);
	Animation* animation = Animation::create();


	for (int i = 1; i <= info.numFrame; i++)
	{
		std::string name = StringUtils::format(info.filePath.c_str(),this->_Level, i);
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



//tao vector state