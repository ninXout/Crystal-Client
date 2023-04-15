#include <cocos2d.h>
#include <Geode/modify/CCTouchDispatcher.hpp>
#include <Geode/modify/CCIMEDispatcher.hpp>
#include <Geode/modify/CCMouseDispatcher.hpp>
#include "CrystalClient.hpp"
#include "ImGui.hpp"

using namespace cocos2d;

// most if not all taken from https://github.com/geode-sdk/DevTools

static void drawTriangle(const std::array<CCPoint, 3>& poli, const std::array<ccColor4F, 3>& colors, const std::array<CCPoint, 3>& uvs) {
    auto* shader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
    shader->use();
    shader->setUniformsForBuiltins();

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

    static_assert(sizeof(CCPoint) == sizeof(ccVertex2F), "so the cocos devs were right then");
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, poli.data());
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors.data());
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, uvs.data());

    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
}

ImGuiKey cocos_to_imkey(cocos2d::enumKeyCodes key) {
	switch (key) {
		case enumKeyCodes::KEY_A: return ImGuiKey_A;
		case enumKeyCodes::KEY_B: return ImGuiKey_B;
		case enumKeyCodes::KEY_C: return ImGuiKey_C;
		case enumKeyCodes::KEY_D: return ImGuiKey_D;
		case enumKeyCodes::KEY_E: return ImGuiKey_E;
		case enumKeyCodes::KEY_F: return ImGuiKey_F;
		case enumKeyCodes::KEY_G: return ImGuiKey_G;
		case enumKeyCodes::KEY_H: return ImGuiKey_H;
		case enumKeyCodes::KEY_I: return ImGuiKey_I;
		case enumKeyCodes::KEY_J: return ImGuiKey_J;
		case enumKeyCodes::KEY_K: return ImGuiKey_K;
		case enumKeyCodes::KEY_L: return ImGuiKey_L;
		case enumKeyCodes::KEY_M: return ImGuiKey_M;
		case enumKeyCodes::KEY_N: return ImGuiKey_N;
		case enumKeyCodes::KEY_O: return ImGuiKey_O;
		case enumKeyCodes::KEY_P: return ImGuiKey_P;
		case enumKeyCodes::KEY_Q: return ImGuiKey_Q;
		case enumKeyCodes::KEY_R: return ImGuiKey_R;
		case enumKeyCodes::KEY_S: return ImGuiKey_S;
		case enumKeyCodes::KEY_T: return ImGuiKey_T;
		case enumKeyCodes::KEY_U: return ImGuiKey_U;
		case enumKeyCodes::KEY_V: return ImGuiKey_V;
		case enumKeyCodes::KEY_W: return ImGuiKey_W;
		case enumKeyCodes::KEY_X: return ImGuiKey_X;
		case enumKeyCodes::KEY_Y: return ImGuiKey_Y;
		case enumKeyCodes::KEY_Z: return ImGuiKey_Z;

		case enumKeyCodes::KEY_Zero: return ImGuiKey_0;
		case enumKeyCodes::KEY_One: return ImGuiKey_1;
		case enumKeyCodes::KEY_Two: return ImGuiKey_2;
		case enumKeyCodes::KEY_Three: return ImGuiKey_3;
		case enumKeyCodes::KEY_Four: return ImGuiKey_4;
		case enumKeyCodes::KEY_Five: return ImGuiKey_5;
		case enumKeyCodes::KEY_Six: return ImGuiKey_6;
		case enumKeyCodes::KEY_Seven: return ImGuiKey_7;
		case enumKeyCodes::KEY_Eight: return ImGuiKey_8;
		case enumKeyCodes::KEY_Nine: return ImGuiKey_9;

		case enumKeyCodes::KEY_ArrowUp: return ImGuiKey_UpArrow;
		case enumKeyCodes::KEY_ArrowDown: return ImGuiKey_DownArrow;
		case enumKeyCodes::KEY_ArrowLeft: return ImGuiKey_LeftArrow;
		case enumKeyCodes::KEY_ArrowRight: return ImGuiKey_RightArrow;

		default: return ImGuiKey_None;
	}
}

void CrystalClient::keyDown(cocos2d::enumKeyCodes key) {
	ImGui::GetIO().AddKeyEvent(cocos_to_imkey(key), true);
}

void CrystalClient::keyUp(cocos2d::enumKeyCodes key) {
	ImGui::GetIO().AddKeyEvent(cocos_to_imkey(key), false);
}

void CrystalClient::insertText(const char* text, int len) {
	std::string str(text, len);
	ImGui::GetIO().AddInputCharactersUTF8(str.c_str());
}

void CrystalClient::deleteBackward() {
	// is this really how youre supposed to do this
	ImGui::GetIO().AddKeyEvent(ImGuiKey_Backspace, true);
	ImGui::GetIO().AddKeyEvent(ImGuiKey_Backspace, false);
}

void CrystalClient::setupPlatform() {
    ImGui::CreateContext();

    auto& io = ImGui::GetIO();

    io.BackendPlatformUserData = this;
    io.BackendPlatformName = "cocos2d-2.2.3 GD";
    // this is a lie hehe
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    auto* tex2d = new CCTexture2D;
    tex2d->initWithData(pixels, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height));

    // TODO: not leak this :-)
    tex2d->retain();

    io.Fonts->SetTexID((ImTextureID)(uintptr_t)tex2d->getName());
}

