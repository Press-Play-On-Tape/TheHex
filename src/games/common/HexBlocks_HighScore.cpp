#include "../../HexBlocks.h"
#include "../../images/Images.h"
#include "../../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::highScore_Init() {
	
    this->gamePlayVariables.cursor = 0;
    this->gameState = GameState::HighScore;
    uint32_t index = cookie->getScoreIndex();

    for (uint8_t x = 0; x < 16; x++) {

        uint8_t rnd = random(0, 13);

        for (uint8_t y = 0; y < 16; y++) {

            if (y >= rnd && y <= rnd + 2) {
                this->highScoreVariables.scoreGameBoard[x][y] = random(1, 9);
            }
            else {
                this->highScoreVariables.scoreGameBoard[x][y] = 0;
            }
            
        }

    }

    this->fadeIn();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::highScore() {
	
    bool flash = Utils::getFrameCountHalf(48);
    uint32_t index = cookie->getScoreIndex();

    const uint8_t frameCount[16] = {4, 5, 7, 4, 6,   5, 7, 6, 5, 6,   4, 5, 6, 4, 5,   6,  };


    // Render background ..

    for (uint8_t x = 0; x < 16; x++) {

        uint8_t bt = this->highScoreVariables.scoreGameBoard[x][15];
        uint8_t temp = this->highScoreVariables.scoreGameBoard[x][15];

        if (Utils::isFrameCount(frameCount[x])) {

            for (uint8_t y = 15; y > 0; y--) {

                switch (this->highScoreVariables.scoreGameBoard[x][y - 1]) {

                    case 0:
                        this->highScoreVariables.scoreGameBoard[x][y] = 0;
                        break;

                    case 1 ... 4:
                        this->highScoreVariables.scoreGameBoard[x][y] = this->highScoreVariables.scoreGameBoard[x][y - 1] + 1;
                        if (this->highScoreVariables.scoreGameBoard[x][y] > 4) this->highScoreVariables.scoreGameBoard[x][y] = 1;
                        break;

                    case 5 ... 8:
                        this->highScoreVariables.scoreGameBoard[x][y] = this->highScoreVariables.scoreGameBoard[x][y - 1] + 1;
                        if (this->highScoreVariables.scoreGameBoard[x][y] > 8) this->highScoreVariables.scoreGameBoard[x][y] = 5;
                        break;

                }
                
            }

            if (bt != 0) {
                this->highScoreVariables.scoreGameBoard[x][0] = random(1, 9);
            }
            else {
                this->highScoreVariables.scoreGameBoard[x][0] = temp;
            }

        }

    }



	// Handle other input ..

    if (index != NO_SCORE) {

        if (PC::buttons.pressed(BTN_LEFT) && this->gamePlayVariables.cursor > 0) {
            this->gamePlayVariables.cursor--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->gamePlayVariables.cursor < 2) {
            this->gamePlayVariables.cursor++;
        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 16)) {

            uint32_t val = cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][this->gamePlayVariables.cursor];
            val++;
            if (val > 26) val = 1;
            cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][this->gamePlayVariables.cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 16)) {

            uint32_t val = cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][this->gamePlayVariables.cursor];
            if (val == 0) val = 26;
            val--;
            cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][this->gamePlayVariables.cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_A)) {

            if (cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][0] != 0 && this->cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][1] != 0 && cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][2] != 0) {

                cookie->saveCookie();
                cookie->setLastScore(this->cookie->gameInPlay, 0);

            }
            else if (this->gamePlayVariables.cursor < 2 && cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][this->gamePlayVariables.cursor] != 0 ) {
                this->gamePlayVariables.cursor++;
            }
            
        }

    }
    else {

        if (PC::buttons.pressed(BTN_LEFT)) {

            if (this->cookie->gameInPlay != GameInPlay::Hexon) {
                this->cookie->gameInPlay--;
                this->cookie->saveCookie();
            }

        }

        if (PC::buttons.pressed(BTN_RIGHT)) {
            
            if (this->cookie->gameInPlay != GameInPlay::Hexic) {
                this->cookie->gameInPlay++;
                this->cookie->saveCookie();
            }

        }

        if (PC::buttons.pressed(BTN_A)) {

            this->nextGameState = GameState::Title_Init;
            this->fadeOut();
        }

   
    }


    // ----------------------------------------------------------------------------
    //  Render the state .. 

    for (uint8_t x = 0; x < 16; x++) {

        for (uint8_t y = 0; y < 16; y++) {

            uint8_t bt = this->highScoreVariables.scoreGameBoard[x][y];

            if (bt != 0) {

                PD::drawBitmap((x * (PART_SIZE + 3)), y * PART_SIZE, Images::Hex_HighScore[bt + 1]);

            }
            
        }

    }

    PD::drawBitmap(48, 18, Images::HighScore);
    PD::setColor(5, 0);
    PD::drawLine(50, 85, 79, 85);
    PD::drawLine(139, 85, 168, 85);
    PD::setColor(6, 0);

    switch (this->cookie->gameInPlay) {

        case GameInPlay::Hexon:
            PD::drawBitmap(86, 73, Images::Hexon);
            break;

        case GameInPlay::Hexer:
            PD::drawBitmap(86, 73, Images::Hexer);
            break;

        case GameInPlay::Hexic:
            PD::drawBitmap(86, 73, Images::Hexic);
            break;
            
    }

    PD::setColor(7, 0);


    // Has a new High Score been set ?
        
    if (index != NO_SCORE) {
    
        uint8_t digits[5] = {};
        Utils::extractDigits(digits, cookie->lastScore);


        // Render Highlights on either side of the entry ..
        
        PD::drawBitmap(48, 105 + (index * 12), Images::HS_Highlight);
        PD::drawBitmap(170, 105 + (index * 12), Images::HS_Highlight);


        // Render score and name entry ..

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->gamePlayVariables.cursor == x && flash) || this->gamePlayVariables.cursor != x) {
            
                if (this->cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][x] > 0) {

                    PD::setCursor(60 + (x * 10), 105 + (index * 12));
                    PD::print(static_cast<char>(cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][index][x] + 64));

                }
                else {
                    PD::setColor(6, 0);
                    PD::fillRect(60 + (x * 10), 105 + (index * 12), 8, 7);
                }
                
            }

        }
        
        for (uint8_t j = 5; j > 0; --j) {
        
            PD::setCursor(163 - (j * 10), 105 + (index * 12));
            PD::print(digits[j - 1], 10);

        }

    }
    else {
          
        if (Utils::isFrameCount(2)) this->launchParticles(110 + random(-16, 17), 180 + random(-16, 17), ExplosionSize::Large);

    }
        


    // Render remaining scores ..
    
    PD::setColor(6, 0);
    for (uint32_t y = 0; y < 5; y++) {
    
        //Score

        uint8_t digits[5] = {};
        Utils::extractDigits(digits, cookie->score[static_cast<uint8_t>(this->cookie->gameInPlay)][y]);
        
        if (index != y) {

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::setCursor(60 + (x * 10), 105 + (y * 12));

                if (this->cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][y][x] > 0) {
                    PD::print(static_cast<char>(cookie->initials[static_cast<uint8_t>(this->cookie->gameInPlay)][y][x] + 64));
                }
                else {
                    PD::print("_");
                }

            }

            for (uint8_t j = 5; j > 0; --j) {
            
                PD::setCursor(163 - (j * 10), 105 + (y * 12));
                PD::print(digits[j - 1] , 10);
            
            }

        }
        
    }

    PD::drawBitmap(205, 168, Images::VersionNo);

    this->fadeInOut();

}
