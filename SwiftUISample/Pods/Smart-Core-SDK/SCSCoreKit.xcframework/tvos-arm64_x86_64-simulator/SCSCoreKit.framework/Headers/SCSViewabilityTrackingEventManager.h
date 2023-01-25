//
//  SCSViewabilityTrackingEventManager.h
//  SCSCoreKit
//
//  Created by Loïc GIRON DIT METAZ on 23/05/2017.
//  Copyright © 2017 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SCSCoreKit/SCSTrackingEvent.h>
#import <SCSCoreKit/SCSViewabilityTrackingEvent.h>
#import <SCSCoreKit/SCSViewabilityTrackingEventManagerProtocol.h>
#import <SCSCoreKit/SCSTrackingEventManager.h>
#import <SCSCoreKit/SCSViewabilityStatus.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Default SCSViewabilityTrackingEventManager protocol implementation.
 */
@interface SCSViewabilityTrackingEventManager : SCSTrackingEventManager <SCSViewabilityTrackingEventManager>

/**
 Updates the viewability information to allow the viewability tracking manager to update all tracking events.
 
 These informations are typically retrieved using an instance of SCSViewabilityManager.
 
 @param viewable YES if the tracked view is considered as viewable, NO otherwise.
 @param percentage The percentage of viewability (between 0.0 and 1.0).
 */
- (void)viewabilityUpdated:(BOOL)viewable withPercentage:(CGFloat)percentage __deprecated_msg("Use viewabilityUpdatedWithViewabilityStatus: instead");

@end

NS_ASSUME_NONNULL_END
