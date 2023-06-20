#include "Includes.hpp"
#include "CrystalProfile.hpp"
#include "Renderer.hpp"

using namespace Crystal;
using namespace subprocess;

Recorder::Recorder() : m_width(3840), m_height(2160), m_fps(60) {}

std::string getOffsetTime(float time) {
    std::stringstream ret;
    ret << "00:";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time / 60)) << ":";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time) % 60);
    return ret.str();
}

int strpos(const char *haystack, const char *needle, int nth) {
    const char *res = haystack;
    for(int i = 1; i <= nth; i++)
    {
        res = strstr(res, needle);
        if (!res)
            return -1;
        else if(i != nth)
            res++;
    }
    return res - haystack;
}

void Recorder::start(const std::string& path) {
    m_recording = true;
    m_frame_has_data = false;
    m_current_frame.resize(Crystal::profile.targetWidth * Crystal::profile.targetHeight * 3, 0);
    m_finished_level = false;
    m_last_frame_t = m_extra_t = 0;
    m_after_end_extra_time = 0.f;
    m_renderer.m_width = Crystal::profile.targetWidth;
    m_renderer.m_height = Crystal::profile.targetHeight;
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
    auto song_offset = m_song_start_offset;
    log::info("starting thread");
    std::thread([&, path, song_file, fade_in, fade_out, bg_volume, sfx_volume, is_testmode, song_offset]() {
        std::string newPATH = std::string(Mod::get()->getResourcesDir()).substr(strpos(Mod::get()->getResourcesDir().c_str(), "/", 3) + 1, std::string(Mod::get()->getResourcesDir()).size() - 1);
        std::stringstream stream;
        //stream << "cd ~/" + std::string(newPATH) + " && ";
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
        stream << " -ss " << getOffsetTime(song_offset) << " -i " << (std::string)song_file;
        stream << " -vf \"vflip\" -an \"" << path << "\" "; // i hope just putting it in "" escapes it
        log::info("executing: {}", stream.str());
        auto process = Popen(stream.str().c_str(), input{PIPE}, output{PIPE});
        //auto process2 = Popen("pwd", input{PIPE}, output{PIPE});
        while (m_recording || m_frame_has_data) {
            m_lock.lock();
            if (m_frame_has_data) {
                const auto frame = m_current_frame; // copy it
                m_frame_has_data = false;
                m_lock.unlock();
                process.send((const char*)frame.data(), frame.size());
                process.wait();
            }
            else m_lock.unlock();
        }
        log::info("video should be done now");
        auto total_time = m_last_frame_t; // 1 frame too short?
    }).detach();
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
    scene->visit();

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    lock.lock();
    lul = true;
    glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
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
            capture_frame();
        }
    } else {
        stop();
    }
}