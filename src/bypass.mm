#include <Geode/Geode.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include <Cocoa/Cocoa.h>
#include "globalBP.h"
#include <mutex>

inline std::mutex eventMutex;
inline std::vector<NSEvent*> eventQueue;

USE_GEODE_NAMESPACE();

bool s_leftMouse;
class $(MyScheduler, CCScheduler) {
	void update(float dt) {
		if (dt < 0) {
			CCScheduler::update(-dt);
		} else {
			s_leftMouse = ([NSEvent pressedMouseButtons] & (1 << 0)) != 0;
		}
	}
};

@implementation NSTimer(BypassCallback)
	+(void)bypass:(id)idk {
		static double s_prevTime = 0.0;

		double currentTime = [[NSDate date] timeIntervalSince1970];
		double dt = currentTime - s_prevTime;
		if (s_prevTime < 0.00001)
		    dt = 1.0 / g_fps;

		s_prevTime = currentTime;

		auto view = NSApp.mainWindow.contentViewController.view;

		bool leftMouse = ([NSEvent pressedMouseButtons] & (1 << 0)) != 0;
		if (leftMouse != s_leftMouse) {
			NSEvent* ev = [NSEvent eventWithCGEvent: CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, [NSEvent mouseLocation], kCGMouseButtonLeft)];

			if (leftMouse) {
				[view mouseDown: ev];
			} else {
				[view mouseUp: ev];
			}
		}

		CCDirector::sharedDirector()->getScheduler()->update(-dt);
	}
@end

void updateFPS(double spf) {
	static NSTimer* ml = nil;
	if (ml != nil) {
	    [ml invalidate];
	}

	ml = [NSTimer timerWithTimeInterval: 1.0 / spf
	                                      target: [NSTimer class]
	                                    selector: @selector(bypass:)
	                                    userInfo: nil 
	                                     repeats: YES];
	[[NSRunLoop currentRunLoop] addTimer:ml forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:ml forMode:NSEventTrackingRunLoopMode];
}


//GEODE_API bool GEODE_DLL geode_load(Mod* m) {
    //Loader::get()->queueInGDThread([m](){
		
    //});
	//updateFPS(g_fps);
    //return true;
//}