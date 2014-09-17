#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    // 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);


	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("HelloWorld.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_MASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);
    
	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);
	this->schedule(schedule_selector(GameScene::SpawnScore), PIPE_SPAWN_FREQUENCY * visibleSize.width);
	bird = new Bird(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	scorePoints = 0;

	__String *tempScore = __String::createWithFormat("%i", scorePoints);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setPosition(Point(visibleSize.width * 0.9  + origin.x, visibleSize.height * 0.9 + origin.y));

	this->addChild(scoreLabel, 10000);

	this->scheduleUpdate();
    return true;
}

void GameScene::SpawnPipe(float dt){
	pipe.SpawnPipe(this);

}

void GameScene::SpawnScore(float dt){
	score.SpawnScore(this);

}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){

	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_MASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_MASK == a->getCollisionBitmask())){
		CCLOG("Points scored: %i", scorePoints);
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		
		return true;
	}
	else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && SCORE_COLLISION_MASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && SCORE_COLLISION_MASK == a->getCollisionBitmask())){

		scorePoints++;
		__String *tempScore = __String::createWithFormat("%i", scorePoints);
		scoreLabel->setString(tempScore->getCString());
	}
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){



	bird->Fly(touch);
	this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);

	return true;
}

void GameScene::StopFlying(float dt){
	bird->StopFlying();

}

void GameScene::update(float dt){
	bird->Fall();

}