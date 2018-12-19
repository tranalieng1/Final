#include "FanMan.h"
#include "cocos2d.h"
#include"Defnition.h"
#include"Hit.h"
#include "GameScene_1.h"
USING_NS_CC;

#define TAG_ACTION_AI_CHASE_PLAYER 100
#define SPEED_X 150.0f
#define SPEED_Y SPEED_X
#define TIME_UPDATE_AI 0.2f

std::map<AnimationType, AnimationInfo> FanMan::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "FatMan_walk_%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(1, "FatMan_attack1_%d.png", 1.0f/4.0f,2 ) },
	{ AnimationType::PREATTACKING, AnimationInfo(1, "FatMan_preattack1_%d.png", 1.0f / 4.0f, 2) },
	{AnimationType::HITTED,AnimationInfo(1,"FatMan_stand_%d.png", 1.0f / 4.0f,2)},
	{AnimationType::DEATH,AnimationInfo(4,"FatMan_fall_%d.png",1.0f/4.0f,1)},
	{AnimationType::FALLING,AnimationInfo(4,"FatMan_fall_%d.png",1.0f / 4.0f,1)},
	{AnimationType::GETUP,AnimationInfo(2,"FatMan_defeat_%d.png",1.0f / 4.0f,1)},
	
};
FanMan::~FanMan()
{

}

FanMan::FanMan() : Enemy()
{
	_MaxHealth = 200;
	_Health = _MaxHealth;
	//_state.resize(2);
	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);
	_timeUpdateAI = TIME_UPDATE_AI;
	_score = 300.f;
	_damage = 20;
}





bool FanMan::init()
{
	if (!Enemy::init())
		return false;
	//Set sprite
	//_state[2] = STATE_STANDING;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FatMan.plist", "FatMan.png");
	_EnemySprite = Sprite::createWithSpriteFrameName("FatMan_default_3.png");
	this->addChild(_EnemySprite);
	_EnemySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_EnemySprite->getContentSize().width,_EnemySprite->getContentSize().height-20));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_EnemySprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
	this->setScale(2.0);
	//Set physicbody
	_physicsBody = PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_physicsBody);
	_physicsBody->setGravityEnable(false);
	_physicsBody->setDynamic(true);
	_physicsBody->setRotationEnable(false);
	
	_physicsBody->setCategoryBitmask(ENEMY_CATE);
	_physicsBody->setCollisionBitmask(ENEMY_COLL);
	_physicsBody->setContactTestBitmask(ENEMY_COLL);
	this->setTag(TAG_CREEP);
	//Set HPbar
	_HealthBar = ui::LoadingBar::create("hp_bar.png");
	_HealthBar->setPosition(Vec2(this->getContentSize().width * 0.5f, -5.0f));
	_HealthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	_HealthBar->setScaleX(0.3f);
	_HealthBar->setScaleY(0.5f);
	_HealthBar->setPercent(100);
	this->addChild(_HealthBar);
	return true;
}

void FanMan::Jump()
{
}

void FanMan::Attack1Animation()
{
	
}

void FanMan::WalkAnimation()
{
}







void FanMan::StopAction()
{
	//_Physicbody->setVelocity(Vec2(0, 0));
	_EnemySprite->stopActionByTag(TAG_ANIMATION);
	_EnemySprite->setSpriteFrame("FatMan_default_3.png");
}

void FanMan::onContactBeganWith(GameObject * obj)
{
	/*if (obj->getTag() == TAG_ARTHUR)
	{
		this->setVisible(false);
	}*/
}

void FanMan::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{

}

