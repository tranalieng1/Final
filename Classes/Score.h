#ifndef _score_H
#define _score_H

#include "cocos2d.h"

class Score : public cocos2d::Node
{
public:
	Score();
	~Score();
	CREATE_FUNC(Score);
	virtual bool init();
	static int _scoreFrist;
	void setscore(int);

	void scoreChange(int score);

private:
	cocos2d::Sprite* _score;
	static bool _beginscore;
	cocos2d::Vector<cocos2d::Sprite*> _listSprite;
};



#endif // !_score_H
