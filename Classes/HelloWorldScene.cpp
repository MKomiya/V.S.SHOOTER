#include "HelloWorldScene.h"
#include "PlayerView.h"
#include "PlayerModel.h"
#include "BulletView.h"

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
    _player = PlayerView::create();
    _player->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    _player->getPlayerModel()->setPosition(_player->getPosition());
    this->addChild(_player, 0);
    
    _prev_pos = _player->getPosition();
    
    // 操作系設定
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        _player->getPlayerModel()->setIsShooting(true);
        _prev_pos = touch->getLocation();
        return true;
    };
    listener->onTouchMoved = [=](Touch* touch, Event* event) {
        auto diff = touch->getLocation() - _prev_pos;
        auto pos = _player->getPlayerModel()->getPosition() + diff;
        _player->getPlayerModel()->moveTo(pos);
        _prev_pos = touch->getLocation();
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        _player->getPlayerModel()->setIsShooting(false);
        _prev_pos = touch->getLocation();
    };
    dispatcher->addEventListenerWithFixedPriority(listener, 128);
    
    // ロジックの登録
    this->schedule(schedule_selector(HelloWorld::playerLogic));
    
    return true;
}

void HelloWorld::playerLogic(float dt)
{
    if (_player->getPlayerModel()->getIsShooting())
    {
        this->_addBullet();
    }
}

void HelloWorld::_addBullet()
{
    auto bullet = BulletView::create(_player->getPosition());
    this->addChild(bullet);
}
