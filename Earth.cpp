#include "Earth.h"
#include "MyBodyParser.h"

USING_NS_CC;
//abc


// on "init" you need to initialize your instance
bool Earth::init()
{
    //////////////////////////////
    // 1. super init first
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
   if(!this->initWithFile("Earth.png"))
   {
	   return false;
   }
   this->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
   //this->setScale(0.3f);
   MyBodyParser::getInstance()->parseJsonFile("EarthBody.json");
   auto body = MyBodyParser::getInstance()->bodyFormJson(this, "Name1", PHYSICSBODY_MATERIAL_DEFAULT);
   body->getShape(0)->setRestitution(1.1f);
   body->getShape(0)->setFriction(0.0f);
   body->getShape(0)->setDensity(1.0f); // Tỷ trọng = 10
   body->setGravityEnable(false); // O đặt gia tốc
   body->setDynamic(false); // Vật tĩnh khi tương tác
								  //paddle->setPosition(visibleSize.width / 2, 50); // Vị trí

								  // I am a pixel
   body->setCategoryBitmask(0x01);
  // body->setCategoryBitmask(0x01);
  // body->setCollisionBitmask(0);
   body->setContactTestBitmask(0x03);
   //body->setContactTestBitmask(0x01);
   this->setPhysicsBody(body);
   auto rotate = RotateBy::create(4, 360);
   this->runAction(RepeatForever::create(rotate));
   
   
   this->scheduleUpdate();

    return true;
}





