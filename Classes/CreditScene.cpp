#include "CreditScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

CreditScene::CreditScene()
{
}

CreditScene::~CreditScene()
{
}

Scene* CreditScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CreditScene::create();
	scene->addChild(layer);
	return scene;
}

bool CreditScene::init()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	if (!Scene::init())
		return false;

	auto sprite = Sprite::create("Credit.png");
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	sprite->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.2));
	this->addChild(sprite);
	auto moveup = MoveBy::create(4, Vec2(0, 400));
	auto seq = Sequence::create(moveup,DelayTime::create(2.0f), CallFunc::create([=]()
	{
		this->goToMenuScene();
	}),NULL);
	sprite->runAction(seq);
	return true;
}

void CreditScene::goToMenuScene()
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}
