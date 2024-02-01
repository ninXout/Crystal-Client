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
    int r, g, b;
	std::sscanf(getSavedVar<std::string>(key).c_str(), "%02x%02x%02x", &r, &g, &b);
	return ImVec4(r / 255.f, g / 255.f, b / 255.f, 1.f);
}

inline std::string decToHexa(float n) {
    char hexaDeciNum[2];

    int real = std::round(n * 255.f);
 
    int i = 0;
    while (real != 0) {
        int temp = 0;
        temp = real % 16;
 
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        } else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        real = real / 16;
    }
 
    std::string hexCode = "";
    if (i == 2) {
        hexCode.push_back(hexaDeciNum[0]);
        hexCode.push_back(hexaDeciNum[1]);
    } else if (i == 1) {
        hexCode = "0";
        hexCode.push_back(hexaDeciNum[0]);
    } else if (i == 0) {
        hexCode = "00";
    }  
 
    return hexCode;
}

void CrystalClient::IV4toVar(ImVec4 col, std::string key) {
    if ((col.x >= 0 && col.x <= 1.f)
        && (col.y >= 0 && col.y <= 1.f)
        && (col.z >= 0 && col.z <= 1.f)) {
 
        std::string hexCode = "";
        hexCode += decToHexa(col.x);
        hexCode += decToHexa(col.y);
        hexCode += decToHexa(col.z);
 
        *setSavedVar<std::string>(key) = hexCode;
    }
}

ccColor3B CrystalClient::VarToCC3B(std::string key) {
    int r, g, b;
	std::sscanf(getSavedVar<std::string>(key).c_str(), "%02x%02x%02x", &r, &g, &b);
    return ccc3(r, g, b);
}

ccColor4B CrystalClient::VarToCC4B(std::string key) {
    int r, g, b;
	std::sscanf(getSavedVar<std::string>(key).c_str(), "%02x%02x%02x", &r, &g, &b);
    return ccc4(r, g, b, 1.f);
}