void FanMan::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void FanMan::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void FanMan::PlayAnimation(AnimationType type)
{
	AnimationInfo info = s_mapAnimations.at(type);
	Animation* animation = Animation::create();
	std::string name = "";
	for (int i = 1; i <= info.numFrame; i++)
	{
		name = StringUtils::format(info.filePath.c_str(), i);
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
	_EnemySprite->stopActionByTag(TAG_ANIMATION);
	_EnemySprite->runAction(seq);
}

void FanMan::SetState(_State state)
{

	cocos2d::Spawn *spawn;
	if (_state[1] != state)
	{
		/*_hit->setVisible(false);*/
		_state[0] = _state[1];
		_state[1] = state;

		switch (state)
		{
		case STATE_PREATTACKING:
			this->setDeathLess(false);
			this->PlayAnimation(AnimationType::PREATTACKING);
			break;
		case STATE_ATTACKING:
			/*this->runAction(Sequence::create(DelayTime::create(0.4f), CallFunc::create([=]()
			{*/
			
		{
			auto hit = Hit::create();
			this->addChild(hit);
			hit->setScaleX(2.0f);
			hit->setTag(TAG_ATTACK_ENEMY);
			hit->setDamage(_damage);
			hit->setcollisin(HIT_ENEMY_COLL);
			hit->setcatory(HIT_ENEMY_CATE);
			hit->setPosition(Vec2(-2 * this->getContentSize().width, this->getContentSize().height * 0.5f - 10));
			hit->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([=]()
			{
				hit->removeFromParent();
			}), nullptr));
		}
			/*}), NULL));*/

			//this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
			//this->SetState(STATE_STANDING);
			/*this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::ATTACKING);
			}), NULL));*/
			this->PlayAnimation(AnimationType::ATTACKING);
			break;
		case STATE_JUMPING:
			break;
		case STATE_STANDING:
			this->setDeathLess(false);
			this->StopAction();
			break;
		case STATE_WALKING:
			this->PlayAnimation(AnimationType::WALKING);
			this->chasePlayer();
			break;
		case STATE_HITTED:
			this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
			this->PlayAnimation(AnimationType::HITTED);


			break;
		case STATE_DEATH:
			this->setDeathLess(true);
			/*this->PlayAnimation(AnimationType::DEATH);*/
			this->_Arthurptr->addScore(_score);
			this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::DEATH);
			}), cocos2d::JumpBy::create(0.8f, Vec2(100, 0), 50, 1), cocos2d::Blink::create(1.2f, 10), NULL);
			//this->runAction(jum);
			this->runAction(Sequence::create(spawn, DelayTime::create(0.5f), RemoveSelf::create(), NULL));
			scene->dieenemy();
			break;
		case STATE_FALLING:
			if (this->getScaleX() > 0)
			{
				_jumph = 100.f;
			}
			else
			{
				_jumph = -100.f;
			}
			this->setDeathLess(true);
			this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::DEATH);
			}), cocos2d::JumpBy::create(0.8f, Vec2(_jumph, 0), 50, 1), NULL);
			this->runAction(spawn);
			break;
		case STATE_GETUP:
			this->setDeathLess(true);
			this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
			this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::GETUP);
			}), NULL));
			break;
		default:
			break;
		}
	}
}


void FanMan::takeDamage(float dmg, int temp)
{
	_Health = _Health - dmg;
	_HealthBar->setPercent((_Health / _MaxHealth) * 100);
	if(this->_state[1]==STATE_HITTED)
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

void FanMan::onFinishAnimation()
{
	if (_state[1] == STATE_HITTED)
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
	else if (_state[1] == STATE_WALKING)
	{
		//this->stopAllActions();
		SetState(STATE_STANDING);
	}
	else if (_state[1] == STATE_ATTACKING)
	{
		
		this->SetState(STATE_STANDING);
	}
	else if (_state[1] == STATE_PREATTACKING)
	{
		this->SetState(STATE_ATTACKING);
	}
}

void FanMan::scheduleUpdateAI(float delta)
{
	
	if (_Arthurptr != nullptr)
	{
		
		if (_state[1] == STATE_FALLING || _state[1] == STATE_DEATH || _state[1] == STATE_HITTED
			|| _state[1] == STATE_GETUP || _state[1] == STATE_ATTACKING)
		{

		}
		else
		{
			if (this->getPosition().x > _Arthurptr->getPosition().x)
			{
				this->setScaleX(2.0f);
			}
			else
			{
				this->setScaleX(-2.0f);
			}
			auto distanceX = std::abs(this->getPosition().x - _Arthurptr->getPosition().x);
			auto distanceY = std::abs(this->getPosition().y - _Arthurptr->getPosition().y);
			if (distanceX < _EnemySprite->getContentSize().width * 0.5f + 100.0f && distanceY<50 )
			{
				/*if (this->_state[1] != STATE_ATTACKING)
				{*/
					//this->PlayAnimation(AnimationType::ATTACKING);
					this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
					this->SetState(STATE_PREATTACKING);
				/*}*/
			}
			else
			{
				this->SetState(STATE_WALKING);
				chasePlayer();
			}
		}
		
	}
}

void FanMan::update(float delta)
{
}

void FanMan::chasePlayer()
{

	
	auto targetPos = _Arthurptr->getPosition();
	auto distance = targetPos - this->getPosition();
	auto timeX = std::abs(distance.x / SPEED_X);
	auto timeY = std::abs(distance.y / SPEED_Y);
	auto time = timeX > timeY ? timeX : timeY;
	auto aMove = MoveBy::create(time, distance);
	aMove->setTag(TAG_ACTION_AI_CHASE_PLAYER);
	this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
	this->runAction(aMove);
}