void CrystalClient::newFrame() {
    auto& io = ImGui::GetIO();

    auto* director = CCDirector::sharedDirector();
    const auto winSize = director->getWinSize();
    const auto frameSize = director->getOpenGLView()->getFrameSize();

    // glfw new frame
    io.DisplaySize = ImVec2(frameSize.width, frameSize.height);
    io.DisplayFramebufferScale = ImVec2(
        winSize.width / frameSize.width,
        winSize.height / frameSize.height
    );
    io.DeltaTime = director->getDeltaTime();

#ifdef GEODE_IS_WINDOWS
    // not in cocos coords!! frame coords instead
    const auto mouse_pos = director->getOpenGLView()->getMousePosition();
    io.AddMousePosEvent(mouse_pos.x, mouse_pos.y);
#endif

    auto* kb = director->getKeyboardDispatcher();
    io.KeyAlt = kb->getAltKeyPressed() || kb->getCommandKeyPressed(); // look
    io.KeyCtrl = kb->getControlKeyPressed();
    io.KeyShift = kb->getShiftKeyPressed();
}

void CrystalClient::render() {
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    this->newFrame();

    ImGui::NewFrame();

    CrystalClient::get()->draw();

    ImGui::Render();

    this->renderDrawData(ImGui::GetDrawData());
}

void CrystalClient::renderDrawData(ImDrawData* draw_data) {
    glEnable(GL_SCISSOR_TEST);

    const auto clip_scale = draw_data->FramebufferScale;

    for (int i = 0; i < draw_data->CmdListsCount; ++i) {
        auto* list = draw_data->CmdLists[i];
        auto* idxBuffer = list->IdxBuffer.Data;
        auto* vtxBuffer = list->VtxBuffer.Data;
        for (auto& cmd : list->CmdBuffer) {
            // TODO: not gonna work on 64 bit
            ccGLBindTexture2D((GLuint)(uintptr_t)cmd.GetTexID());

            const auto rect = cmd.ClipRect;
            const auto orig = toCocos(ImVec2(rect.x, rect.y));
            const auto end = toCocos(ImVec2(rect.z, rect.w));
            if (end.x <= orig.x || end.y >= orig.y)
                continue;
            CCDirector::sharedDirector()->getOpenGLView()->setScissorInPoints(orig.x, end.y, end.x - orig.x, orig.y - end.y);

            for (unsigned int i = 0; i < cmd.ElemCount; i += 3) {
                const auto a = vtxBuffer[idxBuffer[cmd.IdxOffset + i + 0]];
                const auto b = vtxBuffer[idxBuffer[cmd.IdxOffset + i + 1]];
                const auto c = vtxBuffer[idxBuffer[cmd.IdxOffset + i + 2]];
                std::array<CCPoint, 3> points = {
                    toCocos(a.pos),
                    toCocos(b.pos),
                    toCocos(c.pos),
                };
                static constexpr auto ccc4FromImColor = [](const ImColor color) {
                    // beautiful
                    return ccc4f(color.Value.x, color.Value.y, color.Value.z, color.Value.w);
                };
                std::array<ccColor4F, 3> colors = {
                    ccc4FromImColor(a.col),
                    ccc4FromImColor(b.col),
                    ccc4FromImColor(c.col),
                };

                std::array<CCPoint, 3> uvs = {
                    ccp(a.uv.x, a.uv.y),
                    ccp(b.uv.x, b.uv.y),
                    ccp(c.uv.x, c.uv.y),
                };

                drawTriangle(points, colors, uvs);
            }
        }
    }

    glDisable(GL_SCISSOR_TEST);
}

enum TouchMessageType : unsigned int {
    Began = 0,
    Moved = 1,
    Ended = 2,
    Cancelled = 3
};

class $modify(CCMouseDispatcher) {
    bool dispatchScrollMSG(float y, float x) {
        auto& io = ImGui::GetIO();
        io.AddMouseWheelEvent(x / 5, y / 5);

        if (!io.WantCaptureMouse) {
            return CCMouseDispatcher::dispatchScrollMSG(y, x);
        }

        return true;
    }
};

class $modify(CCTouchDispatcher) {
    void touches(CCSet* touches, CCEvent* event, unsigned int type) {
        auto& io = ImGui::GetIO();
        auto* touch = static_cast<CCTouch*>(touches->anyObject());
        const auto pos = toVec2(touch->getLocation());
        io.AddMousePosEvent(pos.x, pos.y);
        if (io.WantCaptureMouse) {
            if (type == TouchMessageType::Began || type == TouchMessageType::Moved) {
                io.AddMouseButtonEvent(0, true);
            } else {
                io.AddMouseButtonEvent(0, false);
            }
        } else {
            if (type != TouchMessageType::Moved) {
                io.AddMouseButtonEvent(0, false);
            }
            if (!CrystalClient::get()->isMenuOpen) {
                CCTouchDispatcher::touches(touches, event, type);
            }
        }
    }
};

class $modify(CCIMEDispatcher) {
    void dispatchInsertText(const char* text, int len) {
        auto& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) {
            CCIMEDispatcher::dispatchInsertText(text, len);
        }
        std::string str(text, len);
        io.AddInputCharactersUTF8(str.c_str());
    }

    void dispatchDeleteBackward() {
        auto& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) {
            CCIMEDispatcher::dispatchDeleteBackward();
        }
        io.AddKeyEvent(ImGuiKey_Backspace, true);
        io.AddKeyEvent(ImGuiKey_Backspace, false);
    }
};