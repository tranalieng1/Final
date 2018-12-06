#include"UIGameScene.h"
#include"score.h"

USING_NS_CC;


using namespace cocos2d::ui;

UIGameScene::UIGameScene()
{
	listLv.push_back(0);//lv0
	listLv.push_back(0);//lv1
	listLv.push_back(1200);//lv2
	listLv.push_back(2500);//lv3
	listLv.push_back(4000);//lv4
	listLv.push_back(6000);//lv5
	listLv.push_back(9000);//lv6
	listLv.push_back(12000);//lv7
	listLv.push_back(15000);//lv8
	listLv.push_back(19000);//lv9

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

	////add avatar
	_winSize = Director::getInstance()->getWinSize();
	Size winSize = Director::getInstance()->getWinSize();
	auto _Bg = Sprite::create("images/bg.png");
	this->addChild(_Bg);
	_Bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_Bg->setPosition(Vec2(0, _winSize.height*0.85));
	float scaleX = winSize.width*0.4 / (_Bg->getContentSize().width);
	float scaleY = winSize.height*0.15 / (_Bg->getContentSize().height);
	_Bg->setScaleX(scaleX);
	_Bg->setScaleY(scaleY);
	// Số lv
	labelLV = Label::createWithTTF("1", "fonts/a.ttf", 12);
	labelLV->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelLV->setPosition(Vec2(155, _winSize.height*0.858));
	this->addChild(labelLV);
	// Số điểm lên lv
	labelScore = Label::createWithTTF("1200", "fonts/a.ttf", 12);
	labelScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelScore->setPosition(Vec2(290, _winSize.height*0.858));
	this->addChild(labelScore);

	//add score
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/numbers.plist", "images/numbers.png");
	_Score = Score::create();
	_Score->setscore(_totalScore);
	this->addChild(_Score);


	// set cai ruot hp
	_HP1 = ui::LoadingBar::create("images/hp.png");
	//_HP1->setScaleX(scaleX);
	_HP1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//_HP1->setScaleY(scaleY);
	_HP1->setPosition(Vec2(145, _winSize.height*0.895));
	_HP1->setPercent(100);
	this->addChild(_HP1,3);
	//add ruot Mana
	_ManaBar = ui::LoadingBar::create("images/mp.png");
	//_ManaBar->setScaleX(scaleX);
	_ManaBar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//_ManaBar->setScaleY(scaleY);
	_ManaBar->setPosition(Vec2(145, _winSize.height*0.875));
	_ManaBar->setPercent(100);
	this->addChild(_ManaBar,4);
	//add Số mạng
	auto labelLife = Label::createWithTTF("01", "fonts/a.ttf", 18);
	labelLife->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelLife->setPosition(Vec2(180, _winSize.height*0.94));
	this->addChild(labelLife);

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

void UIGameScene::updatePlayer(Player * player)
{
	if (player != nullptr)
	{
		this->setScore(player->getScore());
		_HP1->setPercent(player->getHealth());// day la set mau cua nhan vat khi bi enemy danh
		updateLevel(player);
		
		labelLV->setString(std::to_string(player->getLevel()));
	}
}

void UIGameScene::updateLevel(Player * player)
{
	if (player->getScore() >= this->listLv[player->getLevel()+1])
	{
		player->LevelUp();
		labelScore->setString(std::to_string((int)this->listLv[player->getLevel() + 1]));
	}
}
