#include "test.h"
USING_NS_CC;

Test::Test()
{
}

Test::~Test()
{
}

Scene* Test::createScene()
{
	auto scene = Scene::create();
	auto layer = Test::create();
	scene->addChild(layer);
	return scene;
}

bool Test::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if(!Scene::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FatMan.plist", "FatMan.png");
	auto sprite = Sprite::createWithSpriteFrameName("FatMan_attack1_2.png");
	sprite->setPosition(visibleSize*0.5);
	float temp1 = sprite->getContentSize().width;
	float temp2 = sprite->getContentSize().height;
	//sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	sprite->setScale(3.0f);
	auto sprite2 = Sprite::createWithSpriteFrameName("FatMan_icon.png");
	sprite2->setPosition(visibleSize*0.5);
	sprite2->setScale(0.3f);
	this->addChild(sprite2, 3);
	this->addChild(sprite,2);
	return true;

}
