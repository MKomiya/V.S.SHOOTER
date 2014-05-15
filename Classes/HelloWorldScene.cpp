#include "HelloWorldScene.h"
#include "PlayerView.h"
#include "PlayerModel.h"
#include "BulletView.h"
#include "ConnectManager.h"

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
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = Director::getInstance()->getVisibleOrigin();
    
    // プレイヤー表示
    _player = PlayerView::create();
    _player->setPosition(visibleSize.width/2, visibleSize.height/2);
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
    
    // エネミーの表示
    _enemy = PlayerView::create();
    _enemy->setPosition(visibleSize.width * 3.0f / 4.0f + origin.x, visibleSize.height/2 + origin.y);
    _enemy->getPlayerModel()->setPosition(_enemy->getPosition());
    this->addChild(_enemy, 0);
    _enemy->setFlippedX(true);
    
    this->schedule(schedule_selector(HelloWorld::enemyLogic));
    
    ConnectManager::getInstance()->connectAction(this);
    
    return true;
}

void HelloWorld::enemyLogic(float dt)
{
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

Point HelloWorld::getPlayerPos()
{
    return _player->getPosition();
}

void HelloWorld::setEnemyPos(cocos2d::Point pos)
{
    _enemy->setPosition(pos);
}