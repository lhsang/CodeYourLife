#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "cocos2d.h"
USING_NS_CC;
class Shield : public cocos2d::Sprite
{
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bool _rotateRight=false;
	RotateBy *_rotate;
public:
    

    virtual bool init() override;
    
	virtual void update(float dt) override;
	
    // implement the "static create()" method manually
    CREATE_FUNC(Shield);
};

#endif 
