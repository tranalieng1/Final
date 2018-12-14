#ifndef __FLAME_H__
#define __FLAME_H__
#include "cocos2d.h"
#include "GameObject.h"
class Flame;
typedef std::function<void(Flame* MB)> OnHitDestroyCallback2;
class Flame:public GameObject
{
public:
	Flame();
	~Flame();
	virtual bool init() override;
	virtual void onContactBeganWith(GameObject* obj);
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void takeDamage(float dmg, int temp) override;
	void setOnDestroyCallback(OnHitDestroyCallback2 callback);
	void update(float delta);
	void active();
	CREATE_FUNC(Flame);
private:
	float _ManaR;
	cocos2d::Sprite* _Flame1;
	cocos2d::Sprite* _Flame2;
	cocos2d::PhysicsBody *_Physicbody;
	void playanimation();
	bool _willBeDestroy;
	OnHitDestroyCallback2 _onHitDestroyCallback;
};


#endif // !__FLAME_H__

