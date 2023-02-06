#include "hackpro.hpp"


class $modify(Main, PlayLayer) {
	void updateIndex(bool increment) {
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (m_isTestMode) {
			g_startPosText->setOpacity(255);
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
		}

		if (increment) {
			g_startPosIndex++;
			if (m_isPracticeMode) g_checkpointIndex++;
		} else {
			g_startPosIndex--;
			if (m_isPracticeMode) g_checkpointIndex--;
		}

		if (g_startPosIndex == g_startPoses.size()) {
			g_startPosIndex = -1;
		} else if (g_startPosIndex < -1) {
			g_startPosIndex = g_startPoses.size() - 1;
		}



		auto colorPulseBegin = CCTintTo::create(0.0, 0, 255, 0);
		auto colorPulseEnd = CCTintTo::create(0.5, 255, 255, 255);

		auto opacityPulseBegin = CCFadeTo::create(0.0, 255);
		auto opacityPulseEnd = CCFadeTo::create(0.5, 50);

		if (m_isTestMode) {
			auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
			g_startPosText->setString(label.c_str());
			g_startPosText->runAction(CCSequence::create(colorPulseBegin, colorPulseEnd, nullptr));
			g_startPosText->runAction(CCSequence::create(opacityPulseBegin, opacityPulseEnd, nullptr));
		}

		if (m_isTestMode) {
			m_startPosCheckpoint = nullptr;
			if (g_startPosIndex == -1) {
				m_startPos = nullptr;
				m_playerStartPosition = ccp(0, 105);
			} else {
				m_startPos = g_startPoses[g_startPosIndex].first;
				m_playerStartPosition = g_startPoses[g_startPosIndex].second;
			}
		}

		resetLevel();
		if (m_isPracticeMode) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
			load = true;
		}
		if (m_isTestMode) g_startPosText->setOpacity(50);
		if (m_isPaused)
			GameSoundManager::sharedManager()->stopBackgroundMusic();
	}

	void addObject(GameObject* g) {
		if (playerBools[34]) g->m_isGlowDisabled = true;
		if (playerBools[37]) g->m_isDontFade = true;
		if (playerBools[38]) g->m_isDontEnter = true;
		PlayLayer::addObject(g);
		SPs.push_back(reinterpret_cast<StartPosObject*>(g));
		if (playerBools[41]) {
			switch (g->m_objectID) {
			case 10:
			case 11:
				gravityPortals.push_back(g);
				break;
			case 12:
			case 13:
			case 47:
			case 111:
			case 660:
			case 745:
			case 1331:
				gamemodePortals.push_back(g);
				break;
			case 45:
			case 46:
				mirrorPortals.push_back(g);
				break;
			case 99:
			case 101:
				miniPortals.push_back(g);
				break;
			case 286:
			case 287:
				dualPortals.push_back(g);
				break;
			case 200:
			case 201:
			case 202:
			case 203:
			case 1334:
				speedChanges.push_back(g);
				break;
			}
		}
		if (playerBools[24]) {
			if (g->m_objectID == 31) {
				g->retain();
				g_startPoses.push_back({reinterpret_cast<StartPosObject*>(g), g->getPosition()});
				g_startPosIndex += 1;
				auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
				g_startPosText->setString(label.c_str());
			}
		}
	}	

	void resetLevel() {
		auto gj = reinterpret_cast<PlayerObject*>(PlayLayer::get());
		notDone = true;
		if (playerBools[27] && m_isPracticeMode) load = true;
		if (guiBools[10]) {
			noclip_deaths = deathwait = 0;
		}
		if (playerBools[25]) {
			if (m_isTestMode || m_isPracticeMode) {
				smoothOut = 2;
			}
		}
		if (guiBools[7]) {
			bestEnd2 = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		PlayLayer::resetLevel();
	if (!m_isPracticeMode) {
		frame = 0;
		maxFrame = 0;
	}
	else {

	}
		if (m_checkpoints->count() == 0) {
        	g_activated_objects.clear();
        	g_activated_objects_p2.clear();
        	g_orbCheckpoints.clear();
    	} else {
			if (playerBools[26] && m_isPracticeMode) {
				const auto [p1, p2] = g_orbCheckpoints.back();
        		g_activated_objects.erase(
            		g_activated_objects.begin() + p1,
            		g_activated_objects.end()
        		);
        		g_activated_objects_p2.erase(
            		g_activated_objects_p2.begin() + p2,
            		g_activated_objects_p2.end()
        		);
        		for (const auto& object : g_activated_objects) {
            		object->m_hasBeenActivated = true;
        		}
        		for (const auto& object : g_activated_objects_p2) {
            		object->m_hasBeenActivatedP2 = true;
        		}
			}
    	}
		if (guiBools[4]) {
			bad = "Not Cheating";
			g_cheating->setColor(ccc3(0,255,0));
		}
		if (clickreset) clickscount = 0;
		finished = false;
		if (guiBools[8]) {
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from %.0lf%%", start);
			g_run->setString(str);
		}
		if (guiBools[7]) {
			bestStart2 = (m_player1->getPositionX() / m_levelLength) * 100;
			if ((bestEnd2 - bestStart2) > (bestEnd - bestStart)) {
				bestStart = bestStart2;
				bestEnd = bestEnd2;
			}
			display = "Best Run: " + std::to_string(bestStart) + " to " + std::to_string(bestEnd);
			g_bestRun->setString(display.c_str());
		}
		if (guiBools[9]) {
			frames = noclipped_frames = 0;
		}
	}

	void destroyPlayer(PlayerObject* p, GameObject* g) {
		if (g == m_antiCheatObject) {
			return PlayLayer::destroyPlayer(p,g);
		}
		if (frames>20 && guiBools[9]) {
			noclipped_frames++;
			if ((100*(1.0 - (noclipped_frames/(m_time * 500)))) <= killaccuracy) {
				if (!resetaccuracy) {
					PlayLayer::destroyPlayer(p, g);
				} else {
					resetLevel();
				}
				char str[20];
				sprintf(str, "%.2f%%", killaccuracy);
				reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(str);
			}
		}
		if (frames>20 && guiBools[10]) {
			deathwait++;
			if (deathwait >= 25) {
				noclip_deaths++;
				deathwait = 0;
			} 
		}
		if (bypassBools[0]) {
			bool m_antiCheatPassed = true;
			bool m_shouldTryToKick = false;
			bool m_hasCheated = false;
		}
		if (playerBools[35]) {
			if (g->m_objectID != 8 || g->m_objectID != 39 || g->m_objectID != 103) {
				PlayLayer::destroyPlayer(p,g);
			}
		}
		if (playerBools[0]) {
			if (p == m_player2) PlayLayer::destroyPlayer(p,g);
		}
		if (playerBools[1]) {
			if (p == m_player1) PlayLayer::destroyPlayer(p,g);
		} 
		if (!playerBools[0] && !playerBools[1]) {
			PlayLayer::destroyPlayer(p,g);
		}
	}

	void fullReset() {
		if (playerBools[30] && m_isPracticeMode) {
			loadLastCheckpoint();
			resetLevel();
		} else {
			PlayLayer::fullReset();
		}
	}

//GJBaseGameLayer::get()->m_player1->

	void checkCollisions(PlayerObject* p, float g) {
			frames++;

		if (bypassBools[0]) {
			m_antiCheatPassed = true;
			m_shouldTryToKick = false;
			m_hasCheated = false;
		}

		if (bypassBools[9]) GJBaseGameLayer::get()->m_player1->setPositionY(1050);
		if (bypassBools[9]) GJBaseGameLayer::get()->m_player1->setPositionX(m_levelLength - 200);

			auto p1 = GJBaseGameLayer::get()->m_player1;
			auto p2 = GJBaseGameLayer::get()->m_player2;

			if (p1->getPositionX() == 0) { 
				frame = 0;
			}
			else { 
				frame++;
			}

		if (frame > maxFrame) { maxFrame = frame; }

		if (replay) {
			if (std::get<std::deque<float>>(Player1Data["Xpos"]).back() < p1->getPositionX()) {
				frame -= 4;
				//p->setPositionX(std::get<std::deque<float>>(Player1Data["Xpos"]).back());
			}
			if (frame != 0) {
					if (frameAccuracy) {
						p1->setPositionX(xpos[frame - 1]);
						p1->setPositionY(ypos[frame - 1]);
						p1->setRotation(rot[frame - 1]);
					}
					if (push[frame] && !mouse1Down) { 
						GJBaseGameLayer::get()->pushButton(1, true); 
						if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3.ogg", 1, 1, 1);
						mouse1Down = true;
					}
					if (!push[frame] && mouse1Down) { 
						GJBaseGameLayer::get()->releaseButton(1, true); 
						//if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3rel.ogg", 1, 1, 1);
						mouse1Down = false; 
					}
					/*
					p2->setPositionX(std::get<std::deque<float>>(Player2Data["Xpos"])[(frame - 1)]);
					p2->setPositionY(std::get<std::deque<float>>(Player2Data["Ypos"])[(frame - 1)]);
					p2->setRotation(std::get<std::deque<float>>(Player2Data["Rotation"])[(frame - 1)]);
					if (std::get<std::deque<bool>>(Player2Data["Pushed"])[(frame)] && !mouse2Down) { 
						GJBaseGameLayer::get()->pushButton(1, false); 
						//if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3.ogg", 1, 1, 1);
						mouse2Down = true;
					}
					if (!std::get<std::deque<bool>>(Player2Data["Pushed"])[(frame)] && mouse2Down) { 
						GJBaseGameLayer::get()->releaseButton(1, false); 
						//if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3rel.ogg", 1, 1, 1);
						mouse2Down = false; 
					}
					*/
			}
		}
		//double yAcc = (*reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(this) + 0x760));
		if (record) {
			if (frame > 0) {
					macroSpeed = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
					xpos.insert(xpos.end(), p1->getPositionX());
					ypos.insert(ypos.end(), p1->getPositionY());
					rot.insert(rot.end(), p1->getRotation());
					push.insert(push.end(), mouse1Down);
					//std::get<std::deque<double>>(Player1Data["Yvelo"]).insert(std::get<std::deque<double>>(Player1Data["Yvelo"]).end(), yAcc);
					//std::get<std::deque<float>>(Player2Data["Xpos"]).insert(std::get<std::deque<float>>(Player2Data["Xpos"]).end(), p2->getPositionX());
					//std::get<std::deque<float>>(Player2Data["Ypos"]).insert(std::get<std::deque<float>>(Player2Data["Ypos"]).end(), p2->getPositionY());
					//std::get<std::deque<float>>(Player2Data["Rotation"]).insert(std::get<std::deque<float>>(Player2Data["Rotation"]).end(), p2->getRotation());
					//std::get<std::deque<bool>>(Player2Data["Pushed"]).insert(std::get<std::deque<bool>>(Player2Data["Pushed"]).end(), mouse2Down);
			}
		}

			if (playerBools[40]) {
				clickframe++;
				if (clickframe == clickPush) {
					GJBaseGameLayer::get()->pushButton(1, true);
				}
				if (clickframe >= (clickPush + clickRel)) {
					GJBaseGameLayer::get()->releaseButton(1, true);
					clickframe = 0;
				}
			}

			PlayLayer::checkCollisions(p, g);

			if (guiBools[9] && !finished) {
				char ok[20];
				sprintf(ok, "%.2f%%", 100*(1.0 - (noclipped_frames/(m_time * 500))));
				reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(ok);
			}
	}

	void levelComplete() {
		finished = true;
		PlayLayer::levelComplete();
	}

	void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		int resetPercentage = (m_player1->getPositionX() / m_levelLength) * 100;
		if ((resetPercentage == autoresetnum) && playerBools[31]) {
			resetLevel();
		}
		if (playerBools[13]) {
			double percent = (m_player1->getPositionX() / m_levelLength) * 100;
			if (percent > 100.00) {
				percent = 100.00;
			}
			char str[64];
			sprintf(str, "%.2lf%%", percent);
			this->m_percentLabel->setString(str);
		}
	}

	void update(float f4) {
		if (g >= 360) // mod 360
			g = 0;
		else
			g += rainbowspeed; // a good rotation
		col = getRainbow(0);
		colInverse = getRainbow(180);

		if (m_player1) {
			if (playerBools[2]) m_player1->setColor(col);
			if (playerBools[3]) m_player1->setSecondColor(colInverse);
			if (playerBools[33]) m_player1->m_waveTrail->setVisible(false);
			//if (m_player1->m_waveTrail)
				//if (rainP1wave) m_player1->m_waveTrail->setColor(col);
		}

		if (m_player2) {
			if (playerBools[3]) m_player2->setColor(colInverse);
			if (playerBools[2]) m_player2->setSecondColor(col);
			//if (m_player2->m_waveTrail)
				//if (rainP2wave) m_player2->m_waveTrail->setColor(colInverse);
		}


		if (guiBools[9]) {
			percent = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		if (guiBools[0]) {
			g_message->setString(message);
		}
		if (guiBools[4]) {
			if (playerBools[0] || speedhack<1 || nospike || playerBools[36] || playerBools[29] || playerBools[40] || playerBools[39] || bypassBools[9] || moon) {
				bad = "Cheating";
				g_cheating->setColor(ccc3(155,0,0));
			}

			g_cheating->setString(bad.c_str());

		}
		if (pausecountdown) {
			if (freezeCount) {
				GameSoundManager::sharedManager()->stopBackgroundMusic();
				countdown++;
				if (countdown <= 60) {
					g_pauseCount->setString("3");
				} else if (countdown <= 120 && countdown > 60) {
					g_pauseCount->setString("2");
				} else if (countdown <= 180 && countdown > 120) {
					g_pauseCount->setString("1");
				} else if (countdown <= 240 && countdown > 180) {
					freezeCount = false;
					startMusic();
					g_pauseCount->setOpacity(0);
					countdown = 0;
				}
			}
		}
		if (guiBools[10]) {
			std::string nd = "Noclip Deaths: " + std::to_string(noclip_deaths);
			font->setString(nd.c_str());
		}
		if (guiBools[3]) {
			std::string nd = "Total Jumps: " + std::to_string(m_level->m_jumps);
			g_jumps->setString(nd.c_str());
		}
		if (playerBools[5]) {
			m_player2->setSecondColor(secondary);
			m_player2->setColor(primary);
			m_player2->m_waveTrail->setColor(primary);
		}
		if (guiBools[2]) {
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
		}
		m_percentLabel->setPositionX(percentXpos);
		m_percentLabel->setPositionY(percentYpos);
		m_percentLabel->setScale(percentScale);
		m_percentLabel->setOpacity(percentOpac);
		if (playerBools[12]) {
			m_sliderGrooveSprite->setVisible(false);
		} else {
			m_sliderGrooveSprite->setVisible(true);
			m_percentLabel->setPositionX(m_percentLabel->getPositionX());
		}
		if (playerBools[15]) {
			m_attemptLabel->setVisible(false);
		}
		if (playerBools[16]) {
			if (m_isPracticeMode) m_attemptLabel->setVisible(false);
		}
		if (guiBools[6]) {
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);
		}
		if (guiBools[11]) {
			std::string at = "Global Atts: " + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
		}
		if (guiBools[5]) {
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death: %.0lf%%", start);
			g_death->setString(str);
		}
		if (playerBools[25]) {
			if (!smoothOut) {
				return update(f4);
			}

			float time = cocos2d::CCDirector::sharedDirector()->getAnimationInterval();
			if (smoothOut != 0 && f4 - time < 1) {
				smoothOut --;
			}

			PlayLayer::update(time);
		} else {
			if (playerBools[29]) {
				if (stepready) {
					PlayLayer::update(f4);
				}
			} else {
				if (classicspeed) {
					PlayLayer::update(f4 * speedhack);
				} else {
					if (!freezeCount) PlayLayer::update(f4);
				}
			}
		}
	}

	void markCheckpoint() {
		if (playerBools[26]) g_orbCheckpoints.push_back({g_activated_objects.size(), g_activated_objects_p2.size()});
		PlayLayer::markCheckpoint();
		std::get<std::deque<int>>(Player1Data["Checkpoints"]).insert(std::get<std::deque<int>>(Player1Data["Checkpoints"]).end(), frame);
	}

	void removeLastCheckpoint() {
		if (playerBools[26]) g_orbCheckpoints.pop_back();
		PlayLayer::removeLastCheckpoint();
		if (std::get<std::deque<int>>(Player1Data["Checkpoints"]).size() > 0) std::get<std::deque<int>>(Player1Data["Checkpoints"]).pop_back();
	}

	void startMusic() {
		if (playerBools[17]) {
			auto p = m_isPracticeMode;
			m_isPracticeMode = false; // pretend there is no practice mode
			PlayLayer::startMusic();
			m_isPracticeMode = p;
		} else {
			PlayLayer::startMusic();
		}
	}

	void onQuit() {
		FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		if (!shouldQuit && playerBools[19] && !m_hasLevelCompleteMenu && !CCDirector::sharedDirector()->getKeyboardDispatcher()->getShiftKeyPressed()) {
			geode::createQuickPopup(
    "Confirm Quit",            // title
    "Are you sure you would like to Quit?",   // content
    "Cancel", "Quit",      // buttons
    [](auto, bool btn2) {
        if (btn2) {
            shouldQuit = true;
        }
    }
);
		} else {
			PlayLayer::onQuit();
		}
	}

	void togglePracticeMode(bool p) {
		if (playerBools[17]) {
			if (!m_isPracticeMode && p) {
				// receate function without the music restart
				m_isPracticeMode = p;
				m_UILayer->toggleCheckpointsMenu(p);
				PlayLayer::startMusic();
				this->stopActionByTag(18);
				//if (p) stopActionByTag(0x12);
			} else {
				PlayLayer::togglePracticeMode(p);
			}
		}
		else {
			PlayLayer::togglePracticeMode(p);
		}
	}

	void resume() {
		PlayLayer::resume();
		if (pausecountdown) freezeCount = true;
		if (pausecountdown) g_pauseCount->setOpacity(255);
	}

	void toggleFlipped(bool one, bool two) {
		if (!playerBools[36]) {
			PlayLayer::toggleFlipped(one, two);
		}
	}

	void setAnchoredPosition(CCNode* label, int anchorPos) {
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (anchorPos == 1) {
			label->setPosition(5, corner - 10);
		} else if (anchorPos == 2) {
			label->setPosition(5, corner - 25);
		} else if (anchorPos == 3) {
			label->setPosition(5, corner - 40);
		} else if (anchorPos == 4) {
			label->setPosition(5, corner - 55);
		} else if (anchorPos == 5) {
			label->setPosition(5, corner - 70);
		} else if (anchorPos == 6) {
			label->setPosition(5, corner - 85);
		} else if (anchorPos == 7) {
			label->setPosition(5, corner - 100);
		} else if (anchorPos == 8) {
			label->setPosition(5, corner - 115);
		} else if (anchorPos == 9) {
			label->setPosition(5, corner - 130);
		} else if (anchorPos == 10) {
			label->setPosition(5, corner - 145);
		} else if (anchorPos == 11) {
			label->setPosition(5, corner - 160);
		} else if (anchorPos == 12) {
			label->setPosition(5, corner - 175);
		} else if (anchorPos == 13) {
			label->setPosition(5, corner - 190);
		} else if (anchorPos == 14) {
			label->setPosition(5, corner - 205);
		}
	}

	void startGame() {
		PlayLayer::startGame();
		if (guiBools[1]) {
			FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
            reinterpret_cast<cocos2d::CCNode*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0))
                ->addChild(FPSOverlay::sharedState(), 100001);
		}
	}

	void setupSmartSP() {
		if (playerBools[41]) {
			//willFlip.resize(gravityPortals.size());
			for (StartPosObject* startPos : SPs) {
			geode::log::info("started");
		for (int i = 0; i < gravityPortals.size(); i++)
		{
			if (gravityPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (gravityPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				willFlip.push_back(gravityPortals[i]->m_objectID == 11);
		}
		geode::log::info("gravity");
		startPos->m_levelSettings->m_startDual = GJBaseGameLayer::get()->m_levelSettings->m_startDual;
		for (int i = 0; i < dualPortals.size(); i++)
		{
			if (dualPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			//if (dualPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				//startPos->m_levelSettings->m_startDual = (dualPortals[i]->m_objectID == 286);
		}
		geode::log::info("dual");
		startPos->m_levelSettings->m_startMode = GJBaseGameLayer::get()->m_levelSettings->m_startMode;
		for (size_t i = 0; i < gamemodePortals.size(); i++)
		{
			if (gamemodePortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (gamemodePortals[i]->getPositionX() - 10 < startPos->getPositionX())
			{
				switch (gamemodePortals[i]->m_objectID)
				{
				case 12:
					//startPos->m_levelSettings->m_startMode = 0;
					break;
				case 13:
					//startPos->m_levelSettings->m_startMode = 1;
					break;
				case 47:
					//startPos->m_levelSettings->m_startMode = 2;
					break;
				case 111:
					//startPos->m_levelSettings->m_startMode = 3;
					break;
				case 660:
					//startPos->m_levelSettings->m_startMode = 4;
					break;
				case 745:
					//startPos->m_levelSettings->m_startMode = 5;
					break;
				case 1331:
					//startPos->m_levelSettings->m_startMode = 6;
					break;
				}
			}
		}
		geode::log::info("gamemode");
		startPos->m_levelSettings->m_startMini = GJBaseGameLayer::get()->m_levelSettings->m_startMini;
		for (size_t i = 0; i < miniPortals.size(); i++)
		{
			if (miniPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			//if (miniPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				//startPos->m_levelSettings->m_startMini = miniPortals[i]->m_objectID == 101;
		}
		geode::log::info("mini");

		startPos->m_levelSettings->m_startSpeed = GJBaseGameLayer::get()->m_levelSettings->m_startSpeed;
		for (size_t i = 0; i < speedChanges.size(); i++)
		{
			if (speedChanges[i]->getPositionX() - 50 > startPos->getPositionX())
				break;
			if (speedChanges[i]->getPositionX() - 50 < startPos->getPositionX())
			{
				switch (speedChanges[i]->m_objectID)
				{
				case 200:
					//startPos->m_levelSettings->m_startSpeed = 0;
					break;
				case 201:
					//startPos->m_levelSettings->m_startSpeed = 1;
					break;
				case 202:
					//startPos->m_levelSettings->m_startSpeed = 2;
					break;
				case 203:
					//startPos->m_levelSettings->m_startSpeed = 3;
					break;
				case 1334:
					//startPos->m_levelSettings->m_startSpeed = 4;
					break;
				}
			}
		}
		geode::log::info("done");
	}
		}
	}

	bool init(GJGameLevel* gl) {
		leftDisplay = 0;
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (playerBools[24]) {
			rightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			leftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_startPosText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_startPosIndex = -1;
			g_startPoses = {};
			
		}
		if (playerBools[27]) {
			CPrightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			CPleftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_checkpointText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_checkpointIndex = -1;
			g_checkpointsIG = {};
			
		}
		if (guiBools[0]) {
			g_message = CCLabelBMFont::create(message, "bigFont.fnt");
		}
		if (guiBools[3]) {
			g_jumps = CCLabelBMFont::create("Total Jumps: 0", "bigFont.fnt");
		}
		if (guiBools[6]) {
			g_atts = CCLabelBMFont::create("Attempts: 0", "bigFont.fnt");
		}
		if (guiBools[8]) {
			g_run = CCLabelBMFont::create("Run from ???", "bigFont.fnt");
		}
		if (guiBools[7]) {
			g_bestRun = CCLabelBMFont::create("Best Run: 0 to 0", "bigFont.fnt");
		}
		if (guiBools[12]) {
			g_levelInfo = CCLabelBMFont::create("Unnamed (No ID)", "bigFont.fnt");
		}
		if (guiBools[2]) {
			g_clicks = CCLabelBMFont::create("?? Clicks", "bigFont.fnt");
			clickscount = 0;
		}
		if (guiBools[4]) {
			g_cheating = CCLabelBMFont::create("Not Cheating", "bigFont.fnt");
		}
		if (guiBools[11]) {
			g_tatts = CCLabelBMFont::create("Global Atts: ??", "bigFont.fnt");
		}
		if (guiBools[5]) {
			g_death = CCLabelBMFont::create("Last Death: ???", "bigFont.fnt");
		}
		if (guiBools[10]) {
			font = CCLabelBMFont::create("Noclip Deaths: ???", "bigFont.fnt");
		}
		if (guiBools[9]) {
			text = CCLabelBMFont::create("100%", "bigFont.fnt");
		}
		if (macroStatus) {
			g_macro = CCLabelBMFont::create("Playing: 0/0", "bigFont.fnt");
		}
		if (pausecountdown) {
			g_pauseCount = CCLabelBMFont::create("Not Paused", "goldFont.fnt");
		}

			PlayLayer::init(gl);

		setupSmartSP();
		frame = 0;
		maxFrame = 0;
		if (variable_index == 0 && applyVC) {
			//gl->m_levelName = stringVC;
		} else if (variable_index == 1 && applyVC) {
			gl->m_levelDesc = stringVC;
		} else if (variable_index == 2 && applyVC) {
			gl->m_creatorName = stringVC;
		} else if (variable_index == 3 && applyVC) {
			gl->m_attempts = std::stoi(stringVC);
		} else if (variable_index == 4 && applyVC) {
			gl->m_jumps = std::stoi(stringVC);
		}
		if (customColor) {
			m_player1->setColor(ccc3(customR1, customG1, customB1));
			m_player1->setSecondColor(ccc3(customR2, customG2, customB2));
		}
		if (bypassBools[9]) {
			//gl->savePercentage(100, false, 100, 100, true);
		}
		
		if (playerBools[24]) {
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
			g_startPosText->setScale(0.5);
			g_startPosText->setAnchorPoint({0, 0.5});
			g_startPosText->setOpacity(50);
			rightButton->::Main::setPosition(220 , corner - 275);
			rightButton->setScale(0.5);
			rightButton->setAnchorPoint({0, 0.5});
			rightButton->setOpacity(50);
			leftButton->::Main::setPosition(310 , corner - 275);
			leftButton->setRotation(180);
			leftButton->setScale(0.5);
			leftButton->setAnchorPoint({0, 0.5});
			leftButton->setOpacity(50);

			if (!m_isTestMode) {
				g_startPosText->setVisible(false);
				rightButton->setVisible(false);
				leftButton->setVisible(false);
			}
			addChild(g_startPosText, 1000);
			addChild(rightButton, 1000);
			addChild(leftButton, 1000);
		}
		if (playerBools[27]) {
			g_checkpointText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				//g_checkpointText->setPosition(245 , corner - 275);
			}
			g_checkpointText->setScale(0.5);
			g_checkpointText->setAnchorPoint({0, 0.5});
			g_checkpointText->setOpacity(50);
			CPrightButton->::Main::setPosition(220 , corner - 275);
			CPrightButton->setScale(0.5);
			CPrightButton->setAnchorPoint({0, 0.5});
			CPrightButton->setOpacity(50);
			CPleftButton->::Main::setPosition(310 , corner - 275);
			CPleftButton->setRotation(180);
			CPleftButton->setScale(0.5);
			CPleftButton->setAnchorPoint({0, 0.5});
			CPleftButton->setOpacity(50);

			if (!m_isPracticeMode) {/*
				g_checkpointText->setVisible(false);
				CPrightButton->setVisible(false);
				CPleftButton->setVisible(false);
				*/
			}
			addChild(g_checkpointText, 1000);
			addChild(CPrightButton, 1000);
			addChild(CPleftButton, 1000);
		}
		if (playerBools[12]) {
			m_percentLabel->setPositionX(259.638);
		}
			percentXpos = m_percentLabel->getPositionX();
			percentYpos = m_percentLabel->getPositionY();
			percentScale = m_percentLabel->getScale();
			percentOpac = m_percentLabel->getOpacity();
		if (m_isTestMode) leftDisplay = 1;
		if (guiBools[0]) {
			leftDisplay++;
			setAnchoredPosition(g_message, leftDisplay);
			//g_tatts->setPosition(5 , corner - 55);
			g_message->setScale(0.4);
			g_message->setAnchorPoint({0, 0.5});
			g_message->setOpacity(100);
			addChild(g_message, 1001);
		}
		if (guiBools[4]) {
			leftDisplay++;
			setAnchoredPosition(g_cheating, leftDisplay);
			//g_cheating->setPosition(5 , corner - 10);
			g_cheating->setScale(0.4);
			g_cheating->setAnchorPoint({0, 0.5});
			g_cheating->setOpacity(100);
			addChild(g_cheating, 1001);
		}
		if (guiBools[8]) {
			leftDisplay++;
			setAnchoredPosition(g_run, leftDisplay);
			//g_run->setPosition(5 , corner - 70);
			g_run->setScale(0.4);
			g_run->setAnchorPoint({0, 0.5});
			g_run->setOpacity(100);
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from: %.0lf%%", start);
			g_run->setString(str);

			addChild(g_run, 1000);
		}
		if (guiBools[3]) {
			leftDisplay++;
			setAnchoredPosition(g_jumps, leftDisplay);
			//g_tatts->setPosition(5 , corner - 55);
			g_jumps->setScale(0.4);
			g_jumps->setAnchorPoint({0, 0.5});
			g_jumps->setOpacity(100);
			std::string po = "Total Jumps:" + std::to_string(gl->m_jumps);
			g_jumps->setString(po.c_str());
			addChild(g_jumps, 1001);
		}
		if (guiBools[11]) {
			leftDisplay++;
			setAnchoredPosition(g_tatts, leftDisplay);
			//g_tatts->setPosition(5 , corner - 55);
			g_tatts->setScale(0.4);
			g_tatts->setAnchorPoint({0, 0.5});
			g_tatts->setOpacity(100);
			std::string at = "Global Atts:" + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
			addChild(g_tatts, 1001);
		}
		if (guiBools[5]) {
			leftDisplay++;
			setAnchoredPosition(g_death, leftDisplay);
			//g_death->setPosition(5 , corner - 130);
			g_death->setScale(0.4);
			g_death->setAnchorPoint({0, 0.5});
			g_death->setOpacity(100);
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death:%.0lf%%", start);
			g_death->setString(str);

			addChild(g_death, 1000);
		}
		if (guiBools[10]) {
			leftDisplay++;
			setAnchoredPosition(font, leftDisplay);
			//g_tatts->setPosition(5 , corner - 160);
			font->setScale(0.4);
			font->setAnchorPoint({0, 0.5});
			font->setOpacity(100);
			addChild(font, 1001);
		}
		if (guiBools[6]) {
			leftDisplay++;
			setAnchoredPosition(g_atts, leftDisplay);
			//g_atts->setPosition(5 , corner - 40);
			g_atts->setScale(0.4);
			g_atts->setAnchorPoint({0, 0.5});
			g_atts->setOpacity(100);
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);

			addChild(g_atts, 1000);
		}
		if (guiBools[7]) {
			leftDisplay++;
			setAnchoredPosition(g_bestRun, leftDisplay);
			//g_bestRun->setPosition(5 , corner - 85);
			g_bestRun->setScale(0.4);
			g_bestRun->setAnchorPoint({0, 0.5});
			g_bestRun->setOpacity(100);
			bestEnd = 0;
			bestStart = 0;
			bestEnd2 = 0;
			bestStart2 = 0;
			bestStart = (m_player1->getPositionX() / m_levelLength) * 100;
			addChild(g_bestRun, 1001);
		}
		if (guiBools[12]) {
			leftDisplay++;
			setAnchoredPosition(g_levelInfo, leftDisplay);
			std::string display;
			g_levelInfo->setScale(0.4);
			g_levelInfo->setAnchorPoint({0, 0.5});
			g_levelInfo->setOpacity(100);
			std::string levelName = gl->m_levelName;
			std::string levelAuthor = gl->m_creatorName;
			std::string levelID = std::to_string(gl->m_levelID);
			if (hideID) {
				levelID = "--------";
			} else if (levelID<"22" && levelID>"0" || levelID == "3" || levelID == "4" || levelID == "5" || levelID == "6" || levelID == "7" || levelID == "8" || levelID == "9") {
				levelAuthor = "RobTop"; // this wasnt working from Polargeist (3) to Cycles (9) so i had to do that lmao
			} else if (levelID == "0") {
				levelID = "Copy";
			}
			if (author) {
				display = levelName + " by " + levelAuthor + " (" + levelID + ")";
			} else {
				display = levelName + " (" + levelID + ")";
			}
			g_levelInfo->setString(display.c_str());
			addChild(g_levelInfo, 1001);
		}
		if (guiBools[2]) {
			leftDisplay++;
			setAnchoredPosition(g_clicks, leftDisplay);
			//g_clicks->setPosition(5 , corner - 115);
			g_clicks->setScale(0.4);
			g_clicks->setAnchorPoint({0, 0.5});
			g_clicks->setOpacity(100);
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
			addChild(g_clicks, 1001);
		}
		if (guiBools[9]) {
			leftDisplay++;
			setAnchoredPosition(text, leftDisplay);
			//text->setPosition(5 , corner - 145);
			text->setAnchorPoint({0, 0.5});
			text->setTag(31403);
			text->setScale(0.4);
			text->setOpacity(100);
			addChild(text, 1000);
			frames = noclipped_frames = 0;
		}
		if (pausecountdown) {
			g_pauseCount->setPosition({ CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height - 175 });
			g_pauseCount->setAnchorPoint({0, 0.5});
			g_pauseCount->setOpacity(0);
			addChild(g_pauseCount, 1000);
		}
		secondary = m_player2->getColor();
		primary = m_player1->getColor();
		return true;
	}
};