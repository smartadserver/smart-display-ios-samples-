//
//  SASBannerView.h
//  SmartAdServer
//
//  Created by Clémence Laurent on 09/03/12.
//  Copyright © 2018 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SASDisplayKit/SASAdView.h>
#import <SASDisplayKit/SASLoader.h>
#import <SASDisplayKit/SASBannerViewDelegate.h>
#import <SASDisplayKit/SASBiddingAdResponse.h>

#define SASRefreshIntervalOff        (-1)
#define SASRefreshIntervalMinimum    20

NS_ASSUME_NONNULL_BEGIN

/**
 Informations needed to configure the parallax effect manually.
 */
@interface SASParallaxInfos : NSObject

/**
 Initializes a new SASParallaxInfos instance.
 
 @param topOrigin The vertical origin of the parallax viewport relative to UIScreen. The viewport
 represents the whole area where the parallax should be displayed. For example, if you don't want
 to include status and the navigation bars, the top origin should be 64pts.
 @param height The height of the parallax viewport relative to UIScreen.
 @return An initialized instance of SASParallaxInfos.
 */
- (instancetype)initWithViewportTopOrigin:(CGFloat)topOrigin viewportHeight:(CGFloat)height;

@end

/**
 The SASBannerView class provides a view that automatically loads and displays a banner creative.
 
 The SASBAnnerView class inherits from SASAdView, which contains its most useful methods like loadWithPlacement:. We recommend
 you to check the SASAdView API documentation as well.
 
 You can listen for view or ad related events by implementing the SASBannerViewDelegate protocol. Implementing this delegate
 can be particulary useful to hide the banner if the ad loading fails, or in the contrary, to show the banner view instance
 only when an ad as been successfully loaded.
 */
@interface SASBannerView : SASAdView

#pragma mark - Ad banner view properties

/// The object that acts as the delegate of the banner view.
///
/// The delegate must adopt the SASBannerViewDelegate protocol.
@property (nonatomic, weak, nullable) id <SASBannerViewDelegate> delegate;

/// Starts or stops the ad's auto refresh feature on this banner view by setting the refresh interval in seconds. The
/// refresh interval cannot be less than SASRefreshIntervalMinimum (20 seconds).
///
/// By default, the refresh interval is set to SASRefreshIntervalOff.
///
/// @warning The refresh interval will be ignored if a bidding response is currently being displayed by the banner view.
@property (nonatomic, assign) NSInteger refreshInterval;

/// Sets informations that will be used for the parallax effect.
///
/// In most cases, the banner view will automatically get any information needed to allow the parallax effect to
/// work properly. However in some complex integrations, the banner might compute these informations improperly.
/// In this case, you can provide an object with the relevant informations.
///
/// If you set a value here, parallax will not be handled automatically by the SDK anymore. Set this value to nil
/// to get back to automatic positioning.
@property (nonatomic, retain, nullable) SASParallaxInfos *parallaxInfos;

#pragma mark - Creating a banner view

/**
 Initializes a SASBannerView instance for a given frame.
 
 @param frame A rectangle specifying the initial location and size of the ad banner view in its superview's coordinates.
 */
- (instancetype)initWithFrame:(CGRect)frame;

/**
 Initializes a SASBannerView instance for a given frame with a loader.
 
 The loader will be displayed during the ad loading, until an ad has been fetched or until an error happens.
 
 @param frame A rectangle specifying the initial location and size of the ad banner view in its superview's coordinates.
 @param loaderType A SASLoader constant that determines which loader the view should display while downloading the ad.
 */
- (instancetype)initWithFrame:(CGRect)frame loader:(SASLoader)loaderType;

#pragma mark - Loading ad data

/**
 Load a bidding ad received through the SASBiddingManager.
 
 Call this method after initializing your SASBannerView object to load the appropriate SASBiddingAdResponse object from the server.
 
 @param biddingAdResponse The SASBiddingAdResponse that should be used
 */
- (void)loadBiddingAdResponse:(SASBiddingAdResponse *)biddingAdResponse;

#pragma mark - Displaying a banner at proper size

/**
 Returns the recommanded height to display the ad view in a given container, according to the ad aspect ratio.
 
 If no ad is loaded, this method will return its initialization frame height for standard UIView container and will return 0 for UITableView and UICollectionView containers.
 
 @param container The container in which the ad will be displayed (if nil, the current window will be used instead)
 @return The optimized height for the ad view.
 */
- (CGFloat)optimalAdViewHeightForContainer:(nullable UIView *)container;

/**
  Returns the ad aspect ratio.
  
  If no ad is loaded, this method will return default 320x50 ad ratio
  
  @return The ratio for the ad view.
  */
- (CGFloat)ratio;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
