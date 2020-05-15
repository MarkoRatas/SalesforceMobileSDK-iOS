/*
 SFLayoutSyncManager.h
 MobileSync
 
 Created by Bharath Hariharan on 5/18/18.
 
 Copyright (c) 2018-present, salesforce.com, inc. All rights reserved.
 
 Redistribution and use of this software in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions
 and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of
 conditions and the following disclaimer in the documentation and/or other materials provided
 with the distribution.
 * Neither the name of salesforce.com, inc. nor the names of its contributors may be used to
 endorse or promote products derived from this software without specific prior written
 permission of salesforce.com, inc.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <SmartStore/SFSmartStore.h>
#import "SFMobileSyncSyncManager.h"
#import "SFLayout.h"
#import "SFMobileSyncConstants.h"

/**
 * Completion block triggered when layout sync completes.
 *
 * @param objectAPIName Object API name.
 * @param formFactor Form factor.
 * @param layoutType Layout type.
 * @param mode Mode.
 * @param recordTypeId Record type ID.
 * @param layout Layout.
 */
typedef void (^SFLayoutSyncCompletionBlock) (NSString * _Nonnull objectAPIName, NSString * _Nullable formFactor, NSString * _Nullable layoutType, NSString * _Nullable mode, NSString * _Nullable recordTypeId, SFLayout * _Nullable layout) NS_SWIFT_NAME(LayoutSyncCompletionBlock);

/**
 * Provides an easy way to fetch layout data using SFLayoutSyncDownTarget.
 * This class handles creating a soup, storing synched data and reading it into
 * a meaningful data structure, i.e. SFLayout.
 */
NS_SWIFT_NAME(LayoutSyncManager)
@interface SFLayoutSyncManager : NSObject

@property (nonatomic, strong, readonly, nonnull) SFSmartStore *smartStore;
@property (nonatomic, strong, readonly, nonnull) SFMobileSyncSyncManager *syncManager;

/**
 * Returns the instance of this class associated with current user.
 *
 * @return Instance of this class.
 */
+ (nonnull instancetype)sharedInstance;

/**
 * Returns the instance of this class associated with this user account.
 *
 * @param user User account.
 * @return Instance of this class.
 */
+ (nonnull instancetype)sharedInstance:(nullable SFUserAccount *)user;

/**
 * Returns the instance of this class associated with this user and SmartStore.
 *
 * @param user User account. Pass null to use current user.
 * @param smartStore SmartStore name. Pass nil to use current user default SmartStore.
 * @return Instance of this class.
 */
+ (nonnull instancetype)sharedInstance:(nullable SFUserAccount *)user smartStore:(nullable NSString *)smartStore;

/**
 * Resets all the layout sync managers.
 */
+ (void)reset;

/**
 * Resets the layout sync manager for this user account.
 *
 * @param user User account.
 */
+ (void)reset:(nullable SFUserAccount *)user;

/**
 * Fetches layout data for the specified object type and layout type using the specified
 * mode and triggers the supplied completion block once complete.
 *
 * @param objectType Object type.
 * @param layoutType Layout type. Defaults to "Full" if nil is passed in.
 * @param mode Fetch mode. See SFSDKFetchMode for available modes.
 * @param completionBlock Layout sync completion block.
 */
- (void)fetchLayoutForObject:(nonnull NSString *)objectType
                  layoutType:(nullable NSString *)layoutType
                        mode:(SFSDKFetchMode)mode
             completionBlock:(nonnull SFLayoutSyncCompletionBlock)completionBlock SFSDK_DEPRECATED("8.2", "9.0", "Will be removed in Mobile SDK 9.0, use fetchLayoutForObjectAPIName:objectAPIName:formFactor:layoutType:mode:recordTypeId:syncMode:completionBlock instead.");

/**
 * Fetches layout data for the specified parameters using the specified sync
 * mode and triggers the supplied completion block once complete.
 *
 * @param objectAPIName Object API name.
 * @param formFactor Form factor. Could be "Large", "Medium" or "Small". Default value is "Large".
 * @param layoutType Layout type. Defaults to "Full" if nil is passed in.
 * @param mode Mode. Could be "Create", "Edit" or "View". Default value is "View".
 * @param recordTypeId Record type ID. Default will be used if not supplied.
 * @param syncMode Fetch mode. See SFSDKFetchMode for available modes.
 * @param completionBlock Layout sync completion block.
 */
- (void)fetchLayoutForObjectAPIName:(nonnull NSString *)objectAPIName
                         formFactor:(nullable NSString *)formFactor
                         layoutType:(nullable NSString *)layoutType
                               mode:(nullable NSString *)mode
                       recordTypeId:(nullable NSString *)recordTypeId
                           syncMode:(SFSDKFetchMode)syncMode
                    completionBlock:(nonnull SFLayoutSyncCompletionBlock)completionBlock;

@end
