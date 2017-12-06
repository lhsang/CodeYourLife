#include "Shield.h"
#include "MyBodyParser.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool Shield::init()
{
    //////////////////////////////
    // 1. super init first
   
	if (!this->initWithFile("rainbow.png"))
	{
		return false;
	}
   this->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
   MyBodyParser::getInstance()->parseJsonFile("BowBody.json");
   auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(this, "Name1", PHYSICSBODY_MATERIAL_DEFAULT);
   // tạo physics body
   //auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0, 0, 0));
   spriteBody->getShape(0)->setRestitution(1.1f);
   spriteBody->getShape(0)->setFriction(0.0f);
   spriteBody->getShape(0)->setDensity(1.0f); // Tỷ trọng = 10
   spriteBody->setGravityEnable(false); // O đặt gia tốc
   spriteBody->setDynamic(false); // Vật tĩnh khi tương tác
								  //paddle->setPosition(visibleSize.width / 2, 50); // Vị trí
 
   // I am a pixel
   spriteBody->setCategoryBitmask(0x02);
   // I collide with ...
   //body->setCollisionBitmask(0);
   spriteBody->setContactTestBitmask(0x03);
   this->setPhysicsBody(spriteBody);
  // this->setScale(0.6f);
   _rotateRight = true;
   auto rotate = RotateBy::create(3, -360);
   this->runAction(RepeatForever::create(rotate));
   _rotateRight = true;
  
  
   this->scheduleUpdate();
 
    return true;
}

void Shield::update(float dt)
{
	
	
}




