#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		uint32_t score[3][5] = 	     { 50, 40, 30, 20, 10, 50, 40, 30, 20, 10, 50, 40, 30, 20, 10, };
		char initials[3][5][3] =     { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, };
		uint32_t lastScore = 0;
		uint32_t lastScoreIndex = 0;
		uint8_t track = 0;

		SoundEffects sfx = SoundEffects::Both;
		GameInPlay gameInPlay = GameInPlay::Hexon;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;
			this->gameInPlay = GameInPlay::Hexon;
			
			for (uint8_t i = 0; i < 3; i++) {
				this->score[i][0] = 50;
				this->score[i][1] = 40;
				this->score[i][2] = 30;
				this->score[i][3] = 20;
				this->score[i][4] = 10;
			}

			for (uint8_t i = 0; i < 3; i++) {

				for (uint8_t x = 0; x < 5; x++) {

					for (uint8_t y = 0; y < 3; y++) {

						this->initials[i][x][y] = x + 1;

					}

				}

			}

			this->lastScore = 0;
			this->lastScoreIndex = 0;
			this->track = 0;
			this->saveCookie();

		}
		
		uint32_t getScoreIndex() {

			return lastScoreIndex;

		}

		void setScoreIndex(uint32_t val) {

			lastScoreIndex = val;

		}

		uint32_t setLastScore(GameInPlay gameInPlay, uint32_t score) {

            uint32_t index = NO_SCORE;

			for (uint32_t x = 0; x < 5; x++) {

				if (score >= this->score[static_cast<uint8_t>(gameInPlay)][x]) {
				    
				    index = x;
				    break;
				    
				}

			}

			if (index != NO_SCORE) {

			    for (int32_t x = 3; x >= index; x--) {
			        
			        this->score[static_cast<uint8_t>(gameInPlay)][x + 1] = this->score[static_cast<uint8_t>(gameInPlay)][x];
			        this->initials[static_cast<uint8_t>(gameInPlay)][x + 1][0] = this->initials[static_cast<uint8_t>(gameInPlay)][x][0];
			        this->initials[static_cast<uint8_t>(gameInPlay)][x + 1][1] = this->initials[static_cast<uint8_t>(gameInPlay)][x][1];
			        this->initials[static_cast<uint8_t>(gameInPlay)][x + 1][2] = this->initials[static_cast<uint8_t>(gameInPlay)][x][2];
			        
			    }

				this->score[static_cast<uint8_t>(gameInPlay)][index] = score;
				this->initials[static_cast<uint8_t>(gameInPlay)][index][0] = 0;
				this->initials[static_cast<uint8_t>(gameInPlay)][index][1] = 0;
				this->initials[static_cast<uint8_t>(gameInPlay)][index][2] = 0;

			}

			this->lastScore = score;
			this->lastScoreIndex = index;

			return index;

		}

};