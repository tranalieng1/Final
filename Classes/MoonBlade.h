#ifndef __MOONBLADE_H__
#define __MOONBLADE_H__
#include "cocos2d.h"
#include "GameObject.h"
class MoonBlade;
typedef std::function<void(MoonBlade* MB)> OnHitDestroyCallback;
class MoonBlade : public GameObject
{
public:
	MoonBlade();
	~MoonBlade();
	virtual bool init() override;
	void flySkill();
	virtual void onContactBeganWith(GameObject* obj);
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void takeDamage(float dmg) override;
	void setOnDestroyCallback(OnHitDestroyCallback callback);
	CREATE_FUNC(MoonBlade);
	void update(float delta);
private:

	float _ManaR;
	cocos2d::Sprite* _MBSprite1;
	cocos2d::Sprite* _MBSprite2;
	cocos2d::Sprite* _MBSprite3;
	cocos2d::PhysicsBody* _Physicbody;
	float temp;

	bool _willBeDestroy;
	OnHitDestroyCallback _onHitDestroyCallback;
};


#endif //
