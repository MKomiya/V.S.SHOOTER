//
//  ConnectManager.mm
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/15.
//
//

#import "ConnectManager.h"
#import "PeerConnecter.h"
#import "HelloWorldScene.h"

void ConnectManager::connectAction(HelloWorld* parent)
{
    [[PeerConnecter sharedPeerConnecter] connectAction:parent];
}

void ConnectManager::sendPosision()
{
    [[PeerConnecter sharedPeerConnecter] sendText:nil];
}