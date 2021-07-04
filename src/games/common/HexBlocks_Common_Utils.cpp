#include "../../HexBlocks.h"
#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::printBoard() {

    #ifdef DEBUG

        printf("----------------------------------------\n");

            printf("  | ");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                printf("  ");

            }   

            printf(".");

            printf(" | ");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                printf("  ");

            }   

            printf(".");

            printf(" | ");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {
                
                printf("%i.", this->gamePlayVariables.boardTop[x]);

            }   

            printf("\n");


        for (uint8_t y = 0; y < Constants::GridSize; y++) {

            printf("%i | ", y);

            if (y % 2 == 1) printf(".");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                if (this->gamePlayVariables.board[x][y] == 127) {
                    printf("X.");
                }
                else {
                    printf("%i.", this->gamePlayVariables.board[x][y]);
                }

            }   

            if (y % 2 == 0) printf(".");

            printf(" | ");

            if (y % 2 == 1) printf(".");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                if (this->gamePlayVariables.boardBackup[x][y] == 127) {
                    printf("X.");
                }
                else {
                    printf("%i.", this->gamePlayVariables.boardBackup[x][y]);
                }

            }   

            if (y % 2 == 0) printf(".");

            printf(" | ");

            if (y % 2 == 1) printf(".");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                if (this->gamePlayVariables.boardOffset[x][y] == 127) {
                    printf("X.");
                }
                else {
                    printf("%i.", this->gamePlayVariables.boardOffset[x][y]);
                }

            }   

            if (y % 2 == 0) printf(".");

            printf(" | ");

            if (y % 2 == 1) printf(".");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                if (this->gamePlayVariables.boardPopulate[x][y] == 127) {
                    printf("X.");
                }
                else {
                    printf("%i.", this->gamePlayVariables.boardPopulate[x][y]);
                }

            }   

            printf("\n");

        }


            printf("  | ");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                printf("  ");

            }   

            printf(".");

            printf(" | ");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                printf("  ");

            }   

            printf(".");

            printf(" | ");

            for (uint8_t x = 0; x < Constants::GridSize; x++) {
                
                printf("%i.", this->gamePlayVariables.boardBottom[x]);

            }   

            printf("\n");


    #endif

}

void Game::playTheme(uint8_t trackNumber) {

    #ifdef SOUNDS

    constexpr char themes[3][17] = { "music/Hex_01.raw", "music/Hex_02.raw", "music/Hex_03.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            if (this->mainThemeFile.openRO(themes[trackNumber])) {
                auto& music = Audio::play<0>(mainThemeFile);
                music.setLoop(true);
            }

            break;

        case SoundEffects::SFX:
        case SoundEffects::None:

            this->muteTheme();

    }

    #endif

}

void Game::muteTheme() {

    #ifdef SOUNDS
    Audio::stop<0>();
    #endif

}


void Game::playSoundEffect(SoundTheme soundEffect) {

    #ifdef SOUNDS

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:

            switch (soundEffect) {
                
                case SoundTheme::Bubble1:
                    Audio::play<1>(Sounds::sfx_HexSFX_01);    
                    break;
                
                case SoundTheme::LevelUp1:
                    Audio::play<1>(Sounds::sfx_LevelUp1);    
                    break;
                
                case SoundTheme::LevelUp2:
                    Audio::play<1>(Sounds::sfx_LevelUp2);    
                    break;
                        
            }

            break;

        default: break;
        
    }        

    #endif

}    

void Game::getCentreOfTile_Common(const uint8_t x, const uint8_t y, uint8_t &xCentre, uint8_t &yCentre) {

    xCentre = Constants::Cell_xPos[4] + (x * 18) + 8;
    yCentre = Constants::Cell_yPos[y] + 8;

}

uint8_t Game::min(const uint8_t x, const uint8_t y) {

    return x < y ? x : y;

}

void Game::drawHexagon(uint8_t width) {

    uint16_t apothem = width * 0.866;

    int16_t x = 110 - (width / 2);
    int16_t y = 88 - width;

    PD::setColor(0);
    PD::fillRect(x, y, width, apothem * 2);  
    PD::fillTriangle(x, y, x, y + apothem, x - (width / 2), y + apothem); // top left
    PD::fillTriangle(x, y + (apothem * 2), x, y + apothem, x - (width / 2), y + apothem); // bottom left
    PD::fillTriangle(x + width, y, x + width, y + apothem, x + width + (width / 2), y + apothem); // top right
    PD::fillTriangle(x + width, y + apothem, x + width, y + (2 * apothem), x + width + (width / 2), y + apothem); // top right

}

void Game::drawHexagonAlt(uint8_t width) {

    uint16_t apothem = width * 0.866;

    int16_t x = 110 - (width / 2);
    int16_t y = 88 - width;

    PD::setColor(0);
    PD::fillRect(0, 0, 220, y);  
    PD::fillRect(0, y + apothem * 2, 220, 188 - (y + apothem * 2));  

    PD::fillRect(0, 0, x - (width / 2), 188);  
    PD::fillRect(x + width + (width / 2), 0, 220 - (x + width + (width / 2)), 188);  
    PD::fillTriangle(0, 0, x, y, x - (width / 2), y + apothem); // top left
    PD::fillTriangle(0, 188, x, y + (apothem * 2), x - (width / 2), y + apothem); // bottom left
    PD::fillTriangle(220, 0, x + width, y, x + width + (width / 2), y + apothem); // top right
    PD::fillTriangle(220, 188, x + width, y + (2 * apothem), x + width + (width / 2), y + apothem); // top right

}

void Game::fadeOut() {

    this->fadeVariables.size = 5;
    this->fadeVariables.direction = FadeDirection::Out;

}


void Game::fadeIn() {

    this->fadeVariables.size = 5;
    this->fadeVariables.direction = FadeDirection::In;

}


// Handle fade in and out movements?

void Game::fadeInOut() {


    // Draw fade out?

    switch (this->fadeVariables.direction) {

        case FadeDirection::Out:

            if (this->fadeVariables.size > 0) {

                this->drawHexagon(this->fadeVariables.size);

                this->fadeVariables.size = this->fadeVariables.size * 2;

                if (this->fadeVariables.size > 150) {

                    this->gameState = this->nextGameState;
                    this->fadeVariables.direction = FadeDirection::None;

                }

            }

            break;

        case FadeDirection::In:
        
            if (this->fadeVariables.size > 0) {

                this->drawHexagonAlt(this->fadeVariables.size);
                this->fadeVariables.size = this->fadeVariables.size * 2;

                if (this->fadeVariables.size > 150) {

                    this->fadeVariables.direction = FadeDirection::None;

                }

            }

            break;

    }

}


