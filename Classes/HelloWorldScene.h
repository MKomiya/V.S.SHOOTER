#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class PlayerView;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    // プレイヤー関連処理の更新
    void playerLogic(float dt);
    
    // 敵の座標を同期
    void enemyLogic(float dt);
    
    cocos2d::Point getPlayerPos();
    void setEnemyPos(cocos2d::Point pos);
    
private:
    // プレイヤー関連
    PlayerView *_player, *_enemy;
    cocos2d::Point _prev_pos;
    bool _shooting;
    
    void _addBullet();
};

#endif // __HELLOWORLD_SCENE_H__
