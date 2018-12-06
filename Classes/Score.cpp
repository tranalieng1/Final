#include "score.h"
USING_NS_CC;

#define MAXscore 99999
#define UNIT 10
#define DOZENS 10
#define HUNDREDS 100
#define THOUSANDS 1000
#define TENSOFTHOUSANDS 10000

#define NUM_score 5
#define NUMBER_GAMEPLAY_POSITION_HEIGHT 0.968f
#define NUMBER_GAMEPLAY_POSITION_WIDTH 0.4f
#define NUMBER_DISTANT 0.026f

int Score::_scoreFrist = 0;

Score::Score()
{
}

Score::~Score()
{
}
bool Score::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	for (int i = 0; i < NUM_score; i++)
	{
		_score = Sprite::createWithSpriteFrameName("0.png");
		float ScaleX = winSize.width / _score->getContentSize().width;
		float ScaleY = winSize.height / _score->getContentSize().height;
		_score->setScaleX(ScaleX);

		_score->setScaleY(ScaleY);
		_score->setPosition(Vec2(winSize.width*0.35 - (25*i), winSize.height*0.98));
		/*_score->setPosition(Vec2(winSize.width*(NUMBER_GAMEPLAY_POSITION_WIDTH + (NUMBER_DISTANT*i)), winSize.height*NUMBER_GAMEPLAY_POSITION_HEIGHT));*/
		_score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_score->setScale(0.5f);
		this->addChild(_score);
		_listSprite.pushBack(_score);
	}
	return true;
}

void Score::scoreChange(int score)
{
	int unit = score % UNIT;
}


void Score::setscore(int score)
{
	if (score >= MAXscore)
	{
		int max = 9;
		std::string tempscore = StringUtils::format("%i.png", max);
		Sprite *score = nullptr;
		for (int i = 0; i < 6; i++)
		{
			score = _listSprite.at(i);
			score->setSpriteFrame(tempscore);
		}

	}

	else if (score >= TENSOFTHOUSANDS)
	{
		int unit = score % UNIT;
		int dozens = (score / DOZENS) % UNIT;
		int hundreds = (score / HUNDREDS) % DOZENS;
		int thousands = (score / THOUSANDS) % DOZENS;
		int tensofthousands = score / TENSOFTHOUSANDS;

		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(0)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(1)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(2)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(3)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(4)->setSpriteFrame(tempscore5);

	}
	else if (score >= THOUSANDS)
	{
		int unit = score % UNIT;
		int dozens = (score / DOZENS) % UNIT;
		int hundreds = (score / HUNDREDS) % DOZENS;
		int thousands = score / THOUSANDS;
		int tensofthousands = score / TENSOFTHOUSANDS;

		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(0)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(1)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(2)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(3)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(4)->setSpriteFrame(tempscore5);

	}
	else if (score >= HUNDREDS)
	{
		int unit = score % UNIT;
		int dozens = (score / DOZENS) % UNIT;
		int hundreds = score / HUNDREDS;
		int thousands = score / THOUSANDS;
		int tensofthousands = score / TENSOFTHOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(0)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(1)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(2)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(3)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(4)->setSpriteFrame(tempscore5);
	}
	else if (score >= DOZENS)
	{
		int unit = score % UNIT;
		int dozens = score / DOZENS;
		int hundreds = score / HUNDREDS;
		int thousands = score / THOUSANDS;
		int tensofthousands = score / TENSOFTHOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(0)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(1)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(2)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(3)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(4)->setSpriteFrame(tempscore5);
	}
	else
	{
		int dozens = score / DOZENS;
		int hundreds = score / HUNDREDS;
		int thousands = score / THOUSANDS;
		int tensofthousands = score / TENSOFTHOUSANDS;

		std::string tempscore1 = StringUtils::format("%i.png", score);
		_listSprite.at(0)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(1)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(2)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(3)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(4)->setSpriteFrame(tempscore5);
	}
	_scoreFrist = score;
}