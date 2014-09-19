#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe(){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer){
	CCLOG("SPAWN PIPE");

	auto topPipe = Sprite::create("ball.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random > UPPER_SCREEN_PIPE_THRESHOLD){
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	auto topPipePosition = (random*visibleSize.width + (topPipe->getContentSize().width / 2));


	topPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_MASK);
	topPipeBody->setContactTestBitmask(true);
	topPipe->setPhysicsBody(topPipeBody);

	topPipe->setPosition(Point(topPipePosition, -(visibleSize.height + topPipe->getContentSize().height + origin.x)));

	layer->addChild(topPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(0, visibleSize.height *3));

	topPipe->runAction(topPipeAction);


}