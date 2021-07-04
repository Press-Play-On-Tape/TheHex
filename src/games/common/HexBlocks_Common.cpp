#include "../../HexBlocks.h"
#include "../../utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::gameEnd() {

    if (this->gamePlayVariables.gameOverCounter > 0) {

        this->gamePlayVariables.gameOverCounter--;

    }
    else {

        if (this->gamePlayVariables.pearlCreated) {

            PD::drawBitmap(23, 74, Images::Congratulations);
            this->launchParticles(83, 86, ExplosionSize::Large);

        }            
        else {

            PD::drawBitmap(39, 63, Images::GameOver);

        }

        if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
            this->nextGameState = GameState::HighScore_Init;
            this->fadeOut();
            cookie->setLastScore(this->cookie->gameInPlay,  this->gamePlayVariables.score);
        }

    }
 
}

int8_t Game::getCell(const int8_t x, const int8_t y) {

    return this->getCell(BoardType::Main, x, y, false);

}

int8_t Game::getCell(const BoardType boardType, const int8_t x, const int8_t y) {

    return this->getCell(boardType, x, y, false);

}

int8_t Game::getCell(const BoardType boardType, const int8_t x, const int8_t y, const bool absolute) {

    if (x < 0 || x > 8 || y < 0 || y > 8) return Constants::InvalidCell;

    switch (boardType) {

        case BoardType::Main:
            if (absolute) {
                return abs(this->gamePlayVariables.board[x][y]);
            }
            else {
                return this->gamePlayVariables.board[x][y];
            }

        case BoardType::Backup:
            if (absolute) {
                return abs(this->gamePlayVariables.boardBackup[x][y]);
            }
            else {
                return this->gamePlayVariables.boardBackup[x][y];
            }

        case BoardType::Offset:
            if (absolute) {
                return abs(this->gamePlayVariables.boardOffset[x][y]);
            }
            else {
                return this->gamePlayVariables.boardOffset[x][y];
            }

        case BoardType::Populate:
            if (absolute) {
                return abs(this->gamePlayVariables.boardPopulate[x][y]);
            }
            else {
                return this->gamePlayVariables.boardPopulate[x][y];
            }

    }

    return Constants::InvalidCell; 

}


void Game::setCell(const int8_t x, const int8_t y, const int8_t val) {

    this->setCell(BoardType::Main, x, y, val);

}

void Game::setCell(const BoardType boardType, const int8_t x, const int8_t y, const int8_t val) {

    if (x < 0 || x > 8 || y < 0 || y > 8) return;

    switch (boardType) {

        case BoardType::Main:
            this->gamePlayVariables.board[x][y] = val;
            break;

        case BoardType::Backup:
            this->gamePlayVariables.boardBackup[x][y] = val;
            break;

        case BoardType::Offset:
            this->gamePlayVariables.boardOffset[x][y] = val;
            break;

        case BoardType::Populate:
            this->gamePlayVariables.boardPopulate[x][y] = val;
            break;
    }

}
