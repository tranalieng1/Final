#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

bool Boss::init()
{
	if (!cocos2d::Node::init())
		return false;
	return true;
}
