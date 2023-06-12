#pragma once

#include "Includes.hpp"
#include "subprocess.hpp"
#include <Geode/cocos/platform/CCGL.h>
#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/cocos/CCDirector.h>

namespace Renderer {
    static inline CCTexture2D* renderingTexture;
    static inline GLint m_pOldFBO;
    static inline GLuint m_pFBO;
    static inline GLint m_pOldRBO;
    static inline std::vector<GLubyte> currentFrameData;
    static inline bool currentFrameHasData;
    static inline std::mutex threadLock;
    static inline int currentFrame;

    void beginRender(); //done
    void renderingThread(); //done
    void visitPlayLayer(); //done
    void updateRenderer(); //done
    void drawObjectLayer(CCLayer*); //done
}