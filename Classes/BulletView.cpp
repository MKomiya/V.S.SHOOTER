//
//  BulletView.cpp
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/13.
//
//

#include "BulletView.h"

USING_NS_CC;

BulletView* BulletView::create(Point pos)
{
    auto ret = new BulletView();
    if (ret->init(pos))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool BulletView::init(Point pos)
{
    if (!Sprite::initWithFile("bullet.png"))
    {
        return false;
    }
    
    this->setPosition(pos);
    
    auto s = Director::getInstance()->getWinSize();
    auto mover = MoveBy::create(1.0f, Point(s.width, 0));
    auto remover = RemoveSelf::create();
    this->runAction(Sequence::create(mover, remover, NULL));
    
    return true;
}