#include"UIGameScene.h"
USING_NS_CC;


using namespace cocos2d::ui;

UIGameScene::UIGameScene()
{
}

UIGameScene::~UIGameScene()
{
}

bool UIGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	_winSize = Director::getInstance()->getWinSize();
	auto size = Size(40, 50);
	_Avatarp1 = cocos2d::Sprite::createWithSpriteFrameName("Arthur_0_avatar.png");
	
	float ScaleX = size.width / _Avatarp1->getContentSize().width;
	float ScaleY = size.height / _Avatarp1->getContentSize().height;
	_Avatarp1->setScaleX(ScaleX);
	_Avatarp1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_Avatarp1->setScaleY(ScaleY);
	_Avatarp1->setPosition(Vec2(10, _winSize.height*0.9));
	//10, _winSize.height*0.9
	this->addChild(_Avatarp1);

	//_HPbar1 = Sprite::create("LoadingBar.png");

	return true;
}
