#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../images/Images.h"
#include "../../entities/Entities.h"


void Game::renderScreen_Common() {

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::Cell_Count[y]; x++) {

            uint8_t xCell = Constants::Cell_Min_X[y] + x;
            uint8_t value = gamePlayVariables.board[xCell][y];

            PD::drawBitmap(Constants::Cell_xPos[y] + (x * 18), Constants::Cell_yPos[y], Images::Hex_Combined[value]);

        }

    }

}

void Game::renderBackground_Common() {

    uint8_t rightLimit = (this->gameState == GameState::Title || this->gameState == GameState::Intro_Hexon || this->gameState == GameState::Intro_Hexer || this->gameState == GameState::Intro_Hexic ? 220 : 171);


    if (Utils::isFrameCount(2) == 0) {
        this->backgroundVariables.titleOffsetTop = this->backgroundVariables.titleOffsetTop - 1;
        if (this->backgroundVariables.titleOffsetTop < - 220) this->backgroundVariables.titleOffsetTop = 0;
    }

    this->backgroundVariables.titleOffsetTop = this->backgroundVariables.titleOffsetTop - 1;
    if (this->backgroundVariables.titleOffsetTop < - 220) this->backgroundVariables.titleOffsetTop = 0;

    this->backgroundVariables.titleOffsetBottom = this->backgroundVariables.titleOffsetBottom + 1;
    if (this->backgroundVariables.titleOffsetBottom == 0) this->backgroundVariables.titleOffsetBottom = -220;

    for (uint8_t i = 0; i < 6; i++) {

        int16_t x = this->backgroundVariables.titleOffsetBottom + Constants::Background_xBlue[i];

        if (x > -28 && x < rightLimit)                 PD::drawBitmap(x, Constants::Background_yBlue[i], Images::BG_Blue);
        if (x + 220 > -28 && x + 220 < rightLimit)     PD::drawBitmap(x + 220, Constants::Background_yBlue[i], Images::BG_Blue);

    }

    for (uint8_t i = 0; i < 19; i++) {

        int16_t x = this->backgroundVariables.titleOffsetTop + Constants::Background_xBurgundy[i];

        if (x > -28 && x < rightLimit)                 PD::drawBitmap(x, Constants::Background_yBurgundy[i], Images::BG_Burgundy);
        if (x + 220 > -28 && x + 220 < rightLimit)     PD::drawBitmap(x + 220, Constants::Background_yBurgundy[i], Images::BG_Burgundy);

    }

}

void Game::renderFlowers() {

    for (FoundFlower &flower : this->gamePlayVariables.foundFlowers.flower) {

        if (flower.active) {

            uint8_t xCentre = 0;
            uint8_t yCentre = 0;

            this->getCentreOfTile_Common(flower.x, flower.y, xCentre, yCentre);

            PD::drawBitmap(Constants::Cell_xPos[flower.y] + (flower.x * 18) - 20, Constants::Cell_yPos[flower.y] - 13 + 9, Images::Flower);

        }

    }

}