#ifndef __MOONBLADE_H__
#define __MOONBLADE_H__
#include "cocos2d.h"



class MoonBlade : public cocos2d::Node
{
public:
	MoonBlade();
	~MoonBlade();
	virtual bool init();
	void flySkill();

	CREATE_FUNC(MoonBlade);
private:

	cocos2d::Sprite* _MBSprite1;
	cocos2d::Sprite* _MBSprite2;
	cocos2d::Sprite* _MBSprite3;


};


#endif //
