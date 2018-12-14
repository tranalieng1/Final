#include "Percival.h"
#include "cocos2d.h"
#include"Defnition.h"
#include "SKeyboard.h"
#include "AudioEngine.h"
USING_NS_CC;


std::map<AnimationType, AnimationInfo> Percival::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "Percival_%d_walk_%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(4, "Percival_%d_comboattack1_%d.png", 1.0f / 12.0f, 1) },
	{ AnimationType::JUMPING, AnimationInfo(4, "Percival_%d_jump_%d.png", 1.0f / 4.0f, 1) },
	{ AnimationType::HITTED, AnimationInfo(1, "Percival_%d_getdown_%d.png", 1.0f / 4.0f, 1) },
	{AnimationType::FALLING, AnimationInfo(5, "Percival_%d_getdown_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::GETUP, AnimationInfo(1, "Percival_%d_win_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::LEVELUP, AnimationInfo(2, "Percival_%d_win_%d.png", 1.0f / 4.0f, 1)},
	{AnimationType::STANDING, AnimationInfo(1, "Percival_%d_stand_%d.png", 1.0f / 8.0f, 1)},
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
	

	_MaxHealth = 1000;
	_MaxMana = 100;
	_Health = _MaxHealth;
	_Mana = _MaxMana;
	_damage = 20;
	_score =0.f;
	_Level = 1;
}





void Percival::Attack()
{
	
}

bool Percival::init()
{

	if (!Node::init())
		return false;
	//_state = STATE_STANDING;
	_checkwalk = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl1.plist", "PercivalLvl1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl2.plist", "PercivalLvl2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl3.plist", "PercivalLvl3.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl4.plist", "PercivalLvl4.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl12.plist", "PercivalLvl12.png");
	_PlayerSprite = Sprite::createWithSpriteFrameName("Percival_1_ default_1.png");


	//Set sprite
	this->addChild(_PlayerSprite);
	_PlayerSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_PlayerSprite->getContentSize().width , _PlayerSprite->getContentSize().height -20));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_PlayerSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);

	this->setTag(TAG_PLAYER);

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




	return true;
}

void Percival::Jump()
{

}





void Percival::StopAction()
{
	_checkwalk = 0;
	this->_Physicbody->setVelocity(Vec2(0, 0));
	_PlayerSprite->stopActionByTag(TAG_ANIMATION);
	this->PlayAnimation(AnimationType::STANDING);
}

void Percival::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{

	if (_state[1] != STATE_FALLING && _state[1] != STATE_HITTED && _state[1] != STATE_GETUP)
	{
		if (_state[1] == STATE_STANDING || _state[1] == STATE_WALKING)
		{
			if (kc == EventKeyboard::KeyCode::KEY_A)
			{

				this->setScaleX(-2.0f);
				direct = Direction::LEFT;
				if (_state[1] == STATE_STANDING)
				{
					SetState(_State::STATE_WALKING);
				}
				this->_Physicbody->setVelocity(Vec2(-VELOCITY_VALUE_X, 0));
			
			}
			else if (kc == EventKeyboard::KeyCode::KEY_S)
			{

				
				direct = Direction::BOT;
				if (_state[1] == STATE_STANDING)
				{
					SetState(_State::STATE_WALKING);
				}

				this->_Physicbody->setVelocity(Vec2(0, -VELOCITY_VALUE_Y));
			}
			else if (kc == EventKeyboard::KeyCode::KEY_D)
			{
				direct = Direction::RIGHT;
				
				this->setScaleX(2.0f);
				if (_state[1] == STATE_STANDING)
				{
					SetState(_State::STATE_WALKING);
				}
				this->_Physicbody->setVelocity(Vec2(VELOCITY_VALUE_X, 0));
			}
			else if (kc == EventKeyboard::KeyCode::KEY_W)
			{
				direct = Direction::TOP;
				
				if (_state[1] == STATE_STANDING)
				{
					SetState(_State::STATE_WALKING);
				}
				this->_Physicbody->setVelocity(Vec2(0, VELOCITY_VALUE_Y));
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
	}

}

void Percival::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{

	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		

		if (direct == Direction::LEFT)
		{
			direct = Direction::MIDLE;
			_Physicbody->setVelocity(Vec2(0, 0));
			if (/*_checkwalk == 0 &&*/ _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
			{
				SetState(_State::STATE_STANDING);
			}
		}



	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{

		
		if (direct == Direction::BOT)
		{
			direct = Direction::MIDLE;
			_Physicbody->setVelocity(Vec2(0, 0));
			if (/*_checkwalk == 0 &&*/ _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
			{
				SetState(_State::STATE_STANDING);
			}

		}

	}
	else if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		
		if (direct == Direction::RIGHT)
		{
			direct = Direction::MIDLE;
			_Physicbody->setVelocity(Vec2(0, 0));
			if (/*_checkwalk == 0 &&*/ _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
			{
				SetState(_State::STATE_STANDING);
			}
		}

	}
	else if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		
		if (direct == Direction::TOP)
		{
			direct = Direction::MIDLE;
			_Physicbody->setVelocity(Vec2(0, 0));
			if (/*_checkwalk == 0 &&*/ _state[1] != STATE_JUMPING && _state[1] != STATE_ATTACKING)
			{
				SetState(_State::STATE_STANDING);
			}
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
				int _chem = experimental::AudioEngine::play2d("Sound/chemm.mp3");
				auto hit = Hit::create();
				hit->setScaleX(1.2f);
				hit->setScaleY(2.0f);
				this->addChild(hit);
				hit->setTag(TAG_ATTACK_PERCIVAL);
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
			if (direct == Direction::LEFT)
			{
				this->_physicsBody->setVelocity(Vec2(-VELOCITY_VALUE_X, 0));
			}
			else if (direct == Direction::RIGHT)
			{
				this->_physicsBody->setVelocity(Vec2(VELOCITY_VALUE_X, 0));
			}
			else if (direct == Direction::TOP)
			{
				this->_physicsBody->setVelocity(Vec2(0, VELOCITY_VALUE_Y));
			}
			else if (direct == Direction::BOT)
			{
				this->_physicsBody->setVelocity(Vec2(0, -VELOCITY_VALUE_Y));
			}
			else
			{
				this->_physicsBody->setVelocity(Vec2(0, 0));
				this->SetState(STATE_STANDING);
			}

		}
		break;
		case STATE_HITTED:
		{
			_Physicbody->setVelocity(Vec2(0, 0));
			this->PlayAnimation(AnimationType::HITTED);
		}
		break;
		case STATE_FALLING:
		{
			this->setDeathLess(true);
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::FALLING);
			}), cocos2d::JumpBy::create(3 / 4.0f, Vec2(-100, 0), 50, 1), NULL);
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

void Percival::update(float delta)
{

}


void Percival::takeDamage(float dmg,int n)
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
	else if (_state[1] == STATE_LEVELUP)
	{
		this->SetState(STATE_STANDING);
	}
}



void Percival::PlayAnimation(AnimationType type)
{
	AnimationInfo info = s_mapAnimations.at(type);
	Animation* animation = Animation::create();

	for (int i = 1; i <= info.numFrame; i++)
	{
		std::string name = StringUtils::format(info.filePath.c_str(),_Level, i);
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


