#ifndef __HIT_H__
#define __HIT_H__
#include "cocos2d.h"
#include "GameObject.h"
class Hit : public GameObject
{
public:
	Hit();
	~Hit();
	virtual bool init() override;
	

	virtual void onContactBeganWith(GameObject* obj) ;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	CREATE_FUNC(Hit);
	void setSize_body(cocos2d::Size temp);
	void setcatory(int temp);
	void setcollisin(int temp);
	virtual void takeDamage(float dmg,int temp) override;
	
private:
	cocos2d::PhysicsBody *_Physicbody;
	cocos2d::PhysicsBody *_Physicbody2;


};



#endif // !__HIT_H__

