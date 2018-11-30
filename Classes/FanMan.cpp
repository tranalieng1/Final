#include "FanMan.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;

std::map<AnimationType, AnimationInfo> FanMan::s_mapAnimations =
{
	{AnimationType::WALKING, AnimationInfo(4, "%d.png", 1.0f / 12.0f, CC_REPEAT_FOREVER)},
	{ AnimationType::ATTACKING, AnimationInfo(4, "%d.png", 1.0f / 12.0f, 1) },
	{AnimationType::HITTED,AnimationInfo(1,"FatMan_stand_%d.png", 1.0f / 4.0f,1)},
	{AnimationType::DEATH,AnimationInfo(4,"FatMan_fall_%d.png",1.0f/12.0f,1)},
};
FanMan::~FanMan()
{

}

FanMan::FanMan()
{
	_MaxHealth = 50;
	_Health = _MaxHealth;
	//_state.resize(2);
	_state.push_back(_State::STATE_STANDING);
	_state.push_back(_State::STATE_STANDING);
}



void FanMan::Attack()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("FatMan_attack1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 /12);//1:12

	Animate* animate = Animate::create(animation);
	_EnemySprite->runAction(RepeatForever::create(animate));
}

bool FanMan::init()
{
	if (!Node::init())
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
	_physicsBody->setDynamic(false);
	_physicsBody->setRotationEnable(false);
	_physicsBody->setCategoryBitmask(FATMAN_CATEGORY_BITMASK);
	_physicsBody->setCollisionBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
	_physicsBody->setContactTestBitmask(FATMAN_COLLISION_AND_CONTACT_TEST_BITMASK);
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
	_EnemySprite->setSpriteFrame("FatMan_stand_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), this->getContentSize().height*PLAYER_JUMP, 1);
	this->runAction(_Jump);
}

void FanMan::Attack1Animation()
{

	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("FatMan_attack1_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("FatMan_stand_1.png"));
	animation->setDelayPerUnit(1 / 20.0f);

	Animate* animate = Animate::create(animation);
	//_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(animate);

}

void FanMan::WalkAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		std::string name = StringUtils::format("FatMan_walk_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_WalkAction = RepeatForever::create(animate);
	_EnemySprite->runAction(_WalkAction);
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
	if (type == AnimationType::HITTED)
	{
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	Animate* animate = Animate::create(animation);
	auto seq = Sequence::create(Repeat::create(animate, info.loopTime), CallFunc::create([=]()
	{
		//if (type == AnimationType::ATTACKING)
		//_PlayerSprite->setSpriteFrame("Arthur_0_stand_1.png");
		if (type != AnimationType::DEATH)
		{
			this->onFinishAnimation();
		}
	}), NULL);

	seq->setTag(TAG_ANIMATION);
	_EnemySprite->stopActionByTag(TAG_ANIMATION);
	_EnemySprite->runAction(seq);
}

void FanMan::SetState(_State state)
{
	cocos2d::Action *jum;
	cocos2d::Spawn *spawn;
	if (_state[1] != state)
	{
		/*_hit->setVisible(false);*/
		_state[0] = _state[1];
		_state[1] = state;

		switch (state)
		{
		case STATE_ATTACKING:
			break;
		case STATE_JUMPING:
			break;
		case STATE_STANDING:
			this->StopAction();
			break;
		case STATE_WALKING:
			break;
		case STATE_HITTED:
			this->PlayAnimation(AnimationType::HITTED);
		

			break;
		case STATE_DEATH:
			/*this->PlayAnimation(AnimationType::DEATH);*/
			jum = cocos2d::JumpBy::create(0.8f, Vec2(100, 0), 50, 1);
			spawn = cocos2d::Spawn::create(CallFunc::create([=]()
			{
				this->PlayAnimation(AnimationType::DEATH);
			}), jum, NULL);
			//this->runAction(jum);
			this->runAction(spawn);
			
			break;
		default:
			break;
		}
	}
}

void FanMan::takeDamage(float dmg)
{
	_Health = _Health - dmg;
	_HealthBar->setPercent((_Health / _MaxHealth)*100);
	if (_Health > 0)
	{
		this->SetState(STATE_HITTED);
	}
	else
	{
		this->SetState(STATE_DEATH);
	}
}

void FanMan::onFinishAnimation()
{
	if (_state[1] == STATE_HITTED)
	{
		this->SetState(_state[0]);
	}
}
