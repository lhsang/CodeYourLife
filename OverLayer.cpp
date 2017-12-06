#include "OverLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;



bool OverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto OverPanel = Sprite::create("GameOver.png");
	OverPanel->setScale(1.1f);
	OverPanel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(OverPanel);
   // _scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 120);
	//_scoreLabel->setPosition(origin.x + visibleSize.width / 2, OverPanel->getPositionY());

	auto menuBtn = MenuItemImage::create("MenuBtn_Selected.png", "MenuBtn_Selected.png", CC_CALLBACK_0(OverLayer::gotoMenuScene, this));
	auto replayBtn = MenuItemImage::create("ReplayBtn_Selected.png", "ReplayBtn_Selected.png", CC_CALLBACK_0(OverLayer::gotoPlayScene, this));

	auto menu = Menu::create(menuBtn,replayBtn, nullptr);
	menu->alignItemsHorizontallyWithPadding(50);

	menu->setPosition(origin.x + visibleSize.width / 2, OverPanel->getPositionY()- 5);

	this->addChild(menu);
   
    return true;
}
void OverLayer::gotoMenuScene()
{
	auto menuscene = StartGame::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, menuscene));
}

void OverLayer::gotoPlayScene()
{
	auto playscene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(playscene);
}

