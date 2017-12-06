#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
#include "cocos2d.h"
#include"OverLayer.h"
#include "ui/CocosGUI.h"
#include "StartGame.h"
//abc
USING_NS_CC;
const char *HIGH_SCORE = "key";

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mainsoundbackground.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mainsoundbackground.mp3" , true);
	//
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("background.jpg");
	background->setScaleX(1.3);
	background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	background->setScaleX(origin.x + visibleSize.width / background->getContentSize().width);
	background->setScaleY(origin.y + visibleSize.height / background->getContentSize().height);

	this->addChild(background);
	_shield = Shield::create();
	_shield->setTag(2);
	this->addChild(_shield);
	

    _earth = Earth::create();
	_earth->setTag(1);
	
	this->addChild(_earth);

	//auto mouseListener = EventListenerTouchOneByOne::create();
	//mouseListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	


//	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	_score = 0;
	_scoreLabel = LabelTTF::create("0", "fonts/Alba.ttf", 50);
	_scoreLabel->setColor(Color3B::ORANGE);
    _scoreLabel->setPosition(visibleSize.width / 2, (visibleSize.height / 6) * 5);
	this->addChild(_scoreLabel);

	_highscore = 0;
	_highScoreLabel = LabelTTF::create(" ", "fonts/Alba.ttf", 20);
	_highScoreLabel->setPosition(visibleSize.width - 80, visibleSize.height - 30);
	_highScoreLabel->setColor(Color3B::ORANGE);
	this->addChild(_highScoreLabel);
	
	auto buttonleft = ui::Button::create("buttonleft.png");
	buttonleft->setScale(0.5f);
	buttonleft->setPosition(Vec2(buttonleft->getContentSize().width / 2, visibleSize.height / 6));
	buttonleft->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			if (_rotateRight_earth)
			{
				auto rotate = RotateBy::create(3, 360);
				_earth->runAction(RepeatForever::create(rotate));
				_rotateRight_earth = false;

			}
			else
			{
				auto rotate = RotateBy::create(3, -360);
				_earth->runAction(RepeatForever::create(rotate));
				_rotateRight_earth = true;
			}
		}
		break;

		default:
			break;
		}
	});
	this->addChild(buttonleft);

	auto buttonright = ui::Button::create("buttonright.png");
	buttonright->setScale(0.5f);

	buttonright->setPosition(Vec2(visibleSize.width - buttonright->getContentSize().width / 2, visibleSize.height / 6));
	buttonright->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			if (_rotateRight)
			{
				auto rotate = RotateBy::create(3, 360);
				_shield->runAction(RepeatForever::create(rotate));
				_rotateRight = false;

			}
			else
			{
				auto rotate = RotateBy::create(3, -360);
				_shield->runAction(RepeatForever::create(rotate));
				_rotateRight = true;
			}
		}
		break;

		default:
			break;
		}
	});

	this->addChild(buttonright);
	this->scheduleUpdate();
	
    return true;
}

