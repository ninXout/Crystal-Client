#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "../../Utilities/utilities.hpp"

using namespace CrystalClient;

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}


class $modify(PlayLayer) {
    /*float getModifiedDelta(float sp) { // sp is timewarp i think???
        // recreating getModifiedDelta except i wanna add physics bypass
        double dVar1;
        double dVar2;
        float fVar3;
        double dVar4;

        if (0 < from<int>(this, 0x30fc)) {
            from<int*>(this, 0x30fc)--;
            sp = 0.f;
        }

        if (from<float>(this, 0x330) < 1.0) {
            dVar2 = static_cast<double>(from<float>(this, 0x330)) * static_cast<double>(1.f / getSavedVar<float>("physics"));
        } else {
            dVar2 = static_cast<double>(1.f / getSavedVar<float>("physics"));
        }

        dVar1 = (double)sp + from<double>(this, 0x30a8);
        dVar4 = dVar1 / dVar2;
        fVar3 = (float)dVar4;

        from<double>(this, 0x30a8) = dVar1 - dVar2;

        return static_cast<float>(dVar2);
    }*/

    bool init(GJGameLevel* gj, bool b, bool b2) {
        if (!PlayLayer::init(gj,b,b2)) return false;

        /*float timestamping = gj->m_timestamp;

        Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x7e9ac0), toBytes((1.f / getSavedVar<float>("physics"))));

        if (PlayLayer::get() && PlayLayer::get()->m_level->m_timestamp > 0) {
            float timestampMultiplier = (getSavedVar<float>("physics") / 240.f);
            float stepsMultiplier = (timestamping * timestampMultiplier) / PlayLayer::get()->m_level->m_timestamp;
            PlayLayer::get()->m_level->m_timestamp = timestamping * timestampMultiplier;
        }*/

        return true;
    }
};