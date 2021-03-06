#ifndef __MAIN_MENU_SCENE_SCENE_H__
#define __MAIN_MENU_SCENE_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"

class MainMenuScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);

private:
	void GoToGameScene(cocos2d::Ref *sender);
	void SpawnPipe(float dt);
	Pipe pipe;
	cocos2d::Label *nameLabel;

};

#endif // __MAIN_MENU_SCENE_SCENE_H__
