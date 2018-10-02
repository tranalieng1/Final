#ifndef __GAMESCENE1_H__
#define __GAMESCENE1_H__

#include "cocos2d.h"

class GameScene_1 : public cocos2d::Layer
{
public:


	static cocos2d::Scene *createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

private:

	
};


#endif //G__GAMESCENE1_H__

