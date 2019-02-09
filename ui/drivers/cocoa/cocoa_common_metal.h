/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2013-2014 - Jason Fetters
 *  Copyright (C) 2011-2017 - Daniel De Matteis
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __COCOA_COMMON_METAL_H
#define __COCOA_COMMON_METAL_H

#include <Foundation/Foundation.h>

#ifdef HAVE_MENU
#include "../../menu/menu_setting.h"
#include "../../menu/menu_driver.h"
#endif

#include "cocoa_common_shared.h"

typedef enum apple_view_type {
   APPLE_VIEW_TYPE_NONE,
   APPLE_VIEW_TYPE_OPENGL_ES,
   APPLE_VIEW_TYPE_OPENGL,
   APPLE_VIEW_TYPE_VULKAN,
   APPLE_VIEW_TYPE_METAL,
} apple_view_type_t;

#ifdef HAVE_METAL
#import <MetalKit/MetalKit.h>

@interface MetalView : MTKView
@end

#endif

@protocol ApplePlatform

/*! @brief renderView returns the current render view based on the viewType */
@property (readonly) id renderView;

/*! @brief isActive returns true if the application has focus */
@property (readonly) bool hasFocus;

@property (readwrite) apple_view_type_t viewType;

/*! @brief setVideoMode adjusts the video display to the specified mode */
- (void)setVideoMode:(gfx_ctx_mode_t)mode;

/*! @brief setCursorVisible specifies whether the cursor is visible */
- (void)setCursorVisible:(bool)v;

/*! @brief controls whether the screen saver should be disabled and
 * the displays should not sleep.
 */
- (bool)setDisableDisplaySleep:(bool)disable;
@end

extern id<ApplePlatform> apple_platform;

#if defined(HAVE_COCOATOUCH)
#include <UIKit/UIKit.h>

@interface CocoaView : UIViewController<CLLocationManagerDelegate,
AVCaptureAudioDataOutputSampleBufferDelegate>
+ (CocoaView*)get;
@end

@interface RetroArch_iOS : UINavigationController<UIApplicationDelegate,
UINavigationControllerDelegate, ApplePlatform>

@property (nonatomic) UIWindow* window;
@property (nonatomic) NSString* documentsDirectory;
@property (nonatomic) RAMenuBase* mainmenu;
@property (nonatomic) int menu_count;

+ (RetroArch_iOS*)get;

- (void)showGameView;
- (void)toggleUI;
- (void)supportOtherAudioSessions;

- (void)refreshSystemConfig;
- (void)mainMenuPushPop: (bool)pushp;
- (void)mainMenuRefresh;
@end

void get_ios_version(int *major, int *minor);

#endif

#endif
