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

	auto flappyBody = PhysicsBody::createBox(Size(flappyBird->getContentSize().width, flappyBird->getContentSize().height), PhysicsMaterial(0, 1, 0));
	flappyBody->setGravityEnable(false);
	flappyBird->setPhysicsBody(flappyBody);

	layer -> addChild(flappyBird, 100);

	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);
	flappyBody->setMass(1);

	//isFalling = true;

	flappyBird->getPhysicsBody()->setVelocityLimit(300);
	
}

void Bird::Fall(){
		flappyBird->getPhysicsBody()->applyForce(Vec2(0, -30));
	
	
}

void Bird::Fly(cocos2d::Touch *touch) {
	touchLocationX = touch->getLocation().x;
	touchLocationY = touch->getLocation().y;
	willLocationX = flappyBird->getPositionX();
	willLocationY = flappyBird->getPositionY();

	float moveX = abs(touchLocationX - willLocationX);
	float moveY = abs(touchLocationY - willLocationY);

	float moveForce = sqrt(pow(moveX, 2) + pow(moveY, 2));

	float deltaX = touchLocationX - willLocationX;
	float deltaY = touchLocationY - willLocationY;
	float delta = deltaX / deltaY;

	float alpha = atan(delta) * (180 / M_PI);

	if (deltaY > 0){
		alpha += 180;
	}

	float xFactor = cosf(alpha);
	float yFactor = sinf(alpha);
	
	if (touchLocationX - willLocationX > 0){
		if (touchLocationY - willLocationY > 0){
			Vec2 force = Vec2(-1500 * abs(xFactor), -1500 * abs(yFactor));
			flappyBird->getPhysicsBody()->applyForce(force);
		}
		else{
			Vec2 force = Vec2(-1500 * abs(xFactor), 1500 * abs(yFactor));
			flappyBird->getPhysicsBody()->applyForce(force);
		}
	}
	else{
		if (touchLocationY - willLocationY > 0){
			Vec2 force = Vec2(1500 * abs(xFactor), -1500 * abs(yFactor));
			flappyBird->getPhysicsBody()->applyForce(force);

		}
		else{
			Vec2 force = Vec2(1500 * abs(xFactor), 1500 * abs(yFactor));
			flappyBird->getPhysicsBody()->applyForce(force);
		}
	}
	
		

}

int Bird::callculatePos(){
	return 0;
}

cocos2d::Point Bird::getPosition(){

	return cocos2d::Point(willLocationX, willLocationY);
}