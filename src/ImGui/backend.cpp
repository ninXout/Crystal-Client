#include <Geode/Geode.hpp>
#include <imgui.h>
#include "ImGui.hpp"
#include "../CrystalProfile.hpp"

using namespace geode::prelude;

ImGuiCocos& ImGuiCocos::get() {
	static ImGuiCocos inst;
	return inst;
}

ImGuiCocos::ImGuiCocos() {
	m_setupCall = m_drawCall = [] {};
}

ImGuiCocos& ImGuiCocos::setup(std::function<void()> fun) {
	m_setupCall = fun;
	return this->setup();
}

ImGuiCocos& ImGuiCocos::draw(std::function<void()> fun) {
	m_drawCall = fun;
	return *this;
}

void ImGuiCocos::toggle() {
	auto platform = reinterpret_cast<PlatformToolbox*>(AppDelegate::get());
    if (!m_visible) {
		//ImGui::LoadIniSettingsFromDisk((Mod::get()->getSaveDir() / "imgui.ini").c_str());
		platform->showCursor();
	}
    if (m_visible) {
		//ImGui::SaveIniSettingsToDisk((Mod::get()->getSaveDir() / "imgui.ini").c_str());
		Crystal::saveMods(Crystal::profile);
        if (PlayLayer::get() && !PlayLayer::get()->m_isPaused && !PlayLayer::get()->m_hasLevelCompleteMenu) platform->hideCursor();
    }
	this->setVisible(!m_visible);
}

void ImGuiCocos::setVisible(bool v) {
	m_visible = v;
	if (!m_visible) {
		auto& io = ImGui::GetIO();
		io.WantCaptureKeyboard = false;
		io.WantCaptureMouse = false;
		io.WantTextInput = false;
	}
}

bool ImGuiCocos::isVisible() {
	return m_visible;
}

ImGuiCocos& ImGuiCocos::setup() {
	if (m_initialized) return *this;

	ImGui::CreateContext();

	auto& io = ImGui::GetIO();

	io.BackendPlatformName = "gd-imgui-cocos + Geode";
	io.BackendPlatformUserData = this;

	// use static since imgui does not own the pointer!
	static const auto iniPath = (Mod::get()->getSaveDir() / "imgui.ini").string();
	io.IniFilename = iniPath.c_str();

	m_initialized = true;

	// call the setup function before creating the font texture,
	// to allow for custom fonts
	m_setupCall();

	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	m_fontTexture = new CCTexture2D;
	m_fontTexture->initWithData(pixels, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(static_cast<float>(width), static_cast<float>(height)));

	io.Fonts->SetTexID(reinterpret_cast<ImTextureID>(static_cast<std::uintptr_t>(m_fontTexture->getName())));

	return *this;
}

void ImGuiCocos::destroy() {
	if (!m_initialized) return;

	ImGui::DestroyContext();
	delete m_fontTexture;
	m_initialized = false;
}

ImVec2 ImGuiCocos::cocosToFrame(const CCPoint& pos) {
	auto* director = CCDirector::sharedDirector();
	const auto frameSize = director->getOpenGLView()->getFrameSize();
	const auto winSize = director->getWinSize();

	return ImVec2(
		pos.x / winSize.width * frameSize.width,
		(1.f - pos.y / winSize.height) * frameSize.height
	);
}

CCPoint ImGuiCocos::frameToCocos(const ImVec2& pos) {
	auto* director = CCDirector::sharedDirector();
	const auto frameSize = director->getOpenGLView()->getFrameSize();
	const auto winSize = director->getWinSize();

	return CCPoint(
		pos.x / frameSize.width * winSize.width,
		(1.f - pos.y / frameSize.height) * winSize.height
	);
}

void ImGuiCocos::drawFrame() {
	if (!m_initialized || !m_visible) return;

	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// starts a new frame for imgui
	this->newFrame();
	ImGui::NewFrame();

	// actually draws stuff with imgui functions
	m_drawCall();

	// renders the triangles onto the screen
	ImGui::Render();
	this->renderFrame();
}

void ImGuiCocos::newFrame() {
	auto& io = ImGui::GetIO();
	
	// opengl2 new frame
	auto* director = CCDirector::sharedDirector();
	const auto winSize = director->getWinSize();
	const auto frameSize = director->getOpenGLView()->getFrameSize();

	// glfw new frame
	io.DisplaySize = ImVec2(frameSize.width, frameSize.height);
	io.DisplayFramebufferScale = ImVec2(
		winSize.width / frameSize.width,
		winSize.height / frameSize.height
	);
	//io.DeltaTime = director->getDeltaTime();

	//const auto mouse = cocosToFrame(geode::cocos::getMousePos());
	//io.AddMousePosEvent(mouse.x, mouse.y);

	auto* kb = director->getKeyboardDispatcher();
	io.KeyAlt = kb->getAltKeyPressed() || kb->getCommandKeyPressed(); // look
	io.KeyCtrl = kb->getControlKeyPressed();
	io.KeyShift = kb->getShiftKeyPressed();
}

void ImGuiCocos::renderFrame() {
	auto* drawData = ImGui::GetDrawData();

	glEnable(GL_SCISSOR_TEST);

	GLuint vao = 0;
	GLuint vbos[2] = {0, 0};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &vbos[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);

	glEnableVertexAttribArray(kCCVertexAttrib_Position);
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), reinterpret_cast<void*>(offsetof(ImDrawVert, pos)));

	glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), reinterpret_cast<void*>(offsetof(ImDrawVert, uv)));

	glEnableVertexAttribArray(kCCVertexAttrib_Color);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), reinterpret_cast<void*>(offsetof(ImDrawVert, col)));

	auto* shader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
	shader->use();
	shader->setUniformsForBuiltins();

	for (int i = 0; i < drawData->CmdListsCount; ++i) {
		auto* list = drawData->CmdLists[i];

		// convert vertex coords to cocos space
		for (int j = 0; j < list->VtxBuffer.size(); j++) {
			const auto point = frameToCocos(list->VtxBuffer[j].pos);
			list->VtxBuffer[j].pos = ImVec2(point.x, point.y);
		}

		glBufferData(GL_ARRAY_BUFFER, list->VtxBuffer.Size * sizeof(ImDrawVert), list->VtxBuffer.Data, GL_STREAM_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, list->IdxBuffer.Size * sizeof(ImDrawIdx), list->IdxBuffer.Data, GL_STREAM_DRAW);

		for (auto& cmd : list->CmdBuffer) {
			const auto textureID = reinterpret_cast<std::uintptr_t>(cmd.GetTexID());
			ccGLBindTexture2D(static_cast<GLuint>(textureID));

			const auto rect = cmd.ClipRect;
			const auto orig = frameToCocos(ImVec2(rect.x, rect.y));
			const auto end = frameToCocos(ImVec2(rect.z, rect.w));

			if (end.x <= orig.x || end.y >= orig.y)
				continue;

			CCDirector::sharedDirector()->getOpenGLView()->setScissorInPoints(orig.x, end.y, end.x - orig.x, orig.y - end.y);

			glDrawElements(GL_TRIANGLES, cmd.ElemCount, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(cmd.IdxOffset * sizeof(ImDrawIdx)));
		}
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(2, &vbos[0]);
	glDeleteVertexArrays(1, &vao);

	glDisable(GL_SCISSOR_TEST);
}