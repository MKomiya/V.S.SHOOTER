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
    
private:
    CC_SYNTHESIZE(bool, _shooting, IsShooting);
};

#endif /* defined(__V_S_SHOOTER__PlayerModel__) */
