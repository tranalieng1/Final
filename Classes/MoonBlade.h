#ifndef __MOONBLADE_H__
#define __MOONBLADE_H__
#include "cocos2d.h"


class MoonBlade : public cocos2d::Node
{
public:
	MoonBlade();
	~MoonBlade();
	virtual bool init();

	CREATE_FUNC(MoonBlade);
private:

	std::vector<cocos2d::Sprite*> _MBSprite[2];


};
#endif //
