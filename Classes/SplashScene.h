#ifndef _PLASH_SCENE_H_
#define	_PLASH_SCENE_H_
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "cocos2d.h"
class SplashScene : public cocos2d::Scene
{
public:
	SplashScene();
	~SplashScene();
	void	createSprSplash();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void goToMainMenuScene();
	CREATE_FUNC(SplashScene);
private:
	//void GotoMainMenuScene(float dt);

};
//auto loadingBar = LoadingBar::create("LoadingBarFile.png");
//
//loadingBar->setDirection(LoadingBar::Direction::RIGHT);
//
//// something happened, change the percentage of the loading bar
//loadingBar->setPercent(40);
//
//this->addChild(loadingBar);
#endif 
