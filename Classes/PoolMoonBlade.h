#ifndef __POOL_MOONBLADE_H__
#define __POOL_MOONBLADE_H__
#include "cocos2d.h"
class MoonBlade;
class PoolMoonBlade
{
public:
	PoolMoonBlade();
	~PoolMoonBlade();
	MoonBlade *createMB();

private:
	cocos2d::Vector<MoonBlade*> _listMB;
	void returnMBToPool(MoonBlade *MB);
	
};



#endif // !__POOL_MOONBLADE_H__

