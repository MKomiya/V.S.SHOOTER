//
//  ConnectManager.h
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/15.
//
//

#ifndef __V_S_SHOOTER__ConnectManager__
#define __V_S_SHOOTER__ConnectManager__

#include <iostream>

class HelloWorld;
class ConnectManager
{
public:
    static ConnectManager* getInstance()
    {
        ConnectManager instance;
        return &instance;
    }
    
    void connectAction(HelloWorld* scene);
    void sendPosision();
};

#endif /* defined(__V_S_SHOOTER__ConnectManager__) */
