#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/CVDisplayLink.h>
#include "hackpro.hpp"

using namespace cocos2d;


// don't wanna RE, so i'm just gonna make a stub for the thing i want
struct directorStructure {
	char a[0x10];
	NSTimer* renderTimer;
}; 

// the original drawScene calls CCScheduler::update, but we already do that. this removes it.
class CustomDirector : public cocos2d::CCDirector {
 public:
	void drawScene2() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (m_pNextScene) {
		    setNextScene();
		}

		glPushMatrix();

		if (m_pRunningScene) {
		    m_pRunningScene->visit();
		}

		if (m_pNotificationNode) {
		    m_pNotificationNode->visit();
		}
		
		glPopMatrix();

		m_uTotalFrames++;

		if (m_pobOpenGLView) {
		    m_pobOpenGLView->swapBuffers();
		}
	}

	int getFrames() {
		return m_uTotalFrames;
	}
};

@interface BypassTimerCaller : NSObject
	- (void)timerFired:(id)ok;
	- (void)render:(id)ok;
@end

@implementation BypassTimerCaller

	// update the scheduler
	- (void)timerFired:(id)ok {
		auto cur_time = [[NSDate date] timeIntervalSince1970];
		auto dt = cur_time - time_since;
		auto intended_dt = 1.0/g_fps;

		if (time_since < 0.00001)
			dt = intended_dt;
		time_since = cur_time;

		// make up for deviations of previous timer fire

		//dt = intended_dt + (intended_dt - dt);

		CCDirector::sharedDirector()->getScheduler()->update(dt);

		[self render:nil];

	}

	// render, this must be done on the normal 60fps
	- (void)render:(id)_ {
			auto cur_time = [[NSDate date] timeIntervalSince1970];

			NSOpenGLView* openGLView = NSApp.mainWindow.contentView;
			NSOpenGLContext* glContext = openGLView.openGLContext;


			[glContext makeCurrentContext];
			CGLLockContext(glContext.CGLContextObj);
		    
			((CustomDirector*)cocos2d::CCDirector::sharedDirector())->drawScene2();

			[glContext flushBuffer];
			//glFlush();
		    printf("%lf\n", [[NSDate date] timeIntervalSince1970]-cur_time);
			CGLUnlockContext(glContext.CGLContextObj);

			// events, like keyboard/mouse. uses C
			[(id)[NSClassFromString(@"CCEventDispatcher") sharedDispatcher] dispatchQueuedEvents];
	}
@end

BypassTimerCaller* bypassTimer;
NSTimer* renderg = nil;


// hook ccdirectorcaller to use our timers
void setInterval(directorStructure* caller, void*, double a) {
	[caller->renderTimer invalidate];
	caller->renderTimer = nil;
	caller->renderTimer = [NSTimer timerWithTimeInterval:1.0/g_fps
										  target:(id)bypassTimer
										selector:@selector(timerFired:)
										userInfo:nil
										 repeats:YES];
	
	[[NSRunLoop currentRunLoop] addTimer:caller->renderTimer 
								 forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:caller->renderTimer 
								 forMode:NSEventTrackingRunLoopMode];
}

GEODE_API bool GEODE_DLL geode_load(geode::Mod* m) {
	int interval = 0;
	bypassTimer = [[BypassTimerCaller alloc] init];
	[((NSOpenGLView*)NSApplication.sharedApplication.mainWindow.contentView).openGLContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
	//geode::Loader::get()->init(m);

	m->addHook<&setInterval, geode::core::meta::DefaultConv>("Balls and Cock", (void*)(geode::base::get() + 0x1da750));
	return true;
}