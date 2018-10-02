#ifndef __SPLASHSCENE_H__
#define __SPLASHCENE_H__

#include "cocos2d.h"

class SplashScene: public cocos2d::Layer
{
public:
	
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(SplashScene);
private:
	
	void GotoMainMenuScene(float dt);
};


#endif // !__SPLASHSCENE_H__

