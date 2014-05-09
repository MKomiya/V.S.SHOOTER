#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    // プレイヤー関連処理の更新
    void playerLogic(float dt);
    
private:
    // プレイヤー関連
    cocos2d::Sprite* _player;
    cocos2d::Point _prev_pos;
    bool _shooting;
    
    void _addBullet();
};

#endif // __HELLOWORLD_SCENE_H__
