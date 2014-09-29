#include "Bird.h"
#include "Definitions.h"
#include "Math.h"

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
		float moveX = abs(touchLocationX - willLocationX);
		float moveY = abs(touchLocationY - willLocationY);

		float moveForce = sqrt(pow(moveX, 2) + pow(moveY, 2));

		float deltaX = touchLocationX - willLocationX;
		float deltaY = touchLocationY - willLocationY;
		float delta = deltaX / deltaY;

		float alpha = atan(delta) * (180 / M_PI);

		float xFactor = cosf(alpha);
		float yFactor = sinf(alpha);

		if (touchLocationX - willLocationX > 0){

			flappyBird->setPositionX(flappyBird->getPositionX() - (((visibleSize.width * MOVE_POWER / 4) + (MOVE_POWER * moveForce))* abs(xFactor)));
			flappyBird->setPositionY(flappyBird->getPositionY() + (((visibleSize.height * MOVE_POWER / 2) - (MOVE_POWER * moveForce)) * abs(yFactor)));

		}
		else{

			flappyBird->setPositionX(flappyBird->getPositionX() + (((visibleSize.width * MOVE_POWER / 4) - (MOVE_POWER * moveForce)) * abs(xFactor)));
			flappyBird->setPositionY(flappyBird->getPositionY() + (((visibleSize.height * MOVE_POWER / 2) - (MOVE_POWER * moveForce))* abs(yFactor)));
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

int Bird::callculatePos(){
	return 0;
}

cocos2d::Point Bird::getPosition(){

	return cocos2d::Point(willLocationX, willLocationY);
}