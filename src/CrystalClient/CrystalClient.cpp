#include "CrystalClient.hpp"

void CrystalClient::saveConfig() {
    std::ofstream file((Mod::get()->getConfigDir() / "CC_Config.json").string().c_str());
    nlohmann::json JSONobj;

    JSONobj["bools"] = modsMapB;
    JSONobj["ints"] = modsMapI;
    JSONobj["floats"] = modsMapF;
    JSONobj["strings"] = modsMapS;
    JSONobj["keybinds"] = modsMapKEY;

    file << JSONobj;
    file.close();
}

void CrystalClient::loadConfig() {
    std::fstream input((Mod::get()->getConfigDir() / "CC_Config.json").string().c_str());

    if (input.is_open()) {
        auto JSONobj = nlohmann::json::parse(input);
        modsMapB = JSONobj.at("bools").get<std::map<std::string, bool>>();
        modsMapI = JSONobj.at("ints").get<std::map<std::string, int>>();
        modsMapF = JSONobj.at("floats").get<std::map<std::string, float>>();
        modsMapS = JSONobj.at("strings").get<std::map<std::string, std::string>>();
        modsMapKEY = JSONobj.at("keybinds").get<std::map<int, int>>();
    }

    input.close();
}


template <>
bool CrystalClient::getSavedVar<bool>(std::string const& key) {
    return modsMapB[key];
}
template <>
bool* CrystalClient::setSavedVar<bool>(std::string const& key) {
    return &modsMapB[key];
}

template <>
int CrystalClient::getSavedVar<int>(std::string const& key) {
    return modsMapI[key];
}
template <>
int* CrystalClient::setSavedVar<int>(std::string const& key) {
    return &modsMapI[key];
}

template <>
float CrystalClient::getSavedVar<float>(std::string const& key) {
    return modsMapF[key];
}
template <>
float* CrystalClient::setSavedVar<float>(std::string const& key) {
    return &modsMapF[key];
}

template <>
std::string CrystalClient::getSavedVar<std::string>(std::string const& key) {
    return modsMapS[key];
}
template <>
std::string* CrystalClient::setSavedVar<std::string>(std::string const& key) {
    return &modsMapS[key];
}

template <>
bool CrystalClient::getTempVar<bool>(std::string const& key) {
    return TEMPmodsMapB[key];
}
template <>
bool* CrystalClient::setTempVar<bool>(std::string const& key) {
    return &TEMPmodsMapB[key];
}

template <>
int CrystalClient::getTempVar<int>(std::string const& key) {
    return TEMPmodsMapI[key];
}
template <>
int* CrystalClient::setTempVar<int>(std::string const& key) {
    return &TEMPmodsMapI[key];
}

template <>
float CrystalClient::getTempVar<float>(std::string const& key) {
    return TEMPmodsMapF[key];
}
template <>
float* CrystalClient::setTempVar<float>(std::string const& key) {
    return &TEMPmodsMapF[key];
}

ImVec4 CrystalClient::VarToIV4(std::string key) {
    float newr = getSavedVar<float>(key + "-red");
    float newg = getSavedVar<float>(key + "-green");
    float newb = getSavedVar<float>(key + "-blue");
    float newa = getSavedVar<float>(key + "-alpha");
    return ImVec4(newr, newg, newb, newa);
}

ccColor3B CrystalClient::VarToCC3B(std::string key) {
    float newr = getSavedVar<float>(key + "-red") * 255;
    float newg = getSavedVar<float>(key + "-green") * 255;
    float newb = getSavedVar<float>(key + "-blue") * 255;
    return ccc3(newr, newg, newb);
}

ccColor4B CrystalClient::VarToCC4B(std::string key) {
    float newr = getSavedVar<float>(key + "-red") * 255;
    float newg = getSavedVar<float>(key + "-green") * 255;
    float newb = getSavedVar<float>(key + "-blue") * 255;
    float newa = getSavedVar<float>(key + "-alpha") * 255;
    return ccc4(newr, newg, newb, newa);
}