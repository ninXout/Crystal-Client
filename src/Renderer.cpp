#include "Includes.hpp"
#include "CrystalProfile.hpp"
#include "Renderer.hpp"

using namespace Renderer;
using namespace Crystal;

std::string getOffsetTime(float time) {
    std::stringstream ret;
    ret << "00:";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time / 60)) << ":";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time) % 60);
    return ret.str();
}

void Renderer::beginRender() {
    currentFrame = 0;
    currentFrameData.clear();
    currentFrameHasData = false;

    // make resolution even if it somehow isn't
    if(profile.targetWidth % 2 != 0) profile.targetWidth--;
    if(profile.targetHeight % 2 != 0) profile.targetHeight--;

    // render at higher resolution
    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &m_pOldFBO);

    auto data = malloc(profile.targetWidth * profile.targetHeight * 4);
    memset(data, 0, profile.targetWidth * profile.targetHeight * 4);

    renderingTexture = new CCTexture2D();
    renderingTexture->initWithData(data, kCCTexture2DPixelFormat_RGB888, profile.targetWidth, profile.targetHeight, CCSize(static_cast<float>(profile.targetWidth), static_cast<float>(profile.targetHeight)));

    free(data);

    glGetIntegerv(GL_RENDERBUFFER_BINDING_EXT, &m_pOldRBO);
    glGenFramebuffersEXT(1, &m_pFBO);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_pFBO);

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, renderingTexture->getName(), NULL);

    renderingTexture->setAliasTexParameters();
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_pOldFBO);
    glBindFramebufferEXT(GL_RENDERBUFFER_EXT, m_pOldRBO);

    // start rendering thread
    std::thread(renderingThread).detach();
}

void Renderer::renderingThread() {
    auto dir = CCDirector::sharedDirector();

    int frameW = profile.targetWidth;
    int frameH = profile.targetHeight;

    auto pLayer = GameManager::sharedState()->getPlayLayer();
    auto levelData = pLayer->m_level;    

    auto levelSettings = pLayer->m_levelSettings;

    std::string songPath;
    if(profile.includeAudio) {
        songPath = levelData->getAudioFileName();

        if(songPath.find("/") == songPath.npos) {
            songPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(songPath.c_str(), true);
        }
    }

    auto renderer = Mod::get()->getConfigDir().append("Amethyst").append("Renderer");

    std::stringstream rendercmd;
    rendercmd << "cd \"" + std::string(Mod::get()->getResourcesDir()) + "\" && ./ffmpeg -framerate 60 -y -f rawvideo -i -";
    if (profile.includeAudio) rendercmd << " -ss " + getOffsetTime(PlayLayer::get()->m_levelSettings->m_songOffset) + " -i " + songPath;
    rendercmd << " -t " + std::to_string(PlayLayer::get()->m_time) + " -pix_fmt rgba -vb 20M -c:v libx264 \"" + (std::string)renderer + "/" + (std::string)profile.rendername + ".mp4\"";

    //struct subprocess_s subprocess;
    //int result = subprocess_create(rendercmd.str().c_str(), 0, &subprocess);
    //auto process = subprocess::Popen(cmd.getCommandStr(), creationFlag);

    // rendering loop
    while (profile.renderer || currentFrameHasData) {
        // check if error occured
        //if(process.getExitCode() == 1) {
            //lastInfoCode = 1;
                
            //break;
        //}

        threadLock.lock();
        if(currentFrameHasData) {
            const auto frameData = currentFrameData;
            currentFrameData.clear();
            currentFrameHasData = false;

            // write frame data to ffmpeg
            //FILE* p_stdin = subprocess_stdin(&subprocess);
            //fputs((const char*)frameData.data(), p_stdin);
            //fputs((const char*)frameData.size(), p_stdin);
            //process.m_stdin.write(frameData.data(), frameData.size());
        } 

        threadLock.unlock();
    }

    threadLock.lock();
    threadLock.unlock();
}

void Renderer::updateRenderer() {
    auto dir = CCDirector::sharedDirector();
    auto texSize = dir->getOpenGLView()->getFrameSize();

    int frameW = profile.targetWidth;
    int frameH = profile.targetHeight;

    std::vector<GLubyte> frameData;
    frameData.resize(frameW * frameH * 4);

    glViewport(0, 0, frameW, frameH);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &m_pOldFBO);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_pFBO);
        
    visitPlayLayer(); // draw PlayLayer

    // pixels
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, frameW, frameH, GL_RGBA, GL_UNSIGNED_BYTE, frameData.data());

    // reset viewport
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_pOldFBO);
    dir->setViewport();

    // set data
    threadLock.lock();
    currentFrameData = frameData;
    currentFrameHasData = true;
    threadLock.unlock();
}

void Renderer::drawObjectLayer(CCLayer* m_objectLayer) {
    kmGLPushMatrix();

    if(m_objectLayer->getGrid() != nullptr) {
        if(m_objectLayer->getGrid()->isActive())
            m_objectLayer->getGrid()->beforeDraw();
    }

    m_objectLayer->transform();
    m_objectLayer->sortAllChildren();

    bool drawnObjectLayer = false;
    for(size_t i = 0; i < m_objectLayer->getChildrenCount(); i++) {
        auto child = (CCNode*)m_objectLayer->getChildren()->objectAtIndex(i);

        if(child->getZOrder() < 0) {
            child->visit();
        }
        else {
            if(!drawnObjectLayer) {
                m_objectLayer->draw();
                drawnObjectLayer = true;
            }

            child->visit();
        }
    }

    m_objectLayer->setOrderOfArrival(0);

    if(m_objectLayer->getGrid() != nullptr) {
        if(m_objectLayer->getGrid()->isActive())
            m_objectLayer->getGrid()->afterDraw(m_objectLayer);
    }

    kmGLPopMatrix();
    /////////////////////////////
}

void Renderer::visitPlayLayer() {
    auto pLayer = GameManager::sharedState()->getPlayLayer();

    kmGLPushMatrix();

    if(pLayer->getGrid() != nullptr) {
        if(pLayer->getGrid()->isActive())
            pLayer->getGrid()->beforeDraw();
    }

    pLayer->transform();
    pLayer->sortAllChildren();

    // PlayLayer
    bool drawnPlayLayer = false;
    for(size_t i = 0; i < pLayer->getChildrenCount(); i++) {
        auto child = (CCNode*)pLayer->getChildren()->objectAtIndex(i);

        // Object Layer
        if(pLayer->m_objectLayer->m_uID == child->m_uID) {
            drawObjectLayer(pLayer->m_objectLayer);
            continue;
        }

        if(child->getZOrder() < 0) {
            child->visit();
        }
        else {
            if(!drawnPlayLayer) {
                pLayer->draw();
                drawnPlayLayer = true;
            }

            child->visit();
        }
    }

    pLayer->setOrderOfArrival(0);

    if(pLayer->getGrid() != nullptr) {
        if(pLayer->getGrid()->isActive())
            pLayer->getGrid()->afterDraw(pLayer);
    }
    
    kmGLPopMatrix();
}
