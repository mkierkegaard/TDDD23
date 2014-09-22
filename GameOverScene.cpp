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

	

	auto retryItem = MenuItemImage::create("Retry.png","Retry.png" , CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menuItem = MenuItemImage::create("Menu.png", "Menu.png" , CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
	menuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4  + origin.y));

	auto menu = Menu::create(retryItem, menuItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	__String *tempScore = __String::createWithFormat("%i", score);
	auto currentScore = Label::create(tempScore->getCString(), "Arial", visibleSize.height * SCORE_FONT_SIZE);
	currentScore->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 + origin.y));
	currentScore->setColor(Color3B::BLACK);
	
	this->addChild(currentScore);

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