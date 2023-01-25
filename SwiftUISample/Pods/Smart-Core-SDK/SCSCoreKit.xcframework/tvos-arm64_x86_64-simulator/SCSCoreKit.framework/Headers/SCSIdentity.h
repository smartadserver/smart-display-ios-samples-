//
//  SCSIdentity.h
//  SCSCoreKit
//
//  Created by Thomas Geley on 23/03/2017.
//  Copyright © 2017 Smart AdServer. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Enum that defines all possible identities for a device.
typedef NS_ENUM(NSInteger, SCSIdentityType) {
    /// No valid identity can be retrieved for this device.
    SCSIdentityTypeUndefined                        = 0,
    
    /// Apple's advertising ID is used as identity for this device.
    SCSIdentityTypeAdvertisingID                    = 1,
    
    /// A temporary (24 hours) transient ID is used as identity for this device. This ID must no be used for tracking purpose!
    SCSIdentityTypeTransientID                      = 2,
    
    /// A custom identity provided by the publisher.
    SCSIdentityTypeCustomID                         = 3,
};

@protocol SCSIdentityProviderProtocol;
@class SCSTCFString, SCSCCPAString;

/**
 Helper class to retrieve the identity of a device.
 */
@interface SCSIdentity : NSObject

/// The main identity of the device, valid only if the type is not equal to SCSIdentityType.undefined.
@property (nonatomic, readonly) NSString *identity;

/// The type of the main identity of the device.
@property (nonatomic, readonly) SCSIdentityType type;

/// true if the identity string is MD5 hashed, false otherwise.
@property (nonatomic, readonly) BOOL isHashed __deprecated_msg("The user identifier is not hashed anymore, please use HTTPS in order to ensure that all user informations are protected during the ad call.");

/// The ifa of the device if any, nil otherwise.
@property (nullable, nonatomic, readonly) NSString *ifa;

/// The ifv of the device if any, nil otherwise.
@property (nullable, nonatomic, readonly) NSString *ifv;

/// The transient id of the device if any, nil otherwise.
@property (nullable, nonatomic, readonly) NSString *transientId;

/// A custom identifier provided by the app if any, nil otherwise.
@property (nullable, nonatomic, readonly) NSString *customIdentifier;

/// true if the transient ID has been allowed as an identity, false otherwise.
@property (nonatomic, readonly) BOOL isTransientIDEnabled;

/// The consent string stored on the device NSUserDefaults under IAB specifications key.
@property (nullable, nonatomic, readonly) NSString *gdprConsentString;

/// The SCSTCFString instance representing the GDPR Consent String stored on the device NSUserDefaults under IAB specifications key.
@property (nullable, nonatomic, readonly) SCSTCFString *TCFString;

/// The CCPAString instance representing the CCPA Consent String stored on the device NSUserDefaults under IAB specifications key.
@property (nullable, nonatomic, readonly) SCSCCPAString *CCPAString;

/// YES if we can send the device identifiers, NO otherwise.
///
/// Sending the device identifiers can be prevented by any privacy law applicable where the app is running
/// and will be determined using data set by the app CMP.
@property (nonatomic, readonly) BOOL canSendIDs;

/**
 Retrieve an identity for the device using the identity provider given in parameter.
 
 This class handles all the identifier selection logic and defer the actual ID retrieval to the identity
 provider to ease unit testing. It should most of the time be used alongside the default SCSIdentityProvider
 (or with the convenience init).
 
 @param identityProvider the identity provider used to retrieve actual ID.
 @param hashed This parameter is now deprecated and ignored!
 @param transientIDEnabled true if the transient ID is allowed, false otherwise (advertising ID will always be chosen first).
 @param customIdentifier a string generated by the publisher to set a custom identity to the current device.
 */
- (instancetype)initWithIdentityProvider:(id <SCSIdentityProviderProtocol>)identityProvider hashed:(BOOL)hashed transientIDEnabled:(BOOL)transientIDEnabled customIdentifier:(nullable NSString *)customIdentifier NS_DESIGNATED_INITIALIZER;

/**
 Convenience initializer to retrieve an identity for the device using the default identity provider SCSIdentityProvider.
 
 @param hashed This parameter is now deprecated and ignored!
 @param transientIDEnabled true if the transient ID is allowed, false otherwise (advertising ID will always be chosen first).
 */
- (instancetype)initWithHashed:(BOOL)hashed transientIDEnabled:(BOOL)transientIDEnabled;

/**
 Convenience initializer to retrieve an identity for the device using the default identity provider SCSIdentityProvider.

 @param hashed This parameter is now deprecated and ignored!
 @param transientIDEnabled true if the transient ID is allowed, false otherwise (advertising ID will always be chosen first).
 @param customIdentifier a string generated by the publisher to set a custom identity to the current device.
 */
- (instancetype)initWithHashed:(BOOL)hashed transientIDEnabled:(BOOL)transientIDEnabled customIdentifier:(nullable NSString *)customIdentifier;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
