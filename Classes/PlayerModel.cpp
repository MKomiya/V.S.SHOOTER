//
//  PlayerModel.cpp
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/10.
//
//

#include "PlayerModel.h"

USING_NS_CC;

PlayerModel::PlayerModel() :
_pos(Point(0,0)),
_shooting(false)
{
}

void PlayerModel::moveTo(cocos2d::Point pos)
{
    _pos = pos;
    __NotificationCenter::getInstance()->postNotification("playerMoved", NULL);
}