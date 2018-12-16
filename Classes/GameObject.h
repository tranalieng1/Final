#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "cocos2d.h"
enum _State
{
	STATE_ATTACKING,
	STATE_JUMPING,
	STATE_STANDING,
	STATE_WALKING,
	STATE_HITTED,
	STATE_DEATH,
	STATE_FALLING,
	STATE_GETUP,
	STATE_LEVELUP,
	STATE_WIN
};
struct AnimationInfo
{
	int numFrame;
	std::string filePath;
	float fps;
	int loopTime;

	AnimationInfo(int num, std::string path, float f, int loop)
	{
		numFrame = num;
		filePath = path;
		fps = f;
		loopTime = loop;
	}
};

enum class AnimationType
{
	WALKING,
	ATTACKING,
	JUMPING,
	HITTED,
	DEATH,
	FALLING,
	GETUP,
	LEVELUP,
	STANDING,
};
class GameObject: public cocos2d::Node
{
public:
	GameObject();
	~GameObject();

	virtual void onContactBeganWith(GameObject* obj) = 0;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) = 0;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) = 0;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) = 0;
	virtual bool init() override;
	float getDamage();
	void setDamage(float temp);
	virtual void takeDamage(float dmg,int temp) = 0;
	//virtual void enalbeAI(GameObject* player);
private:
protected:
	float _damage;
	
};


#endif // !__GAMEOBJECT_H__

