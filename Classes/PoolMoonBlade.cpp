#include "PoolMoonBlade.h"
#include "MoonBlade.h"

PoolMoonBlade::PoolMoonBlade()
{
	for (int i = 0; i < 2; i++)
	{
		auto instance = MoonBlade::create();
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolMoonBlade::returnMBToPool, this));
		_listMB.pushBack(instance);
	}
}

PoolMoonBlade::~PoolMoonBlade()
{
	for (int i = 0; i < _listMB.size(); i++)
	{
		auto moon = _listMB.at(i);
		CC_SAFE_RELEASE_NULL(moon);
	}
}
void PoolMoonBlade::returnMBToPool(MoonBlade * MB)
{
	MB->retain();
}
MoonBlade * PoolMoonBlade::createMB()
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