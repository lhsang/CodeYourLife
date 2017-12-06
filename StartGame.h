#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__

#include "cocos2d.h"
#include"HelloWorldScene.h"
using namespace cocos2d;
using namespace std;
class StartGame : public cocos2d::Layer
{
public:
	int _score;
    static cocos2d::Scene* createScene();
	LabelTTF *_scoreLabel;
    virtual bool init();
	
	void gotoPlayScene();
	void MenuHelp();
	void gotoMenuScene();
	void MenuScore();
	
	CREATE_FUNC(StartGame);
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

};

#endif 
