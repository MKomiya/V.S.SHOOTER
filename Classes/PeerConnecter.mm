//
//  PeerConnecter.mm
//  V.S.SHOOTER
//
//  Created by S_Wyvern on 2014/05/13.
//
//

#import "PeerConnecter.h"

@implementation PeerConnecter

static PeerConnecter* _sharedData = nil;

+ (PeerConnecter*)sharedPeerConnecter {
    if (!_sharedData) {
        _sharedData = [PeerConnecter new];
    }
    return _sharedData;
}

- (id)init
{
    self = [super init];
    if(!self) { return nil; }
    return self;
}

- (void)connectAction:(HelloWorld *)parent
{
    self.parentScene = parent;
    
    GKPeerPickerController* picker = [[GKPeerPickerController alloc] init];
    picker.connectionTypesMask = GKPeerPickerConnectionTypeNearby;
    picker.delegate = self;
    [picker show];
}

- (void)peerPickerController:(GKPeerPickerController *)picker didConnectPeer:(NSString *)peerID toSession:(GKSession *)session
{
    self.session = session;
    self.peerID  = peerID;
    session.delegate = self;
    [session setDataReceiveHandler:self withContext:nil];
    picker.delegate = nil;
    [picker dismiss];
    [picker autorelease];
}

- (IBAction)sendText:(id)sender
{
    cocos2d::Point pos = _parentScene->getPlayerPos();
    
    NSMutableData* data = [[NSMutableData alloc] init];
    [data appendData:[NSData dataWithBytes:&pos length:sizeof(cocos2d::Point)]];
    
    NSError* error = nil;
    [self.session sendData:data toPeers:[NSArray arrayWithObject:self.peerID]
              withDataMode:GKSendDataReliable error:&error];
    if (error) {
        NSLog(@"%@", error);
    }
}

- (void)session:(GKSession *)session peer:(NSString *)peerID didChangeState:(GKPeerConnectionState)state
{
	NSString* stateDesc;
	if (state == GKPeerStateAvailable) stateDesc = @"GKPeerStateAvailable";
    else if (state == GKPeerStateUnavailable) stateDesc = @"GKPeerStateUnavailable";
    else if (state == GKPeerStateConnected) stateDesc =	@"GKPeerStateConnected";
    else if (state == GKPeerStateDisconnected) stateDesc = @"GKPeerStateDisconnected";
    else if (state == GKPeerStateConnecting) stateDesc = @"GKPeerStateConnecting";
    NSLog(@"%s|%@|%@", __PRETTY_FUNCTION__, peerID, stateDesc);
                        
    switch (state) {
        case GKPeerStateConnected:
            CCLOG("connected");
            self.peerID = peerID;
            break;
        case GKPeerStateDisconnected:
            CCLOG("disconnected");
            self.session = nil;
        default:
            break;
    }
}

- (void)session:(GKSession *)session didReceiveConnectionRequestFromPeer:(NSString *)peerID
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, peerID);
	NSError* error = nil;
	[session acceptConnectionFromPeer:peerID error:&error];
	if (error) {
		NSLog(@"%@", error);
	}
}

- (void)session:(GKSession *)session connectionWithPeerFailed:(NSString *)peerID withError:(NSError *)error
{
	NSLog(@"%s|%@|%@", __PRETTY_FUNCTION__, peerID, error);
}

- (void)session:(GKSession *)session didFailWithError:(NSError *)error
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, error);
}

- (void) receiveData:(NSData *)data fromPeer:(NSString *)peer
inSession: (GKSession *)session context:(void *)context
{
    cocos2d::Point pos;
    [data getBytes:&pos length:sizeof(cocos2d::Point)];
    self.parentScene->setEnemyPos(pos);
}

@end