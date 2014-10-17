#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
	score = tempScore;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }

	this->setColor(ccc3(255, 255, 255));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	auto retryItem = MenuItemImage::create("Retry.png","Retry_Selected.png" , CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menuItem = MenuItemImage::create("Menu.png", "Menu_Selected.png" , CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
	menuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4  + origin.y));

	auto menu = Menu::create(retryItem, menuItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	UserDefault *def = UserDefault::getInstance();

	auto highscore = def->getIntegerForKey("HIGHSCORE", 0);

	if (score > highscore){

		highscore = score;
		def->setIntegerForKey("HIGHSCORE", highscore);
	}

	def->flush();

	__String *tempScore = __String::createWithFormat("Score: %i", score);
	auto currentScore = Label::create(tempScore->getCString(), "Arial", visibleSize.height * SCORE_FONT_SIZE);
	currentScore->setPosition(Point(visibleSize.width * 0.25 + origin.x, visibleSize.height / 4 * 3 + origin.y));
	currentScore->setColor(Color3B::BLACK);
	
	this->addChild(currentScore);

	__String *tempHighScore = __String::createWithFormat("Highscore: %i", highscore);
	auto highScoreLabel = Label::create(tempHighScore->getCString(), "Arial", visibleSize.height *SCORE_FONT_SIZE);
	highScoreLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 4 * 3 + origin.y));
	highScoreLabel->setColor(Color3B::BLACK);

	this->addChild(highScoreLabel);

    return true;
}

void GameOverScene::GoToGameScene(cocos2d::Ref *sender){
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender){
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}