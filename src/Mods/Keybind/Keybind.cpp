#include "Keybind.hpp"
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace CrystalClient;

#define KEY_TO_STR(var) case KEY_##var: ret = #var; break;

std::string Keybinds::keyToString(cocos2d::enumKeyCodes key) {
    std::string ret;
    switch (key) {
        KEY_TO_STR(A);
        KEY_TO_STR(B);
        KEY_TO_STR(C);
        KEY_TO_STR(D);
        KEY_TO_STR(E);
        KEY_TO_STR(F);
        KEY_TO_STR(G);
        KEY_TO_STR(H);
        KEY_TO_STR(I);
        KEY_TO_STR(J);
        KEY_TO_STR(K);
        KEY_TO_STR(L);
        KEY_TO_STR(M);
        KEY_TO_STR(N);
        KEY_TO_STR(O);
        KEY_TO_STR(P);
        KEY_TO_STR(Q);
        KEY_TO_STR(R);
        KEY_TO_STR(S);
        KEY_TO_STR(T);
        KEY_TO_STR(U);
        KEY_TO_STR(V);
        KEY_TO_STR(W);
        KEY_TO_STR(X);
        KEY_TO_STR(Y);
        KEY_TO_STR(Z);

        case KEY_One: ret = "1"; break;
        case KEY_Two: ret = "2"; break;
        case KEY_Three: ret = "3"; break;
        case KEY_Four: ret = "4"; break;
        case KEY_Five: ret = "5"; break;
        case KEY_Six: ret = "6"; break;
        case KEY_Seven: ret = "7"; break;
        case KEY_Eight: ret = "8"; break;
        case KEY_Nine: ret = "9"; break;
        case KEY_Zero: ret = "0"; break;

        default: ret = "UNK"; break;
    }
    return ret;
};

void Keybinds::pushKeybind() {
    keybind.push_back({currentKey, currentMod});
}

bool last_down = false;

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool down) {
        if (Keybinds::waitingForKeybind && down) {
            Keybinds::currentKey = key;
            Keybinds::waitingForKeybind = false;
            return true;
        }

        for (auto [k,v] : Keybinds::keybind) {
            if (key == k && down && v == 1 && PlayLayer::get()) {
                PlayLayer::get()->resetLevel();
            } else if (key == k && v == 4 && GJBaseGameLayer::get()) {
                if (!down && last_down) {
                    GJBaseGameLayer::get()->releaseButton(1, true);
                    last_down = false;
                }
                if (down && !last_down) {
                    GJBaseGameLayer::get()->pushButton(1, true);
                    last_down = true;
                }
            } else if (key == k && down) *setSavedVar<bool>(Keybinds::modvars[v]) = !getSavedVar<bool>(Keybinds::modvars[v]);
        }

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};