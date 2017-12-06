#ifndef __OVER_LAYER_H__
#define __OVER_LAYER_H__

#include "cocos2d.h"
#include "StartGame.h"
#include "HelloWorldScene.h"
class OverLayer : public cocos2d::Layer
{
public:
    

    virtual bool init();
	void gotoMenuScene();
	void gotoPlayScene();
	
	CREATE_FUNC(OverLayer);
	//void setScore(int score);

	

	
	
};

#endif // __HELLOWORLD_SCENE_H__
