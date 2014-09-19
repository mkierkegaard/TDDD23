#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"

class Score 
{
public:

	Score();
      
	void Score::SpawnScore(cocos2d::Layer *layer);

	void Score::removeScoreObject();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};

#endif // __SCORE_SCENE_H__