void HelloWorld::update(float dt)
{
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
/*
bool HelloWorld::onTouchBegan(Touch * touch, Event * event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 touchLocation = touch->getLocation();
	if (( (touchLocation.x > visibleSize.width/2 -_earth->getContentSize().width/2) && (touchLocation.x < visibleSize.width/2+_earth->getContentSize().width/2))
		&& ((touchLocation.y > visibleSize.height / 2 - _earth->getContentSize().height / 2) && (touchLocation.y < visibleSize.height / 2 + _earth->getContentSize().height / 2)) )
		{
		if (_rotateRight_earth)
		{
			auto rotate = RotateBy::create(2, 360);
			_earth->runAction(RepeatForever::create(rotate));
			_rotateRight_earth = false;

		}
		else
		{
			auto rotate = RotateBy::create(2, -360);
			_earth->runAction(RepeatForever::create(rotate));
			_rotateRight_earth = true;
		}
	}
	else
	{
		if (_rotateRight)
		{
			auto rotate = RotateBy::create(2, 360);
			_shield->runAction(RepeatForever::create(rotate));
			_rotateRight = false;

		}
		else
		{
			auto rotate = RotateBy::create(2, -360);
			_shield->runAction(RepeatForever::create(rotate));
			_rotateRight = true;
		}
	}
	return true;
}*/
void HelloWorld::spriteMoveFinished(Node* sender)
{

	auto sprite = (Sprite *)sender;
	this->removeChild(sprite, true);
}
void HelloWorld::gameLogic(float dt)
{
	this->addCreep();
}
inline void HelloWorld::addCreep()
{
	char as[100];
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	srand(time(NULL));
	int c = rand() % 2 + 1; int a = rand() % 4 + 1;
	if (c == 1)
	{
		std::string ten = "harmful_";
		//srand(time(NULL));
		int dem = rand() % 3 + 1;
		sprintf(as, "%d", dem);
		ten += as;
		ten += ".png";
		creep = Sprite::create(ten);
		creep->setTag(4);
	}
	if (c == 2)
	{
		std::string ten = "useful_";
	
		int dem = rand() % 3 + 1;
		sprintf(as, "%d", dem);
		ten += as;
		ten += ".png";
		creep = Sprite::create(ten);
		creep->setTag(3);
	}
	int b;
	
	if (a == 1)
	{
		//CCLOG("win");Vect force = Vect(-100000.0f / 2, 100000.0f / b)
		int minX = creep->getContentSize().width / 2;

		int maxX = origin.x + visibleSize.width - creep->getContentSize().width / 2;
		int rangeX = maxX - minX;
		int actualX = (rand() % rangeX) + minX;
		int l;
		if (actualX < origin.x + visibleSize.width / 2)
		{
			l = (origin.x + visibleSize.width / 2 - actualX) * 100;
		}
		else { l = -(actualX - origin.x + visibleSize.width / 2) * 100; }
		CCLOG("%d", l);
		creep->setPosition(Point(actualX, origin.y + visibleSize.height - (creep->getContentSize().height / 2)));


		auto creepBody = PhysicsBody::createCircle(creep->getContentSize().width / 3);
		creepBody->getShape(0)->setRestitution(1.2f);
		creepBody->getShape(0)->setFriction(0.0f);
		creepBody->getShape(0)->setDensity(1.0f);
		do { b = rand() % 2 + 3; } while (b == 0);
		Vect force = Vect(100000.0f / 2 + l, -100000.0f / 2); // T?o 1 l?c tác d?ng
		creepBody->applyImpulse(force);
		creepBody->setCategoryBitmask(0x03);
		creepBody->setContactTestBitmask(0x01 | 0x02);
		creep->setPhysicsBody(creepBody);
		this->addChild(creep);
		int minDuration = (int)2.0;
		int maxDuration = (int)4.0;
		int rangeDuration = maxDuration - minDuration;
		int actualDuration = (rand() % rangeDuration) + minDuration;
		auto actionMove = MoveTo::create((float)actualDuration, Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		auto actionRotate = RotateBy::create(3, 360);
		creep->runAction(RepeatForever::create(actionRotate));
		auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
		//creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
	}
	if (a == 2)
	{
		int minY = creep->getContentSize().height / 2;

		int maxY = origin.y + visibleSize.height - creep->getContentSize().width / 2;
		int rangeY = maxY - minY;
		int actualY = (rand() % rangeY) + minY;

		creep->setPosition(Point(origin.x + (creep->getContentSize().width / 2), actualY));


		auto creepBody = PhysicsBody::createCircle(creep->getContentSize().width / 3);
		creepBody->getShape(0)->setRestitution(1.2f);
		creepBody->getShape(0)->setFriction(0.0f);
		creepBody->getShape(0)->setDensity(1.0f);
		creepBody->setGravityEnable(false); // giatoc=0
		do { b = rand() % 2 + 3; } while (b == 0);
		Vect force = Vect(100000.0f / 2, 100000.0f / b); // T?o 1 l?c tác d?ng
		creepBody->applyImpulse(force);
		creepBody->setCategoryBitmask(0x03);
		creepBody->setContactTestBitmask(0x01 | 0x02);
		creep->setPhysicsBody(creepBody);
		this->addChild(creep);
		int minDuration = (int)2.0;
		int maxDuration = (int)4.0;
		int rangeDuration = maxDuration - minDuration;
		int actualDuration = (rand() % rangeDuration) + minDuration;
		auto actionMove = MoveTo::create((float)actualDuration, Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		auto actionRotate = RotateBy::create(3, 360);
		creep->runAction(RepeatForever::create(actionRotate));
		auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
		//creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
	}
	if (a == 3)
	{
		int minY = creep->getContentSize().height / 2;

		int maxY = origin.y + visibleSize.height - creep->getContentSize().width / 2;
		int rangeY = maxY - minY;
		int actualY = (rand() % rangeY) + minY;

		creep->setPosition(Point(origin.x + visibleSize.width - (creep->getContentSize().width / 2), actualY));


		auto creepBody = PhysicsBody::createCircle(creep->getContentSize().width / 3);
		creepBody->getShape(0)->setRestitution(1.2f);
		creepBody->getShape(0)->setFriction(0.0f);
		creepBody->getShape(0)->setDensity(1.0f);
		creepBody->setGravityEnable(false); // giatoc=0
		do { b = rand() % 2 + 3; } while (b == 0);
		Vect force = Vect(-100000.0f / 2, 100000.0f / b); // T?o 1 l?c tác d?ng
		creepBody->applyImpulse(force);
		creepBody->setCategoryBitmask(0x03);
		creepBody->setContactTestBitmask(0x01 | 0x02);

		creep->setPhysicsBody(creepBody);
		this->addChild(creep);
		int minDuration = (int)2.0;
		int maxDuration = (int)4.0;
		int rangeDuration = maxDuration - minDuration;
		int actualDuration = (rand() % rangeDuration) + minDuration;
		auto actionMove = MoveTo::create((float)actualDuration, Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		auto actionRotate = RotateBy::create(3, 360);
		creep->runAction(RepeatForever::create(actionRotate));
		auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
		//creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
	}
	if (a == 4)
	{
		int minX = origin.x + creep->getContentSize().width / 2;
		//CCLOG("%d", minX);
		int maxX = origin.x + visibleSize.width - creep->getContentSize().width / 2;
		//CCLOG("%d", maxX);
		int rangeX = maxX - minX;
		srand(time(NULL));
		int actualX = (rand() % rangeX) + minX;
		//CCLOG("%d", actualX);
		creep->setPosition(Point(actualX, origin.y + (creep->getContentSize().height / 3)));


		auto creepBody = PhysicsBody::createCircle(creep->getContentSize().width / 2);

		creepBody->getShape(0)->setRestitution(1.2f);
		creepBody->getShape(0)->setFriction(0.0f);
		creepBody->getShape(0)->setDensity(1.0f);
		creepBody->setGravityEnable(false); // giatoc=0
		do { b = rand() % 2 + 3; } while (b == 0);
		int l;
		if (actualX < origin.x + visibleSize.width / 2) { l = (origin.x + visibleSize.width / 2 - actualX) * 100; }
		else { l = -(actualX - origin.x + visibleSize.width / 2) * 100; }
		Vect force = Vect(100000.0f / 2 + l, 100000.0f / 2); // T?o 1 l?c tác d?ng
		creepBody->applyImpulse(force); // Ð?y 1 l?c
		creep->setPhysicsBody(creepBody);


		creepBody->setCategoryBitmask(0x03);
		creepBody->setContactTestBitmask(0x01 | 0x02);
		//creep->setPhysicsBody(creepBody);
		this->addChild(creep);
		int minDuration = (int)2.0;
		int maxDuration = (int)4.0;
		int rangeDuration = maxDuration - minDuration;
		int actualDuration = (rand() % rangeDuration) + minDuration;
		auto actionMove = MoveTo::create((float)actualDuration, Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		auto actionRotate = RotateBy::create(3, 360);
		creep->runAction(RepeatForever::create(actionRotate));

		auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
		//creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
	}
	//CCLOG("%d", creep -> getTag());
}
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto shapeA = contact.getShapeA()->getBody()->getNode();
	auto shapeB = contact.getShapeB()->getBody()->getNode();
	int tagA = shapeA->getTag();

	int tagB = shapeB->getTag();
	if ((tagA == 1 && tagB == 3) || (tagA == 3 && tagB == 1))
	{

		int wA = origin.x + visibleSize.width / 2;int hA = origin.y + visibleSize.height / 2;
		int  wB = shapeA->getPositionX();
		int hB = shapeA->getPositionY();
		if ((wB - wA)*(wB - wA) + (hB - hA)*(hB - hA) < _earth->getContentSize().width / 2 * _earth->getContentSize().width / 2)
		{
			_score+=2;
			_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
			this->removeChild(shapeA);
			//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("eat.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("eat.mp3", false, 1.0f, 1.0f, 1.0f);
		
			userdefault = UserDefault::getInstance();
            highscore = userdefault->getIntegerForKey(HIGH_SCORE, highscore);
			if (_score > highscore)
			{
				highscore = _score;
				userdefault->setIntegerForKey(HIGH_SCORE, highscore);
			}
            _highScoreLabel->setString(String::createWithFormat("BEST SCORE: %d", highscore)->getCString());
		}
	}
	
	if ((tagA==1 && tagB==4)||(tagA==4 &&tagB==1))
		
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("GameOverSound.mp3");
		_earth->stopAllActions();
		_shield->stopAllActions();
		this->pause();
		auto overlayer = OverLayer::create();
	       
			overlayer->setPosition(origin.x, origin.y);
			this->addChild(overlayer, 110);

		}
	if ((tagA == 2 && tagB == 4) || (tagA == 4 && tagB == 2))
	{
		
		_score++;
		this->removeChild(creep);
		_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
        userdefault = UserDefault::getInstance();
        highscore = userdefault->getIntegerForKey(HIGH_SCORE, highscore);
		if (_score > highscore)
		{
			highscore = _score;
			userdefault->setIntegerForKey(HIGH_SCORE, highscore);
		}

		_highScoreLabel->setString(String::createWithFormat("BEST SCORE: %d", highscore)->getCString());
	}
	return true;
}
int HelloWorld::getHighScore()
{
	return highscore;
}
