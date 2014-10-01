#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"
#include "Score.h"


class GameScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world){ sceneWorld = world; }
	cocos2d::PhysicsWorld *sceneWorld;

	void SpawnPipe(float dt);
	void SpawnScore(float dt);

	cocos2d::Sprite *instruction;

	bool onContactBegin(cocos2d::PhysicsContact &contact);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void StopFlying(float dt);
	void update(float dt);

	void addPoint(float dt);

	Pipe pipe;

	Score score;

	Bird *bird;

	unsigned int scorePoints;
	cocos2d::Label *scoreLabel;

};

#endif // __GAME_SCENE_H__
