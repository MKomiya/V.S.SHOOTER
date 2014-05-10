//
//  PlayerModel.h
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/10.
//
//

#ifndef __V_S_SHOOTER__PlayerModel__
#define __V_S_SHOOTER__PlayerModel__

#include <iostream>
#include <cocos2d.h>

class PlayerModel
{
public:
    PlayerModel();
    
    void moveTo(cocos2d::Point pos);
    
private:
    // 現在と前フレームの座標
    CC_SYNTHESIZE(cocos2d::Point, _pos, Position);
    CC_SYNTHESIZE(bool, _shooting, IsShooting);
};

#endif /* defined(__V_S_SHOOTER__PlayerModel__) */
