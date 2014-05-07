#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // プレイヤー表示
    _player = Sprite::create("player.png");
    _player->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(_player, 0);
    
    // 操作系設定
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        _prev_pos = touch->getLocation();
        return true;
    };
    listener->onTouchMoved = [=](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto add_pos = pos - _prev_pos;
        auto new_pos = _player->getPosition() + add_pos;
        _player->setPosition(new_pos);
        _prev_pos = pos;
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        _prev_pos = touch->getLocation();
    };
    dispatcher->addEventListenerWithFixedPriority(listener, 128);
    
    return true;
}
