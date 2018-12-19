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

	return true;
}

void UIPause::goToUpgradeScene(cocos2d::Ref * pSender)
{
}

void UIPause::goToOptionScene(cocos2d::Ref * pSender)
{
}
