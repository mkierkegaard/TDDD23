#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	flappyBird = Sprite::create("Will.png");
	flappyBird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	willLocationX = flappyBird->getPositionX();
	willLocationY = flappyBird->getPositionY();

	auto flappyBody = PhysicsBody::createBox(Size(flappyBird->getContentSize().width, flappyBird->getContentSize().height) );
	flappyBird->setPhysicsBody(flappyBody);

	layer -> addChild(flappyBird, 100);

	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);

	isFalling = true;

}

void Bird::Fall(){
	if (true == isFalling) {
		flappyBird->setPositionX(flappyBird->getPositionX());
		flappyBird->setPositionY(flappyBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
	}
	else{
		if (touchLocationX - willLocationX > 0){
			flappyBird->setPositionX(flappyBird->getPositionX() - (WIND_POWER * visibleSize.width));
			flappyBird->setPositionY(flappyBird->getPositionY() + (WIND_POWER * visibleSize.height));

		}
		else{
			flappyBird->setPositionX(flappyBird->getPositionX() + (WIND_POWER * visibleSize.width));
			flappyBird->setPositionY(flappyBird->getPositionY() + (WIND_POWER * visibleSize.height));
		}
		
	}
}

void Bird::Fly(cocos2d::Touch *touch) {
	touchLocationX = touch->getLocation().x;
	touchLocationY = touch->getLocation().y;
	willLocationX = flappyBird->getPositionX();
	willLocationY = flappyBird->getPositionY();

	if (abs(touchLocationX - willLocationX) < visibleSize.width / 4 && abs(touchLocationY - willLocationY) < visibleSize.height / 4){

		isFalling = false; 

	}

	

}
