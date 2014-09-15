#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe(){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer){
	CCLOG("SPAWN PIPE");

	auto topPipe = Sprite::create("Pipe.png");
	auto buttomPipe = Sprite::create("Pipe.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto buttomPipeBody = PhysicsBody::createBox(buttomPipe->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_PIPE_THRESHOLD){
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD){
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	auto topPipePosition = (random*visibleSize.height + (topPipe->getContentSize().height / 2));

	topPipeBody->setDynamic(false);
	buttomPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_MASK);
	buttomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_MASK);

	topPipe->setPhysicsBody(topPipeBody);
	buttomPipe->setPhysicsBody(buttomPipeBody);

	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
	buttomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - (Sprite::create("ball.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));

	layer->addChild(topPipe);
	layer->addChild(buttomPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
	auto buttomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));

	topPipe->runAction(topPipeAction);
	buttomPipe->runAction(buttomPipeAction);
}