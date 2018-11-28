#ifndef __FANMAN_H__
#define __FANMAN_H__
#include "cocos2d.h"
#include"Enemy.h"

class FanMan : public Enemy
{
	/*struct AnimationInfo
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
		JUMPING
	};*/
public:
	FanMan();
	~FanMan();
	void Attack() override;
	virtual bool init() override;
	void Jump() override;
	void Attack1Animation() override;
	void WalkAnimation() override;
	void StopAction() override;

	void onContactBeganWith(GameObject* obj) override ;
	void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)override;
	void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)override;
	void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	void PlayAnimation(AnimationType type);

	

	CREATE_FUNC(FanMan);
private:

	

};
#endif //