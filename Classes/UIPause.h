#ifndef __UI_PAUSE_H__
#define __UI_PAUSE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class UIPause: public cocos2d::Layer
{
public:
	UIPause();
	~UIPause();
	CREATE_FUNC(UIPause);
	virtual bool init() override;
	void goToUpgradeScene(cocos2d::Ref * pSender);
	void goToOptionScene(cocos2d::Ref* pSender);

private:
	cocos2d::Size winSize;
	cocos2d::MenuItemImage *_upgradeBtn;
	cocos2d::MenuItemImage *_optionBtn;
	cocos2d::MenuItemImage *_resumeBtn;
	cocos2d::Sprite * _backgroundSpr;
	cocos2d::Menu *menu1;


};



#endif // !__UI_PAUSE_H__
