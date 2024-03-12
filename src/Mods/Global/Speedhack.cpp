#include <Geode/modify/CCScheduler.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

float leftOver = 0.f;

class $modify(CCScheduler) {
    void update(float dt) {
        using namespace std::literals;

		//float dt2 = (1.f / 60.f);

		dt *= getSavedVar<bool>("speedhack") ? (getSavedVar<float>("speed")) : 1.f;

    	//auto startTime = std::chrono::high_resolution_clock::now();
		//int mult = static_cast<int>((dt + leftOver)/dt2);  
    	//for (int i = 0; i < mult; ++i) {
        	CCScheduler::update(dt);
        	//if (std::chrono::high_resolution_clock::now() - startTime > 33.333ms) {
            	//mult = i + 1;
            	//break;
        	//}
    	//}
        //leftOver += (dt - dt2 * mult); 
    }
};