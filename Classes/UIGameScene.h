#ifndef _UI_GAME_SCENE_H
#define _UI_GAME_SCENE_H
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Score.h"
class UIGameScene : public cocos2d::Layer
{
public:

	UIGameScene();
	~UIGameScene();
	virtual bool init();
	
	CREATE_FUNC(UIGameScene);
	void scoreChange();
	void setScore(float temp);


private:
	

	cocos2d::Sprite * _Avatarp1;
	cocos2d::Sprite * _Level;
	cocos2d::Sprite *_HPbar1;
	cocos2d::Sprite *_HPbar2;
	Score* _Score;

	cocos2d::ui::LoadingBar *_HP1;
	cocos2d::ui::LoadingBar *_HP2;

	cocos2d::Size _winSize;
protected:
	cocos2d::ui::LoadingBar* _HealthBar1;
	cocos2d::ui::LoadingBar* _ManaBar;
	
	int _totalScore = 0;
};


#endif //_UI_GAME_SCENE_H

