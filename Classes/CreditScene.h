#ifndef __CREDITSCENE_H__
#define __CREDITSCENE_H__
#include "cocos2d.h"
class CreditScene : cocos2d::Scene
{
public:
	CreditScene();
	~CreditScene();
	static Scene* createScene();
	virtual bool init();
	void goToMenuScene();
	CREATE_FUNC(CreditScene);
	
private:
	

};


#endif // !__ENDSCENE_H__


