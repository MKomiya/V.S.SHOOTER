//
//  BulletView.h
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/13.
//
//

#ifndef __V_S_SHOOTER__BulletView__
#define __V_S_SHOOTER__BulletView__

#include <iostream>
#include <cocos2d.h>

class BulletView : public cocos2d::Sprite
{
public:
    static BulletView* create(cocos2d::Point pos);
    virtual bool init(cocos2d::Point pos);
};

#endif /* defined(__V_S_SHOOTER__BulletView__) */
