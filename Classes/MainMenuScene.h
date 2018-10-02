#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class MainMenuScene : public cocos2d::Layer
{
public:

	MainMenuScene();
	~MainMenuScene();
	static cocos2d::Scene *createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	
	CREATE_FUNC(MainMenuScene);
private:
	//void onTouchBegan_PlayButton(Ref *sender, cocos2d::ui::Widget::TouchEventType *type);
	cocos2d::MenuItemImage * _Playgame_button;
	cocos2d::Menu *menu;
	
	void GotoGameScene(Ref *sender);
};


#endif // !__SPLASHSCENE_H__

