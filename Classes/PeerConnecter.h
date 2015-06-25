//
//  PeerConnecter.h
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/13.
//
//

#import <GameKit/GameKit.h>
#import "HelloWorldScene.h"

@interface PeerConnecter : UIViewController<GKPeerPickerControllerDelegate, GKSessionDelegate> {
    GKSession* _session;
    NSString* _peerID;
    HelloWorld* _parentScene;
}

@property (nonatomic,retain) GKSession* session;
@property (nonatomic,retain) NSString* peerID;
@property HelloWorld* parentScene;

+ (PeerConnecter*)sharedPeerConnecter;
- (void)connectAction:(HelloWorld*)parent;
- (IBAction)sendText:(id)sender;

@end