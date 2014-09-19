#include "Score.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;


// on "init" you need to initialize your instance
Score::Score()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	
}


void Score::SpawnScore(cocos2d::Layer *layer){
	auto scoreNode = Node::create();
	auto scoreBody = PhysicsBody::createBox(Size(visibleSize.width, 1));
	scoreBody->setDynamic(false);
	scoreBody->setCollisionBitmask(SCORE_COLLISION_MASK);
	scoreBody->setContactTestBitmask(true);

	

	scoreNode->setPhysicsBody(scoreBody);
	scoreNode->setPosition(Point(visibleSize.width / 2, -(visibleSize.height + visibleSize.height + origin.x)));
	


	layer->addChild(scoreNode);

	auto scoreNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(0, visibleSize.height * 3));

	scoreNode->runAction(scoreNodeAction);
}

void Score::removeScoreObject(){

}