/*#include "../Includes.hpp"
#include "Renderer.hpp"
#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <thread>

using namespace geode::prelude;
#ifdef GEODE_IS_MACOS
#include "../subprocess.hpp"

using namespace subprocess::literals;
#endif

FILE * pFile;
Recorder record;

Recorder::Recorder() : m_width(3840), m_height(2160), m_fps(60) {}

std::string getOffsetTime(float time) {
    std::stringstream ret;
    ret << "00:";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time / 60)) << ":";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time) % 60);
    return ret.str();
}

void Recorder::start(const std::string& path, const std::string& temp) {
#ifdef GEODE_IS_MACOS
    m_recording = true;
    m_frame_has_data = false;
    init_quality();
    m_current_frame.resize(getVar<int>("target_width") * getVar<int>("target_height") * 3, 0);
    m_finished_level = false;
    m_last_frame_t = m_extra_t = 0;
    m_after_end_extra_time = 0.f;
    m_renderer.m_width = getVar<int>("target_width");
    m_renderer.m_height = getVar<int>("target_height");
    m_width = getVar<int>("target_width");
    m_height = getVar<int>("target_height");
    m_fps = getVar<int>("target_FPS");
    m_renderer.begin();
    auto gm = GameManager::sharedState();
    auto play_layer = gm->getPlayLayer();
    auto song_file = play_layer->m_level->getAudioFileName();
    auto fade_in = play_layer->m_levelSettings->m_fadeIn;
    auto fade_out = play_layer->m_levelSettings->m_fadeOut;
    auto bg_volume = gm->m_backgroundMusicVolume;
    auto sfx_volume = gm->m_effectsVolume;
    if (play_layer->m_level->m_songID == 0)
        song_file = CCFileUtils::sharedFileUtils()->fullPathForFilename(song_file.c_str(), false);
    auto is_testmode = play_layer->m_isTestMode;
    auto song_offset = std::to_string(PlayLayer::get()->m_levelSettings->m_songOffset);
    //auto tempPATH = Mod::get()->getConfigDir().append("Amethyst").append("Renderer").append("temp.mp4");
    log::info("starting thread");
    std::thread([&, path, song_file, fade_in, fade_out, bg_volume, sfx_volume, is_testmode, song_offset, temp]() {
        //std::string newPATH = std::string(Mod::get()->getResourcesDir()).substr(strpos(Mod::get()->getResourcesDir().c_str(), "/", 3) + 1, std::string(Mod::get()->getResourcesDir()).size() - 1);
        std::stringstream stream;
        stream << '"' << m_ffmpeg_path << '"' << " -y -f rawvideo -pix_fmt rgb24 -s " << m_width << "x" << m_height << " -r " << m_fps
        << " -i - "; 
        if (!m_codec.empty())
            stream << "-c:v " << m_codec << " ";
        if (!m_bitrate.empty())
            stream << "-b:v " << m_bitrate << " ";
        if (!m_extra_args.empty())
            stream << m_extra_args << " ";
        else
            stream << "-pix_fmt yuv420p ";
        stream << "-vf \"vflip\" -an \"" << std::string(temp) << "\" "; // i hope just putting it in "" escapes it
        std::cout << "executing: " << stream.str() << std::endl;
        //pFile = popen(stream.str().c_str(), "w");
        std::string uhhh = stream.str();
        subprocess::command render{uhhh.c_str()};
        render.run();
        while (m_recording || m_frame_has_data) {
            m_lock.lock();
            if (m_frame_has_data) {
                const auto frame = m_current_frame; // copy it
                m_frame_has_data = false;
                m_lock.unlock();
                std::string input((const char*)frame.data(), frame.size());
                render < input;
                //size_t nNumWritten = fwrite(frame.data(), 1, frame.size(), pFile);
            }
            else m_lock.unlock();
        }
        //pclose(pFile);
        log::info("actual video is done");
        wchar_t buffer[128];
        //auto temp_path = narrow(buffer) + "." + std::filesystem::path(path).filename().string();
        //std::filesystem::rename(buffer, temp_path);
        auto total_time = m_last_frame_t;
        {
            std::stringstream stream;
            stream << '"' << m_ffmpeg_path << '"' << " -y -ss " << song_offset << " -i \"" << std::string(song_file)
            << "\" -i \"" << std::string(temp) << "\" -t " << total_time << " -c:v copy ";
            if (!m_extra_audio_args.empty())
                stream << m_extra_audio_args << " ";
            stream << "-filter:a \"volume=1[0:a]";
            if (fade_in && !is_testmode)
                stream << ";[0:a]afade=t=in:d=2[0:a]";
            if (fade_out && m_finished_level)
                stream << ";[0:a]afade=t=out:d=2:st=" << (total_time - m_after_end_duration - 3.5f) << "[0:a]";
            std::cout << "in " << fade_in << " out " << fade_out << std::endl;
            stream << "\" \"" << path << "\"";
            std::cout << "executing: " << stream.str() << std::endl;
            auto song_process = system(stream.str().c_str());
        }
        log::info("video should be done now");
        ghc::filesystem::remove(temp);
        log::info("deleted temp");
    }).detach();
#endif
}

void Recorder::stop() {
    m_renderer.end();
    m_recording = false;
}

void MyRenderTexture::begin() {
    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &m_old_fbo);

    m_texture = new CCTexture2D;
    {
        auto data = malloc(m_width * m_height * 3);
        memset(data, 0, m_width * m_height * 3);
        m_texture->initWithData(data, kCCTexture2DPixelFormat_RGB888, m_width, m_height, CCSize(static_cast<float>(m_width), static_cast<float>(m_height)));
        free(data);
    }

    glGetIntegerv(GL_RENDERBUFFER_BINDING_EXT, &m_old_rbo);

    glGenFramebuffersEXT(1, &m_fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_texture->getName(), 0);

    m_texture->setAliasTexParameters();

    m_texture->autorelease();

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_old_rbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_old_fbo);
}

void MyRenderTexture::capture(std::mutex& lock, std::vector<u8>& data, volatile bool& lul) {
    glViewport(0, 0, m_width, m_height);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &m_old_fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

    auto director = CCDirector::sharedDirector();
    auto scene = director->getRunningScene();
    if (static_cast<CCNode*>(PlayLayer::get())->getChildrenCount()) {
        CCArrayExt<CCNode*> children = PlayLayer::get()->getChildren();
        for (auto* child : children) {
            using namespace std::literals::string_view_literals;
            if ((typeinfo_cast<CCLabelBMFont*>(child) && typeinfo_cast<CCLabelBMFont*>(child)->getString() == "Testmode"sv) || child->getZOrder() == 1000) {
                if (getVar<bool>("include_displays")) child->visit();
            } else {
                child->visit();
            }
        }
    }

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    lock.lock();
    lul = true;
    glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    //CGImageWriteToFile(CGImageFromCCImage(data.data(), 121));
    lock.unlock();

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_old_fbo);
    log::info("captured");
    cocos2d::CCEGLView::sharedOpenGLView()->setViewPortInPoints(0, 0, CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height);
    //director->setViewport();
}

void MyRenderTexture::end() {
    m_texture->release();
}

void Recorder::capture_frame() {
    while (m_frame_has_data) {}
    log::info("frame doesn't have data no more, capturing");
    m_renderer.capture(m_lock, m_current_frame, m_frame_has_data);
}

void Recorder::handle_recording(PlayLayer* play_layer, float dt) {
    if (!play_layer->m_hasLevelCompleteMenu || m_after_end_extra_time < m_after_end_duration) {
        if (play_layer->m_hasLevelCompleteMenu) {
            m_after_end_extra_time += dt;
            m_finished_level = true;
        }
        auto frame_dt = 1. / static_cast<double>(m_fps);
        auto time = play_layer->m_time + m_extra_t - m_last_frame_t;
        if (time >= frame_dt) {
            m_extra_t = time - frame_dt;
            m_last_frame_t = play_layer->m_time;
            play_layer->startMusic();
            capture_frame();
        }
    } else {
        stop();
    }
}

void Recorder::init_quality() {
    if (currentPreset == 0) {
        *setVar<int>("target_width") = 3840;
        *setVar<int>("target_height") = 2160;
        *setVar<int>("target_FPS") = 60;
    } else if (currentPreset == 1) {
        *setVar<int>("target_width") = 1920;
        *setVar<int>("target_height") = 1080;
        *setVar<int>("target_FPS") = 60;
    } else if (currentPreset == 2) {
        *setVar<int>("target_width") = 1280;
        *setVar<int>("target_height") = 720;
        *setVar<int>("target_FPS") = 60;
    } else if (currentPreset == 3) {
        *setVar<int>("target_width") = 640;
        *setVar<int>("target_height") = 480;
        *setVar<int>("target_FPS") = 30;
    }
}

class $modify(PlayLayer) {
    void update(float dt) {
		PlayLayer::update(dt);
		if (getVar<bool>("AT_render")) record.handle_recording(this, dt);
	}

    void onQuit() {
		if (getVar<bool>("AT_render")) record.stop();
		PlayLayer::onQuit();
	}

	bool init(GJGameLevel* gl) {
		if (!PlayLayer::init(gl)) return false;

		if (getVar<bool>("AT_render")) {
			std::string filePATH = Mod::get()->getConfigDir().append("Amethyst").append("Renderer").string() + "/" + getVar<std::string>("video_name") + ".mp4";
			std::string tempPATH = Mod::get()->getConfigDir().append("Amethyst").append("Renderer").string() + "/temp.mp4";
			record.start(filePATH, tempPATH);
		}
		return true;
	}
};*/