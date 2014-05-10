//
//  PlayerView.cpp
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/10.
//
//

#include "PlayerView.h"
#include "PlayerModel.h"

USING_NS_CC;

PlayerView* PlayerView::create()
{
    auto ret = new PlayerView();
    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

PlayerView::~PlayerView()
{
    delete _model;
}

bool PlayerView::init()
{
    if (!Sprite::initWithFile("player.png"))
    {
        return false;
    }
    
    _model = new PlayerModel();
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayerView::playerMove), "playerMoved", NULL);
    return true;
}

void PlayerView::playerMove(Ref* ref)
{
    this->setPosition(_model->getPosition());
}