#include <Geode/modify/ShaderLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

class $modify(ShaderLayer) {
    void visit() {
        if (getSavedVar<bool>("no_shader")) return CCNode::visit();
        ShaderLayer::visit();
    }
};