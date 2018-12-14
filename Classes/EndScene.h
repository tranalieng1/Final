#ifndef __ENDSCENE_H__
#define __ENDSCENE_H__
#include "cocos2d.h"
class EndScene : cocos2d::Scene
{
public:
	EndScene();
	~EndScene();
	static Scene* createScene();
	virtual bool init();
	void Message(float delta);
	void Invi(float delta);
	void goToEndScene(float delta);
	CREATE_FUNC(EndScene);
	cocos2d::Animate* createAnimate(std::string s, int n,float f);
	int _musicEnd;
private:
	cocos2d::Sprite* _ArthurSprite;
	cocos2d::Sprite* _PercivalSprite;
	cocos2d::Sprite* _MerlinSprite;

	cocos2d::Sprite* _Cloud;
	cocos2d::Label* _label;
	cocos2d::Size visibleSize;

};


#endif // !__ENDSCENE_H__


