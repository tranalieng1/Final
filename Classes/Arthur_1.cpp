#include "Arthur_1.h"
#include "cocos2d.h"
#include"Defnition.h"
USING_NS_CC;



Arthur_1::~Arthur_1()
{

}

Arthur_1::Arthur_1()
{
	_checkwalk = 0;
	_velocityX = 0;
	_velocityY = 0;
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
	_PlayerSprite->runAction(RepeatForever::create(animate));
}

bool Arthur_1::init()
{
	if (!Node::init())
		return false;
	_state = STATE_STANDING;
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

	//Setbody
	_Physicbody = cocos2d::PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody(_Physicbody);
	_Physicbody->setDynamic(false);
	_Physicbody->setGravityEnable(false);
	_Physicbody->setRotationEnable(false);
	_Physicbody->setCategoryBitmask(ARTHUR_CATEGORY_BITMASK);
	_Physicbody->setCollisionBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
	_Physicbody->setContactTestBitmask(ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK);
	
	
	return true;
}

void Arthur_1::Jump()
{
	//_ArthurSprite->setSpriteFrame("Arthur_0_stand_1.png");
	_PlayerSprite->stopAllActions();
	_PlayerSprite->setSpriteFrame("Arthur_0_jump_1.png");
	_Jump = JumpBy::create(1.0f, Vec2(0.0f,0.0f),  this->getContentSize().height*PLAYER_JUMP, 1);
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
	_PlayerSprite->runAction(animate);
	
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
	_PlayerSprite->runAction(_WalkAction);
	_WalkAction->setTag(1);
}

void Arthur_1::StopAction()
{
	_PlayerSprite->stopActionByTag(1);
	
	_PlayerSprite->setSpriteFrame("Arthur_0_stand_1.png");
}


void Arthur_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	//switch (this->_state)
	//{
	//case STATE_ATTACKING:
	//	break;
	//case STATE_JUMPING:
	//	break;
	//case STATE_STANDING:
	//	if (kc == EventKeyboard::KeyCode::KEY_D)
	//	{

	//		//_Arthur->setScaleX(2.0f);
	//		if (_checkwalk == 0)
	//			this->WalkAnimation();
	//		moveright = true;

	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_A)
	//	{
	//		//_Arthur->setScaleX(-2.0f);

	//		moveleft = true;
	//		if (_checkwalk == 0)
	//			this->WalkAnimation();
	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_S)
	//	{
	//		movedown = true;
	//		if (_checkwalk == 0)
	//			this->WalkAnimation();
	//		_checkwalk++;
	//	}
	//	if (kc == EventKeyboard::KeyCode::KEY_W)
	//	{
	//		moveup = true;
	//		if (_checkwalk == 0)
	//			this->WalkAnimation();
	//		_checkwalk++;
	//	}
	//	else if (kc == EventKeyboard::KeyCode::KEY_K)
	//	{

	//		this->Attack1Animation();
	//		this->SetState(STATE_ATTACKING);
	//		//_Arthur->StopAction();
	//	}
	//	else if (kc == EventKeyboard::KeyCode::KEY_J)
	//	{

	//	/*	moonblade->setPosition(Vec2(_Arthur->getPositionX() + _Arthur->getContentSize().width / 2 + 20, _Arthur->getPositionY() + +10));
	//		moonblade->setVisible(true);
	//		moonblade->flySkill();*/
	//	}
	//	else if (kc == EventKeyboard::KeyCode::KEY_L)
	//	{
	//		/*if (CheckJump(_Arthur, _nodePosPlayer) == true)
	//		{*/
	//		this->Jump();
	//		this->SetState(STATE_JUMPING);
	//		/*}*/
	//	}
	//	break;
	//case STATE_WALKING:
	//	break;
	//default:
	//	break;
	//}

	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		this->setScaleX(-2.0f);
		if(_checkwalk==0)
			this->WalkAnimation();
		_checkwalk++;
		_velocityX -= VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{
		_velocityY -= VELOCITY_VALUE_Y;
		if (_checkwalk == 0)
			this->WalkAnimation();
		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		this->setScaleX(2.0f);
		_velocityX += VELOCITY_VALUE_X;
		if (_checkwalk == 0)
			this->WalkAnimation();
		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		_velocityY += VELOCITY_VALUE_Y;
		if (_checkwalk == 0)
			this->WalkAnimation();
		_checkwalk++;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
	}
	else if (kc == EventKeyboard::KeyCode::KEY_K)
	{
		this->Attack1Animation();
	}

}

void Arthur_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event * event)
{
	if (kc == EventKeyboard::KeyCode::KEY_A)
	{
		_velocityX += VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			this->StopAction();

		
	}
	else if (kc == EventKeyboard::KeyCode::KEY_S)
	{
		_velocityY += VELOCITY_VALUE_Y;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			this->StopAction();
		
	}
	else if (kc == EventKeyboard::KeyCode::KEY_D)
	{
		_velocityX -= VELOCITY_VALUE_X;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			this->StopAction();
		
	}
	else if (kc == EventKeyboard::KeyCode::KEY_W)
	{
		_velocityY -= VELOCITY_VALUE_Y;
		this->_Physicbody->setVelocity(Vec2(_velocityX, _velocityY));
		_checkwalk--;
		if (_checkwalk == 0)
			this->StopAction();
		
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

