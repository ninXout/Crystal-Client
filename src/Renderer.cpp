#include "Includes.hpp"
#include "CrystalProfile.hpp"
#include "Renderer.hpp"

using namespace Crystal;
using namespace subprocess;

FILE * pFile;

Recorder::Recorder() : m_width(3840), m_height(2160), m_fps(60) {}

std::string getOffsetTime(float time) {
    std::stringstream ret;
    ret << "00:";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time / 60)) << ":";
    ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time) % 60);
    return ret.str();
}

void Recorder::start(const std::string& path, const std::string& temp) {
    m_recording = true;
    m_frame_has_data = false;
    init_quality();
    m_current_frame.resize(Crystal::profile.targetWidth * Crystal::profile.targetHeight * 3, 0);
    m_finished_level = false;
    m_last_frame_t = m_extra_t = 0;
    m_after_end_extra_time = 0.f;
    m_renderer.m_width = Crystal::profile.targetWidth;
    m_renderer.m_height = Crystal::profile.targetHeight;
    m_fps = Crystal::profile.targetFPS;
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
        pFile = popen(stream.str().c_str(), "w");
        while (m_recording || m_frame_has_data) {
            m_lock.lock();
            if (m_frame_has_data) {
                const auto frame = m_current_frame; // copy it
                m_frame_has_data = false;
                m_lock.unlock();
                size_t nNumWritten = fwrite(frame.data(), 1, frame.size(), pFile);
            }
            else m_lock.unlock();
        }
        pclose(pFile);
        //if (Crystal::profile.includeAudio) stream << "-ss " << std::to_string(song_offset) << " -i " << std::string(song_file) << " ";
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

CGImageRef MyRenderTexture::CGImageFromCCImage(const void* data, int newDataLen) {
    float width = Crystal::profile.targetWidth;
    float height = Crystal::profile.targetHeight;
    int dataLen = width * height * 4;

    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, data, dataLen, NULL);


    return CGImageCreate(
        width, height, 
        8, 8 * 4, width * 4, 
        CGColorSpaceCreateDeviceRGB(), 
        kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedFirst, 
        provider,   // data provider
        NULL,       // decode
        true,        // should interpolate
        kCGRenderingIntentDefault
    );
}

bool MyRenderTexture::CGImageWriteToFile(CGImageRef image) {
    std::stringstream newthing;
    newthing << (std::string)geode::Mod::get()->getConfigDir();
    newthing << "/Amethyst/Renderer/Frames/";
    newthing << "frame_";
    newthing << std::setw(4) << std::setfill('0') << std::to_string(Crystal::profile.ss);
    newthing << ".png";
    std::string name = newthing.str();

    Crystal::profile.ss++;

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

void Recorder::init_quality() {
    if (currentPreset == 0) {
        profile.targetWidth = 3840;
        profile.targetHeight = 2160;
        profile.targetFPS = 60;
    } else if (currentPreset == 1) {
        profile.targetWidth = 1920;
        profile.targetHeight = 1080;
        profile.targetFPS = 60;
    } else if (currentPreset == 2) {
        profile.targetWidth = 1280;
        profile.targetHeight = 720;
        profile.targetFPS = 60;
    } else if (currentPreset == 3) {
        profile.targetWidth = 640;
        profile.targetHeight = 480;
        profile.targetFPS = 30;
    }
}