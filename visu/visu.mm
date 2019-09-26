/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:22:13 by afeuerst          #+#    #+#             */
/*   Updated: 2019/08/30 14:32:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#import <Foundation/Foundation.h>
#import <Appkit/Appkit.h>
#import <SceneKit/SceneKit.h>
#include <math.h>

static __strong NSColor *_blueSkyColor = nil;
static __strong NSColor *_pinkLollypopColor = nil;
static __strong NSColor *_redCorailColor = nil;
static __strong NSColor *_yellowLightningColor = nil;
static __strong NSColor *_blackNightSky = nil;

static NSString *_fourmiName = @"fourmi";

@interface LeminScene: SCNScene

+ (instancetype)sceneWithVisu:(t_visu *const)visu;

- (void)addBall:(t_room *const)room;

- (void)addConection:(const SCNVector3)start end:(const SCNVector3)end;

- (SCNNode *)addLight:(t_room *const)room;
- (void)startFourmiMovement:(t_visu *const)visu;
- (void)startFourmiMovementAtPath:(const int)count index:(const int)index visu:(t_visu *const)visu;

@property(strong, nonatomic) NSTextView *textLabel;
@property(assign, nonatomic) int fourmiCounter;

@end
static __strong LeminScene *_scene;
@implementation LeminScene: SCNScene

- (void)addBall:(t_room *const)room {
	SCNSphere *const			sphere = [SCNSphere sphereWithRadius:BALL_RADIUS];
	SCNNode *const				node = [SCNNode nodeWithGeometry:sphere];

	[[[[sphere materials] firstObject] diffuse] setContents:_pinkLollypopColor];
	[node setPosition:SCNVector3Make(room->x, room->y, room->z)];
	[[self rootNode] addChildNode:node];
}

- (void)addConection:(const SCNVector3)start end:(const SCNVector3)end {
	const SCNVector3 vector = SCNVector3Make(start.x - end.x, start.y - end.y, start.z - end.z);
	const CGFloat len = sqrt(pow(end.x - start.x, 2.0) + pow(end.y - start.y, 2.0) + pow(end.z - start.z, 2.0)) - CONNECT_BALL_SPACE_DIFF;
	SCNCylinder *const cylinder = [SCNCylinder cylinderWithRadius:CONNECT_RADIUS height:len];
	SCNNode *const node = [SCNNode nodeWithGeometry:cylinder];

	[[[cylinder firstMaterial] diffuse] setContents:_redCorailColor];
	[node setPosition:SCNVector3Make((end.x + start.x) / 2.0, (end.y + start.y) / 2.0, (end.z + start.z) / 2.0)];
	[node setEulerAngles:SCNVector3Make(M_PI / 2, acos((end.z - start.z) / len), atan2((end.y - start.y), (end.x - start.x)))];
	[[self rootNode] addChildNode:node];
}

- (SCNNode *)addLight:(t_room *const)room {
	SCNSphere *const			sphere = [SCNSphere sphereWithRadius:FOURMI_RADIUS];
	SCNNode *const				node = [SCNNode nodeWithGeometry:sphere];
	SCNLight *const				light = [SCNLight light];

	[light setType:SCNLightTypeOmni];
	[light setColor:_yellowLightningColor];
	[light setTemperature:5000.0];
	[light setIntensity:100];
	[node setPosition:SCNVector3Make(room->x, room->y, room->z)];
	//[node setLight:light];
	[[[[sphere materials] firstObject] diffuse] setContents:_yellowLightningColor];
	[node setName:_fourmiName];
	[[self rootNode] addChildNode:node];
	return node;
}

+ (instancetype)sceneWithVisu:(t_visu *const)visu {
	__strong LeminScene *const	scene = [LeminScene scene];
	NSInteger					indexPath = 0;
	NSInteger					indexInPath;
	t_room						*l;
	t_room						*r;

	while (visu->paths[indexPath]) {
		indexInPath = 0;
		while (visu->paths[indexPath][indexInPath]) {
			[scene addBall:visu->paths[indexPath][indexInPath]];
			if (visu->paths[indexPath][++indexInPath]) {
				l = visu->paths[indexPath][indexInPath - 1];
				r = visu->paths[indexPath][indexInPath];
				[scene addConection:SCNVector3Make(l->x, l->y, l->z) end:SCNVector3Make(r->x, r->y, r->z)];
			}
		}
		++indexPath;
	}
	return scene;
}

static int						_fourmiCount = 0;
- (void)setFourmiCounter:(int)fourmiCounter {
	if (!fourmiCounter) {
		if (_fourmiCount)
			[[self textLabel] setString:[[[NSString alloc] initWithFormat:@"%d ants", _fourmiCount] autorelease]];
		else
			[[self textLabel] setString:@""];
	}
	else {
		[[self textLabel] setString:[[[NSString alloc] initWithFormat:@"Ants: %d / %d", fourmiCounter, _fourmiCount] autorelease]];
	}
	_fourmiCounter = fourmiCounter;
}
static BOOL						_fourmiState = NO;
static t_visu					*_visu = nil;

- (void)startFourmiMovement:(t_visu *const)visu {
	int							index;

	index = 0;
	_fourmiCount = 0;
	_fourmiState = YES;
	_visu = visu;
	while (index < visu->nb_paths) {
		[self startFourmiMovementAtPath:visu->flux[index] index:index visu:visu];
		_fourmiCount += visu->flux[index];
		++index;
	}
	[self setFourmiCounter:0];
}

- (void)fourmiMovement:(const int)index position:(const int)position node:(SCNNode *const)node visu:(t_visu *const)visu {
	t_room *const				room = visu->paths[index][position + 1];
	SCNAction					*action;

	if (room) {
		action = [SCNAction sequence:@[
									[SCNAction moveTo:SCNVector3Make(room->x, room->y, room->z) duration:DURATION],
									[SCNAction runBlock:^(SCNNode *const node){
										[self fourmiMovement:index position:position + 1 node:node visu:visu];
									} queue:dispatch_get_main_queue()]
									]];
		[node runAction:action];
	}
	else {
		[node removeFromParentNode];
		[self setFourmiCounter:[self fourmiCounter] + 1];
		if ([self fourmiCounter] >= _fourmiCount) {
			_fourmiState = NO;
		}
	}
}
- (void)startFourmiMovementAtPath:(const int)count index:(const int)index visu:(t_visu *const)visu {
	int							c;
	SCNAction					*action;

	c = 0;
	while (c < count)
	{
		action = [SCNAction sequence:@[
									[SCNAction waitForDuration:DURATION * (NSTimeInterval)c],
									[SCNAction runBlock:^(SCNNode *const node){
										SCNNode *const light = [self addLight:visu->paths[index][0]];

										[self fourmiMovement:index position:0 node:light visu:visu];
									} queue:dispatch_get_main_queue()]
							]];
		[[self rootNode] runAction:action];
		++c;
	}
}

@end

@interface NSApplication (Extension)

- (void)closeApplication;
- (void)initializeScene:(t_visu *const)visu;

- (void)setupMenu:(NSString *const)appName;
- (void)actionPlayPause;
- (void)actionReset;

@end
@implementation NSApplication (Extension)

- (void)closeApplication {
	NSLog(@"closeApplication");
	[self terminate:self];
}

static __strong NSWindow *displayWindow = nil;
- (void)initializeScene:(t_visu *const)visu {
	SCNView					*view = [[[SCNView alloc] initWithFrame:NSMakeRect(0, 0, W_SCREEN, H_SCREEN)
																options:@{}] autorelease];
	LeminScene				*scene = [[LeminScene sceneWithVisu:visu] autorelease];

	[view setBackgroundColor:_blackNightSky];
	[view setAllowsCameraControl:YES];
	[view setScene:scene];
	_scene = scene;

	NSRect frameRect = NSMakeRect(36.0, H_SCREEN - (36.0 + 50.0), W_SCREEN - 36.0 * 2.0, 50.0);
	NSTextView *myTextField = [[[NSTextView alloc] initWithFrame:frameRect] autorelease];

	[myTextField setString:@""];
	[myTextField setEditable:NO];
	[myTextField setTextColor:_pinkLollypopColor];
	[myTextField setBackgroundColor:[NSColor clearColor]];
	[myTextField setFont:[NSFont systemFontOfSize:30.0 weight:NSFontWeightBold]];
	[view addSubview:myTextField];
	[[displayWindow contentView] addSubview:view];

	[scene setTextLabel:myTextField];
	[scene startFourmiMovement:visu];
}

- (void)setupMenu:(NSString *const)appName {
	const id		menu = [[[NSMenu alloc] initWithTitle:@"MainMenu"] autorelease];

	const id		appMenuItem = [[[NSMenuItem alloc] initWithTitle:appName action:nil keyEquivalent:@""] autorelease];
	const id		appMenuItemMenu = [[[NSMenu alloc] initWithTitle:appName] autorelease];
	const id		appMenuItemMenuItemAboutName = [[[NSMenuItem alloc] initWithTitle:[[[NSString alloc] initWithFormat:@"About %@", appName] autorelease] action:nil keyEquivalent:@""] autorelease];
	const id		appMenuItemMenuItemSeparator = [[[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""] autorelease];
	const id		appMenuItemMenuItemQuit = [[[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(closeApplication) keyEquivalent:@"q"] autorelease];

	const id		actionMenuItem = [[[NSMenuItem alloc] initWithTitle:@"Actions" action:nil keyEquivalent:@""] autorelease];
	const id		actionMenuItemMenu = [[[NSMenu alloc] initWithTitle:@"Actions"] autorelease];
	const id		actionMenuItemMenuItemPlayPause = [[[NSMenuItem alloc] initWithTitle:@"Play / Pause" action:@selector(actionPlayPause) keyEquivalent:@"p"] autorelease];
	const id		actionMenuItemMenuItemReset = [[[NSMenuItem alloc] initWithTitle:@"Reset" action:@selector(actionReset) keyEquivalent:@"r"] autorelease];

	[appMenuItemMenu addItem:appMenuItemMenuItemAboutName];
	[appMenuItemMenu addItem:appMenuItemMenuItemSeparator];
	[appMenuItemMenu addItem:appMenuItemMenuItemQuit];
	[appMenuItem setSubmenu:appMenuItemMenu];

	[menu addItem:appMenuItem];

	[actionMenuItemMenu addItem:actionMenuItemMenuItemPlayPause];
	[actionMenuItemMenu addItem:actionMenuItemMenuItemReset];
	[actionMenuItem setSubmenu:actionMenuItemMenu];

	[menu addItem:actionMenuItem];
	[self setMainMenu:menu];
}
- (void)actionPlayPause {
	if ([[_scene rootNode] actionKeys] && [[[_scene rootNode] actionKeys] count])
		[_scene setPaused:![_scene isPaused]];
	else
		[_scene startFourmiMovement:_visu];
}
- (void)actionReset {
	_fourmiCount = 0;
	[_scene setFourmiCounter:0];
	[[_scene rootNode] removeAllActions];
	for (SCNNode *const node in [[_scene rootNode] childNodes]) {
		if ([node name]) {
			[node removeFromParentNode];
		}
	}
}

@end


void							launch_visual(t_visu *const visu)
{
	const NSApplication			*application = [NSApplication sharedApplication];
	NSString *const				appname = [[NSProcessInfo processInfo] processName];
	const NSAutoreleasePool		*pool = [[NSAutoreleasePool alloc] init];

	const id					window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, W_SCREEN, H_SCREEN)
																	  styleMask:NSWindowStyleMaskTitled
																	    backing:NSBackingStoreBuffered defer:NO] autorelease];
	[application setActivationPolicy:NSApplicationActivationPolicyRegular];
	[application setupMenu:appname];
	[window cascadeTopLeftFromPoint:NSMakePoint(180, 320)];
	[window setTitle:appname];
	[window makeKeyAndOrderFront:nil];
	[application activateIgnoringOtherApps:YES];

	displayWindow = window;
	_blueSkyColor = [NSColor colorWithSRGBRed:171.0/255.0 green:241.0/255.0 blue:1.0 alpha:1.0];
	_pinkLollypopColor = [NSColor colorWithSRGBRed:1.0 green:171.0/255.0 blue:234.0/255.0 alpha:0.8];
	_redCorailColor = [NSColor colorWithSRGBRed:1.0 green:146.0/255.0 blue:135.0/255.0 alpha:0.1];
	_yellowLightningColor = [NSColor colorWithSRGBRed:1.0 green:1.0 blue:24.0/255.0 alpha:1.0];
	_blackNightSky = [NSColor colorWithSRGBRed:4.0/255.0 green:35.0/255.0 blue:40.0/255.0 alpha:1.0];
	[application initializeScene:visu];

	[application run];
}
