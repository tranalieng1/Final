#ifndef _GAMEOPTIONS_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class GameOptions : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	int				_musicOptions;
	virtual bool init();
#define TRANSITTION_TIME 0.5
	void onTouchBegan(Ref *senser, cocos2d::ui::Widget::TouchEventType type);
	//void onTouchBegan_2(Ref *senser, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(GameOptions);
private:
	void CombackMainMenuScene(cocos2d::Ref *sender);

	cocos2d::ui::Button *soundbutton;
	cocos2d::ui::Button *musicbutton;
};


#endif // !_GAMEOPTIONS_H
