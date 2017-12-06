#include "StartGame.h"
#include"HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"ui\CocosGUI.h"
#include"SimpleAudioEngine.h"
using namespace cocos2d;
using namespace std;
USING_NS_CC;

Scene* StartGame::createScene()
{
    auto scene = Scene::create();
	auto layer = StartGame::create();

    scene->addChild(layer);

    return scene;
}

bool StartGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	//background
	_score = UserDefault::getInstance()->getIntegerForKey("key", 0);
	//
	auto menuBackground = Sprite::create("background_startgame1.png");
	menuBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	menuBackground->setScaleX(origin.x+visibleSize.width / menuBackground->getContentSize().width);
	menuBackground->setScaleY(origin.y+visibleSize.height / menuBackground->getContentSize().height);

	this->addChild(menuBackground);
	//music background
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mymusic.mp3", true);
	// tên game
	auto titleGame = Sprite::create("Title.png");
	titleGame->setScale(0.8f);
	titleGame->setPosition(visibleSize.width/2.2,visibleSize.height/1.1);
	this->addChild(titleGame);
	//Khien
	auto protect = Sprite::create("protect.png");
	protect->setScale(0.9f);
	protect->setPosition(visibleSize.width / 4, visibleSize.height /  3);
	this->addChild(protect);
	auto rotateBy1 = RotateBy::create(2.0f, -360.0f);
	auto actionRepeat1 = RepeatForever::create(rotateBy1);
	protect->runAction(actionRepeat1);
	//khien 2
	auto protect1 = Sprite::create("protect.png");
	protect1->setPosition(visibleSize.width / 4, visibleSize.height /  3);
	protect1->setScale(0.9f);
	this->addChild(protect1);
	auto rotateBy2 = RotateBy::create(2.0f, 360.0f);
	auto actionRepeat2 = RepeatForever::create(rotateBy2);
	protect1->runAction(actionRepeat2);
	// EARTH
	auto earth = Sprite::create("Earth.png");
	earth->setPosition(visibleSize.width / 4, visibleSize.height /  3);
	earth->setScale(0.9f);
	this->addChild(earth);
	auto rotateBy = RotateBy::create(5.0f, 360.0f);
	auto actionRepeat = RepeatForever::create(rotateBy); 
	earth->runAction(actionRepeat);
	
	// nút play để vào chơi
	auto playBtn = MenuItemImage::create("playButton.png", "playButton.png", CC_CALLBACK_0(StartGame::gotoPlayScene, this));
	auto menu = Menu::create(playBtn, nullptr);
	menu->setPosition(visibleSize.width /1.6,visibleSize.height / 1.7);
	this->addChild(menu);
	//button help

	auto helpbutton = MenuItemImage::create("help.png", "help.png", CC_CALLBACK_0(StartGame::MenuHelp, this));
	auto menuhelp = Menu::create(helpbutton, nullptr);
	menuhelp->setPosition(menu->getPositionX()+50, menu->getPositionY() - 80);

	this->addChild(menuhelp);
	//bestscore
	auto bestbutton = MenuItemImage::create("bestscore.png", "bestscore.png", CC_CALLBACK_0(StartGame::MenuScore, this));
	auto menubest = Menu::create(bestbutton, nullptr);
	menubest->setPosition(menuhelp->getPositionX() + 50, menuhelp->getPositionY() - 80);
	this->addChild(menubest);
    return true;
}

void StartGame::gotoPlayScene()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto playscene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(playscene);
}
void StartGame::MenuHelp()
{
	auto _menuhelp = Sprite::create("menuhelp.png");
	_menuhelp->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	_menuhelp->setScaleX(origin.x + visibleSize.width / _menuhelp->getContentSize().width);
	_menuhelp->setScaleY(origin.y + visibleSize.height / _menuhelp->getContentSize().height);
	this->addChild(_menuhelp);
	//button menu
	
	auto menuBtn1 = MenuItemImage::create("MenuBtn_Selected.png", "MenuBtn_Selected.png", CC_CALLBACK_0(StartGame::gotoMenuScene, this));
	menuBtn1->setScale(0.6f);
	auto menuscene1 = Menu::create(menuBtn1, nullptr);
	menuscene1->setPosition(visibleSize.width-50,60);
	this->addChild(menuscene1);
	//
	
}
void StartGame::MenuScore()
{
	auto _menuscore = Sprite::create("background_startgame2.png");
	_menuscore->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	_menuscore->setScaleX(origin.x + visibleSize.width / _menuscore->getContentSize().width);
	_menuscore->setScaleY(origin.y + visibleSize.height / _menuscore->getContentSize().height);
	this->addChild(_menuscore);
	//button menu

	auto menuBtn2 = MenuItemImage::create("MenuBtn_Selected.png", "MenuBtn_Selected.png", CC_CALLBACK_0(StartGame::gotoMenuScene, this));
	auto menuscene2 = Menu::create(menuBtn2, nullptr);
	menuscene2->setPosition(visibleSize.width - 50, 60);
	this->addChild(menuscene2);
	
	_scoreLabel = LabelTTF::create("0" , "fonts/Minecrafter.ttf", 120);
	_scoreLabel->setPosition(visibleSize.width/2,visibleSize.height/2);
	_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	this-> addChild(_scoreLabel);
}
void StartGame::gotoMenuScene()
{
	auto menuscene = StartGame::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, menuscene));
}



