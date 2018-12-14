#ifndef __POOL_FLAME_H__
#define __POOL_FLAME_H__
#include "cocos2d.h"
class Flame;
class PoolFlame
{
public:
	PoolFlame();
	~PoolFlame();
	Flame *createMB();

private:
	cocos2d::Vector<Flame*> _listMB;
	void returnMBToPool(Flame *MB);
	
};



#endif // !__POOL_MOONBLADE_H__

