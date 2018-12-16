#include "Garibaldi.h"
#include "Defnition.h"
#include "Hit.h"

USING_NS_CC;
#define TAG_ACTION_AI_CHASE_PLAYER 100
#define SPEED_X 150.0f
#define SPEED_Y SPEED_X
#define TIME_UPDATE_AI 0.2f

std::map<AnimationType, AnimationInfo> Garibaldi::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "Garibaldi_walk_%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(2, "Garibaldi_attack_%d.png", 1.0f / 4.0f, 1) },
	{AnimationType::HITTED,AnimationInfo(1,"Garibaldi_hitted_%d.png", 1.0f / 4.0f,2)},
	{AnimationType::DEATH,AnimationInfo(2,"Garibaldi_fall_%d.png",1.0f / 4.0f,1)},
	{AnimationType::FALLING,AnimationInfo(2,"Garibaldi_fall_%d.png",1.0f / 4.0f,1)},
	{AnimationType::GETUP,AnimationInfo(2,"Garibaldi_getup_%d.png",1.0f / 4.0f,1)},

};
Garibaldi::Garibaldi()
{
	_MaxHealth = 1000;
	_Health = _MaxHealth;
	//_state.resize(2);
	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);
	_timeUpdateAI = TIME_UPDATE_AI;
	_score = 200.f;
	_damage = 20;
}

Garibaldi::~Garibaldi()
{
}

void Garibaldi::Attack()
{
}

bool Garibaldi::init()
{
	if (!Boss::init())
		return false;
	//Set sprite
	//_state[2] = STATE_STANDING;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boss.plist", "Boss.png");
	_BossSprite = Sprite::createWithSpriteFrameName("Garibaldi_stand_1.png");
	this->addChild(_BossSprite);
	_BossSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setContentSize(Size(_BossSprite->getContentSize().width-40, _BossSprite->getContentSize().height - 20));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_BossSprite->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.0f));
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
	_HealthBar = ui::LoadingBar::create("hp_bar.png");
	_HealthBar->setPosition(Vec2(this->getContentSize().width * 0.5f, -5.0f));
	_HealthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	_HealthBar->setScaleX(1.0f);
	_HealthBar->setScaleY(0.8f);
	_HealthBar->setPercent(100);
	this->addChild(_HealthBar);
	return true;
}

void Garibaldi::Jump()
{

}

void Garibaldi::Attack1Animation()
{
}

void Garibaldi::WalkAnimation()
{
}

void Garibaldi::StopAction()
{
	_BossSprite->stopActionByTag(TAG_ANIMATION);
	_BossSprite->setSpriteFrame("Garibaldi_stand_1.png");
}

void Garibaldi::onContactBeganWith(GameObject * obj)
{
}

void Garibaldi::onContactPostSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, const cocos2d::PhysicsContactPostSolve & solve)
{
}

void Garibaldi::onContactPreSolveWith(GameObject * obj, cocos2d::PhysicsContact & contact, cocos2d::PhysicsContactPreSolve & solve)
{
}

void Garibaldi::onContactSeparateWith(GameObject * obj, cocos2d::PhysicsContact & contact)
{
}

void Garibaldi::takeDamage(float dmg,int temp)
{
	_Health = _Health - dmg;
	_HealthBar->setPercent((_Health / _MaxHealth) * 100);
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

void Garibaldi::PlayAnimation(AnimationType type)
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

	if (type == AnimationType::ATTACKING)
	{
		attackdelay = 0.5f;
	}
	else
		attackdelay = 0;
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(Repeat::create(animate, info.loopTime), DelayTime::create(attackdelay), CallFunc::create([=]()
	{
		//if (type == AnimationType::ATTACKING)
		//_PlayerSprite->setSpriteFrame("Arthur_0_stand_1.png");

		this->onFinishAnimation();

	}), NULL);

	seq->setTag(TAG_ANIMATION);
	_BossSprite->stopActionByTag(TAG_ANIMATION);
	_BossSprite->runAction(seq);
}

void Garibaldi::SetState(_State state)
{
	cocos2d::Spawn *spawn;
	if (_state[1] != state)
	{
		/*_hit->setVisible(false);*/
		_state[0] = _state[1];
		_state[1] = state;

		switch (state)
		{
		case STATE_ATTACKING:
			this->runAction(Sequence::create(DelayTime::create(0.4f), CallFunc::create([=]()
			{
				auto hit = Hit::create();
				this->addChild(hit);
				hit->setScaleX(2.0f);
				hit->setTag(TAG_ATTACK_ENEMY);
				hit->setDamage(_damage);
				hit->setcollisin(HIT_ENEMY_COLL);
				hit->setcatory(HIT_ENEMY_CATE);
				hit->setPosition(Vec2(-25, this->getContentSize().height * 0.5f - 10));
				hit->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([=]()
				{
					hit->removeFromParent();
				}), nullptr));
			}), NULL));

			this->stopActionByTag(TAG_ACTION_AI_CHASE_PLAYER);
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
			_Arthurptr->statewin();
			scene->setlockey();
			scene->scheduleOnce(schedule_selector(GameScene_1::goToEndScene2), 4.0f);

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

void Garibaldi::onFinishAnimation()
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
}

void Garibaldi::scheduleUpdateAI(float delta)
{
	if (_Arthurptr != nullptr)
	{

		if (this->getPosition().x > _Arthurptr->getPosition().x)
		{
			this->setScaleX(2.0f);
		}
		else
		{
			this->setScaleX(-2.0f);
		}
		if (_state[1] == STATE_FALLING || _state[1] == STATE_DEATH || _state[1] == STATE_HITTED
			|| _state[1] == STATE_GETUP)
		{

		}
		else
		{


			auto distanceX = std::abs(this->getPosition().x - _Arthurptr->getPosition().x);
			auto distanceY = std::abs(this->getPosition().y - _Arthurptr->getPosition().y);
			if (distanceX < _BossSprite->getContentSize().width * 0.5f + 100.0f && distanceY < 30)
			{
				//this->PlayAnimation(AnimationType::ATTACKING);

				this->SetState(STATE_ATTACKING);
			}
			else
			{
				this->SetState(STATE_WALKING);
				chasePlayer();
			}
		}

	}
}

void Garibaldi::update(float delta)
{
}

void Garibaldi::chasePlayer()
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
