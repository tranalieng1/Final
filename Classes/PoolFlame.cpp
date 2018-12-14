#include "PoolFlame.h"
#include "Flame.h"

PoolFlame::PoolFlame()
{
	for (int i = 0; i < 2; i++)
	{
		auto instance = Flame::create();
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolFlame::returnMBToPool, this));
		_listMB.pushBack(instance);
	}
}

PoolFlame::~PoolFlame()
{
	for (int i = 0; i < _listMB.size(); i++)
	{
		auto moon = _listMB.at(i);
		CC_SAFE_RELEASE_NULL(moon);
	}
}
void PoolFlame::returnMBToPool(Flame * MB)
{
	MB->retain();
}
Flame * PoolFlame::createMB()
{
	for (int i = 0; i < _listMB.size(); i++)
	{
		auto moon = _listMB.at(i);
		if (moon->isVisible() == false)
		{
			return moon;
		}
	}

	return nullptr;
}