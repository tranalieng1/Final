#include"UIGameScene.h"
#include"score.h"
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
	//add avatar
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	_winSize = Director::getInstance()->getWinSize();
	auto size = Size(70, 80);
	_Avatarp1 = cocos2d::Sprite::createWithSpriteFrameName("Arthur_0_avatar.png");
	
	float ScaleX = size.width / _Avatarp1->getContentSize().width;
	float ScaleY = size.height / _Avatarp1->getContentSize().height;
	_Avatarp1->setScaleX(ScaleX);
	_Avatarp1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_Avatarp1->setScaleY(ScaleY);
	_Avatarp1->setPosition(Vec2(0, _winSize.height*0.9));
	//10, _winSize.height*0.9
	this->addChild(_Avatarp1);
	//add score
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/numbers.plist", "images/numbers.png");
	_Score = Score::create();
	_Score->setscore(_totalScore);
	this->addChild(_Score);


	//add HP
	_HealthBar1 = ui::LoadingBar::create("HP.png");
	_HealthBar1->setScaleX(ScaleX);
	_HealthBar1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_HealthBar1->setScaleY(ScaleY);
	_HealthBar1->setPosition(Vec2(70, _winSize.height*0.93));
	_HealthBar1->setPercent(100);
	this->addChild(_HealthBar1);
	//add Mana
	_ManaBar = ui::LoadingBar::create("Mana.png");
	_ManaBar->setScaleX(ScaleX);
	_ManaBar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_ManaBar->setScaleY(ScaleY);
	_ManaBar->setPosition(Vec2(70, _winSize.height*0.9));
	_ManaBar->setPercent(100);
	this->addChild(_ManaBar);
	//add lv
	//_Level = Sprite::createWithSpriteFrameName("images/Lv.png");

	//
	//_Level->setPosition(Vec2(_winSize.width*0.5, _winSize.height*0.5));
	//_Level->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//_Level->setScale(0.5f);

	//this->addChild(_Level);
	//_HPbar1 = Sprite::create("LoadingBar.png");

	return true;
}
void UIGameScene::scoreChange()
{
	_totalScore = _totalScore + 100;
	_Score->setscore(_totalScore);
}

void UIGameScene::setScore(float temp)
{
	_totalScore = (int)temp;
	_Score->setscore(_totalScore);
}
