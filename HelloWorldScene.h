#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Earth.h"
#include"Shield.h"
//abc
class HelloWorld : public cocos2d::Layer
{
protected:
	private:
		int highscore;
		Sprite *creep;
		Earth *_earth;
		Shield *_shield;
		bool _rotateRight=true;
		bool _rotateRight_earth = true;
		int _score;
		LabelTTF *_scoreLabel;
		LabelTTF *_highScoreLabel;
		int _highscore;
		UserDefault *userdefault;
public:
	PhysicsWorld* m_world;

	//LabelTTF *status_label;

	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
    static cocos2d::Scene* createScene();

    virtual bool init() override;
	virtual void update(float dt) override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//bool onTouchBegan(Touch *touch, Event *event);
	bool onContactBegin(PhysicsContact &contact);
	void gameLogic(float dt);
	void addCreep();
	void spriteMoveFinished(Node* sender);
	int getHighScore();
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
