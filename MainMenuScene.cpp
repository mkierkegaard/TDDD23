#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }

	this->setColor(ccc3(255, 255, 255));

	if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Around the Fireplace_3.mp3", true);
	}
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->schedule(schedule_selector(MainMenuScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * Director::getInstance()->getVisibleSize().width);

	auto titleSprite = Sprite::create("Menu_Header.png");
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + titleSprite->getContentSize().height));

	this->addChild(titleSprite, 1000);

	auto playItem = MenuItemImage::create("play.png", "play_selected.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu, 1000);

	__String *name = __String::createWithFormat("Martin Kierkegaard 2014");
	nameLabel = Label::create(name->getCString(), "Arial", visibleSize.height * NAME_FONT_SIZE);
	nameLabel->setColor(Color3B::BLACK);
	nameLabel->setPosition(Point(visibleSize.width * 0.9 + origin.x, +origin.y + NAME_FONT_SIZE + visibleSize.height * NAME_FONT_SIZE));
	this->addChild(nameLabel, 10000);

    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender){
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void MainMenuScene::SpawnPipe(float dt){
	pipe.SpawnPipe(this);

}