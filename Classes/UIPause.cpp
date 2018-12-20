#include "UIPause.h"
USING_NS_CC;
UIPause::UIPause()
{

}

UIPause::~UIPause()
{

}

bool UIPause::init()
{
	winSize = Director::getInstance()->getWinSize();

	if (!Layer::init())
		return false;
	_backgroundSpr = Sprite::create("UI/bg.png");
	_backgroundSpr->setPosition(winSize*0.5);
	_backgroundSpr->setScaleY(0.3f);
	_backgroundSpr->setScaleX(0.2f);
	this->addChild(_backgroundSpr, 1);
	
	_resumeBtn = MenuItemImage::create("UI/resumebtn.png", "UI/resumebtn1.png", CC_CALLBACK_1(UIPause::ResumeEvent, this));
	_resumeBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.62f));
	_resumeBtn->setScale(0.5f);
	
	_upgradeBtn = MenuItemImage::create("UI/upgradebtn.png", "UI/upgradebtn1.png", CC_CALLBACK_1(UIPause::goToUpgradeScene, this));
	_upgradeBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
	_upgradeBtn->setScale(0.5f);

	_optionBtn = MenuItemImage::create("UI/Optionsbtn.png", "UI/Optionsbtn1.png", CC_CALLBACK_1(UIPause::goToOptionScene, this));
	_optionBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.38f));
	_optionBtn->setScale(0.5f);

	menu1 = Menu::create(_resumeBtn, _upgradeBtn, _optionBtn, NULL);
	menu1->setPosition(Vec2::ZERO);
	//menu1->setScale(0.5f);
	this->addChild(menu1, 2);
	return true;
}

void UIPause::goToUpgradeScene(cocos2d::Ref * pSender)
{
}

void UIPause::goToOptionScene(cocos2d::Ref * pSender)
{
}

void UIPause::ResumeEvent(cocos2d::Ref * pSender)
{
}
