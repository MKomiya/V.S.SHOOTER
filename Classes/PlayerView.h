//
//  PlayerView.h
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/10.
//
//

#ifndef __V_S_SHOOTER__PlayerView__
#define __V_S_SHOOTER__PlayerView__

#include <iostream>
#include <cocos2d.h>

class PlayerModel;

class PlayerView : public cocos2d::Sprite
{
public:
    static PlayerView* create();
    virtual bool init();
    virtual ~PlayerView();
private:
    CC_SYNTHESIZE_READONLY(PlayerModel*, _model, PlayerModel);
};

#endif /* defined(__V_S_SHOOTER__PlayerView__) */
