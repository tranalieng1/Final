#include "EndScene.h"
#include "CreditScene.h"
USING_NS_CC;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

Scene* EndScene::createScene()
{
	auto scene = Scene::create();
	auto layer = EndScene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init()
{
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	if (!Scene::init())
		return false;
	auto background = Sprite::create("Endgame_Background.png");
	float tempx =  visibleSize.width/ background->getContentSize().width ;
	float tempy =   visibleSize.height/ background->getContentSize().height;

	background->setScaleX(tempx);
	background->setScaleY(tempy);
	background->setPosition(visibleSize*0.5f);
	this->addChild(background,0);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PercivalLvl1.plist", "PercivalLvl1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Merlin.plist", "Merlin.png");
	////////////////////////////////////
	_ArthurSprite = Sprite::createWithSpriteFrameName("Arthur_1_stand_1.png");
	_ArthurSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_ArthurSprite->setPosition(Vec2(0, visibleSize.height*0.3));
	_ArthurSprite->setScale(2.0f);
	this->addChild(_ArthurSprite,1);

	
	_ArthurSprite->runAction(RepeatForever::create(createAnimate("Arthur_1_walk_%d.png", 4, 1/8.0f)));
	auto action = MoveBy::create(2.0f, Vec2(300, 0));
	_ArthurSprite->runAction(Sequence::create(action, CallFunc::create([=]()
	{
		_ArthurSprite->stopAllActions();
		_ArthurSprite->setSpriteFrame("Arthur_1_default_3.png");
	}),NULL));

	////////////////////////////////

	_PercivalSprite = Sprite::createWithSpriteFrameName("Percival_1_ default_1.png");
	_PercivalSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_PercivalSprite->setPosition(Vec2(-50, visibleSize.height*0.2));
	_PercivalSprite->setScale(2.0f);
	this->addChild(_PercivalSprite, 3);

	_PercivalSprite->runAction(RepeatForever::create(createAnimate("Percival_1_walk_%d.png", 4, 1 / 8.0f)));
	auto action2 = MoveBy::create(2.0f, Vec2(300, 0));
	_PercivalSprite->runAction(Sequence::create(action2, CallFunc::create([=]()
	{
		_PercivalSprite->stopAllActions();
		_PercivalSprite->setSpriteFrame("Percival_1_getdown_2.png");
	}), NULL));
	//////////////////////////////////////////////////
	_MerlinSprite = Sprite::createWithSpriteFrameName("Merlin_stand.png");
	_MerlinSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_MerlinSprite->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.25));
	_MerlinSprite->setScale(2.0f);
	this->addChild(_MerlinSprite,1);
	/////
	this->scheduleOnce(schedule_selector(EndScene::Message), 2.5f);
	this->scheduleOnce(schedule_selector(EndScene::Invi), 4.5f);
	this->scheduleOnce(schedule_selector(EndScene::goToEndScene), 7.0f);
	return true;

}

void EndScene::Message(float delta)
{
	_Cloud = Sprite::create("cloud.png");
	_Cloud->setPosition(Vec2(visibleSize.width*0.7-20, visibleSize.height*0.25+100));
	_Cloud->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	_Cloud->setScale(0.2f);
	this->addChild(_Cloud,2);

	_label = Label::createWithTTF("Thank for save \n the world", "fonts/arial.ttf", 80);
	_label->setTextColor(Color4B::BLACK);
	//_label->enableOutline(Color4B::BLUE, 1);
	_Cloud->addChild(_label);
	_label->setPosition(Vec2(_Cloud->getContentSize().width*0.5, _Cloud->getContentSize().height*0.5+35));
}

void EndScene::Invi(float delta)
{
	this->_Cloud->setVisible(false);
	auto action = _MerlinSprite->runAction(createAnimate("Merlin_Hide_%d.png", 8, 1 / 8.0f));
	auto seq = Sequence::create(DelayTime::create(0.5f), action, DelayTime::create(1/8.0f), CallFunc::create([=]()
	{
		this->_MerlinSprite->setVisible(false);
	}),NULL);
	this->_MerlinSprite->runAction(seq);


}

void EndScene::goToEndScene(float delta)
{
	auto scene = CreditScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}

Animate * EndScene::createAnimate(std::string s, int n,float f)
{
	std::string temp;
	auto aniamtion = Animation::create();
	for (int i = 1; i <= n; i++)
	{
		temp = StringUtils::format(s.c_str(), i);
		aniamtion->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(temp));
	}
	aniamtion->setDelayPerUnit(f);
	auto animate = Animate::create(aniamtion);
	return animate;
}
