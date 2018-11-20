#ifndef __GAMESCENE1_H__
#define __GAMESCENE1_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"

class UIGameScene : public cocos2d::Layer
{
public:

	UIGameScene();
	~UIGameScene();
	virtual bool init();
	
	CREATE_FUNC(UIGameScene);



private:
	

	cocos2d::Sprite * _Avatarp1;
	cocos2d::Sprite * _Avatarp2;
	cocos2d::Sprite *_HPbar1;
	cocos2d::Sprite *_HPbar2;

	cocos2d::ui::LoadingBar *_HP1;
	cocos2d::ui::LoadingBar *_HP2;

	cocos2d::Size _winSize;

	
};


#endif //G__GAMESCENE1_H__

