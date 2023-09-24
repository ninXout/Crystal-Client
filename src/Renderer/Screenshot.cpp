#include "Screenshot.hpp"

#ifdef GEODE_IS_MACOS
Screenshot Screenshot::create() {
    Screenshot ret;
    return ret;
}

CGImageRef Screenshot::CGImageFromCCImage(CCImage* img) {
    float width = img->getWidth();
    float height = img->getHeight();
    int dataLen = width * height * 4;

    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, img->getData(), dataLen, NULL);

    return CGImageCreate(
        width, height, 
        8, 8 * 4, width * 4, 
        CGColorSpaceCreateDeviceRGB(), 
        kCGBitmapByteOrderDefault | kCGImageAlphaPremultipliedLast, 
        provider,   // data provider
        NULL,       // decode
        true,        // should interpolate
        kCGRenderingIntentDefault
    );
}

bool Screenshot::CGImageWriteToFile(CGImageRef image) {
    std::string name = std::string("/Users/") + getenv("USER") + "/Downloads/";
    int iter = 0;
    while (ghc::filesystem::exists(name + std::to_string(PlayLayer::get()->m_level->m_levelID) + "-" + std::to_string(iter) + ".png")) {
        iter++;
    }
    name += std::to_string(PlayLayer::get()->m_level->m_levelID) + "-" + std::to_string(iter) + ".png";

    CFStringRef file = CFStringCreateWithCString(kCFAllocatorDefault,
    name.c_str(),
    kCFStringEncodingMacRoman);
    CFStringRef type = CFSTR("public.png");
    CFURLRef urlRef = CFURLCreateWithFileSystemPath( kCFAllocatorDefault, file, kCFURLPOSIXPathStyle, false );
    CGImageDestinationRef destination = CGImageDestinationCreateWithURL( urlRef, kUTTypePNG, 1, NULL );
    CGImageDestinationAddImage( destination, image, NULL );
    CGImageDestinationFinalize( destination );
    if (!destination) {
        return false;
    }

    CGImageDestinationAddImage(destination, image, nil);

    if (!CGImageDestinationFinalize(destination)) {
        CFRelease(destination);
        return false;
    }

    CFRelease(destination);
    return true;
}

void Screenshot::saveImage(bool toClipboard) {
    auto size = CCDirector::sharedDirector()->getWinSize();
    auto renderer = CCRenderTexture::create(size.width, size.height, cocos2d::kCCTexture2DPixelFormat_RGBA8888);

    renderer->begin();
    if (static_cast<CCNode*>(PlayLayer::get())->getChildrenCount()) {
        CCArrayExt<CCNode*> children = PlayLayer::get()->getChildren();
        for (auto* child : children) {
            using namespace std::literals::string_view_literals;
            if ((typeinfo_cast<CCLabelBMFont*>(child) && typeinfo_cast<CCLabelBMFont*>(child)->getString() == "Testmode"sv) || child->getZOrder() == 1000) {
                if (getVar<bool>("SS_displays")) child->visit();
            } else if (child == static_cast<CCNode*>(PlayLayer::get()->m_player1) || child == static_cast<CCNode*>(PlayLayer::get()->m_player2)) {
                if (getVar<bool>("SS_players")) child->visit();
            } else {
                child->visit();
            }
        }
    }
    renderer->end();

    auto img = renderer->newCCImage(true);
    CGImageWriteToFile(CGImageFromCCImage(img));    
}
#endif