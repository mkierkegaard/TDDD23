#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird 
{
public:
	Bird(cocos2d::Layer *layer);

	void Fall();
	void Fly(cocos2d::Touch *touch);
	void StopFlying(){ isFalling = true; }


private: 
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *flappyBird;

	float touchLocationX;
	float touchLocationY;
	float willLocationX;
	float willLocationY;


	bool isFalling;
};

#endif // __BIRD_H__
