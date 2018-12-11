#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "SplashScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
USING_NS_CC;

SplashScene::SplashScene()
{
}
SplashScene::~SplashScene()
{
}
Scene* SplashScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SplashScene::create();

	scene->addChild(layer);
	return scene;

}


bool SplashScene::init()
{
	////////////////////////////

	if (!Scene::init())
	{
		return false;
	}
	//Load music
	experimental::AudioEngine::preload("Sound/splash.mp3");
	experimental::AudioEngine::preload("Sound/menu.mp3");
	experimental::AudioEngine::preload("Sound/option.mp3");
	experimental::AudioEngine::preload("Sound/chemm.mp3");
	experimental::AudioEngine::preload("Sound/credit.mp3");
	experimental::AudioEngine::preload("Sound/splash.mp3");
	experimental::AudioEngine::preload("Sound/nhacgame.mp3");
	experimental::AudioEngine::preload("Sound/no.mp3");
	experimental::AudioEngine::preload("Sound/jump.mp3");
	//sound Spl
	experimental::AudioEngine::play2d("Sound/splash.mp3");
	/*auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Sound/strat16.mp3", false);*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ArthurLvl1.plist", "ArthurLvl1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill/Flame.plist", "Skill/Flame.png");
	/*CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/sfx_die.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/sfx_point.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/sfx_wing.wav");*/

	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createSprSplash();
	///////////////////////////
	/*createSprSplash();*/
	return true;
}
void SplashScene::goToMainMenuScene()
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}
void SplashScene::createSprSplash()
{
	//
	
	//Back Ground
	Size winSize = Director::getInstance()->getWinSize();
	auto backgound = Sprite::create("bgSplash.png");
	this->addChild(backgound);
	backgound->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	backgound->setPosition(this->getContentSize() * 0.5f);
	float scaleX = winSize.width*0.8 / (backgound->getContentSize().width);
	float scaleY = winSize.height*0.8 / (backgound->getContentSize().height);
	backgound->setScaleX(scaleX);
	backgound->setScaleY(scaleY);
	//cái vỏ 
	auto bgLoading = Sprite::create("LoadingBar.png");
	this->addChild(bgLoading);
	bgLoading->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.05f));
	//cái ruột
	auto loadingBar = ui::LoadingBar::create("LoadingBar2.png");
	loadingBar->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.05f));
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPercent(0);
	this->addChild(loadingBar);
	this->schedule([=](float delta) {
		float percen = loadingBar->getPercent();
		percen++;
		loadingBar->setPercent(percen);
		if (percen >= 100.0f)
		{
			this->unschedule("updateloadingBar");
			this->goToMainMenuScene();
		}
	}, 0.05f, "updateloadingBar"); //thời gian

}