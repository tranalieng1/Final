#ifndef __TEST_H__
#define __TEST_H__
#include "cocos2d.h"
class Test: cocos2d::Scene
{
public:
	Test();
	~Test();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Test);

private:

};


#endif // !__TEST_H__

