#include "CrystalClient.hpp"
/*
void saveConfig() {
    auto JSONobj01 = json2::object();
    JSONobj01 = modsMapB;
    auto JSONobj02 = json2::object();
    JSONobj02 = modsMapI;
    auto JSONobj03 = json2::object();
    JSONobj03 = modsMapF;
    auto JSONobj04 = json2::object();
    JSONobj04 = modsMapS;
    std::ofstream file((Mod::get()->getConfigDir() / "Config" / "GH_config-01.json").string().c_str());
    file << JSONobj01;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-02.json").string().c_str());
    file << JSONobj02;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-03.json").string().c_str());
    file << JSONobj03;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-04.json").string().c_str());
    file << JSONobj04;
    file.close();
}

void loadConfig() {
    std::fstream input((Mod::get()->getConfigDir() / "Config" / "GH_config-01.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj1 = json2::parse(input);
        modsMapB = JSONobj1;
    }
    input.close();
    input.open((Mod::get()->getConfigDir() / "Config" / "GH_config-02.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj2 = json2::parse(input);
        modsMapI = JSONobj2;
    }
    input.close();
    input.open((Mod::get()->getConfigDir() / "Config" / "GH_config-03.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj3 = json2::parse(input);
        modsMapF = JSONobj3;
    }
    input.close();
    input.open((Mod::get()->getConfigDir() / "Config" / "GH_config-04.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj4 = json2::parse(input);
        modsMapS = JSONobj4;
    }
    input.close();
}
*/

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
    float newg = getSavedVar<float>(key + "-blue");
    float newb = getSavedVar<float>(key + "-green");
    float newa = getSavedVar<float>(key + "-alpha");
    return ImVec4(newr, newg, newb, newa);
}