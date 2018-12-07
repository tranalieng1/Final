#ifndef _UI_GAME_SCENE_H
#define _UI_GAME_SCENE_H
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Score.h"
#include "Player.h"
#include <vector>
class UIGameScene : public cocos2d::Layer
{
public:

	UIGameScene();
	~UIGameScene();
	virtual bool init();

	CREATE_FUNC(UIGameScene);
	void scoreChange();
	void setScore(float temp);
	void updatePlayer(Player *player);

private:


	//cocos2d::Sprite * _Avatarp1;
	cocos2d::Sprite * _Bg;
	cocos2d::Sprite * _Bg1;
	cocos2d::Sprite * _Level;
	cocos2d::Sprite *_BgBar;
	cocos2d::Sprite *_HPbar2;
	Score* _Score;
	Score* _Score1;
	cocos2d::ui::LoadingBar *_HP1;
	cocos2d::ui::LoadingBar *_HP2;

	cocos2d::Size _winSize;

	cocos2d::Label* labelLV;
	cocos2d::Label* labelScore;
protected:
	//cocos2d::ui::LoadingBar* _HealthBar1;
	cocos2d::ui::LoadingBar* _ManaBar;
	cocos2d::ui::LoadingBar* _ManaBar1;
	int _totalScore = 0;

		int _totalScore1 = 0;
	


		void updateLevel(Player* player);
private:
	std::vector<float> listLv;
	
};


#endif //_UI_GAME_SCENE_H

