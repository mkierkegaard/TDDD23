#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
	this->setColor(ccc3(255, 255, 255));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_MASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);
    
	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);
	bird = new Bird(this);

	instruction = Sprite::create("Instruction.png");
	instruction->setPosition(Point(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y - 120));
	this->addChild(instruction);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	scorePoints = 0;
	this->schedule(schedule_selector(GameScene::addPoint), 1 );
	__String *currTempScore = __String::createWithFormat("%i", scorePoints);
	scoreLabel = Label::create(currTempScore->getCString(), "Arial", visibleSize.height * SCORE_FONT_SIZE);
	scoreLabel->setColor(Color3B::BLACK);
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
		auto scene = GameOverScene::createScene(scorePoints);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		
		return true;
	}
	
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){



	bird->Fly(touch);
	this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);

	float xPos = touch->getLocation().x;
	float yPos = touch->getLocation().y;

	cocos2d::Sprite* wind = Sprite::create("Wind.png");

	Point willPos = bird->getPosition();

	float deltaX = (xPos - willPos.x);
	float deltaY = (yPos - willPos.y);
	float delta = deltaX / deltaY;
	
	float alpha = atan(delta) * (180 / M_PI);

	if (deltaY > 0){
		alpha += 180;
	}

	
	
	CCLOG("alpha : %f", alpha);
		
		
	auto rotation = RotateBy::create(0, alpha);
	wind->runAction(rotation);
	wind->setPosition(Point(xPos,yPos));

	this->addChild(wind);
	auto fadeAction = FadeOut::create(2);
	wind->runAction(fadeAction);

	auto expand = ScaleBy::create(1, 2.5);
	wind->runAction(expand);

	//this->removeChild(wind);
	return true;
}

void GameScene::StopFlying(float dt){
	bird->StopFlying();

}

void GameScene::update(float dt){
	bird->Fall();
	__String *tempScore = __String::createWithFormat("%i", scorePoints);
	scoreLabel->setString(tempScore->getCString());
}


void GameScene::addPoint(float dt){
	scorePoints++;
}
