#ifndef _UI_SCENE_H
#define _UI_SCENE_H

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void GoToGameScene(cocos2d::Ref* pSender);
	void GoToGameOptions(cocos2d::Ref* pSender);
	CREATE_FUNC(MainMenuScene);
	virtual bool init();
private:

};


#endif // !_UI_SCENE_H
