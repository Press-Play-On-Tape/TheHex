#pragma once

#include "Constants.h"
#include "Utils.h"

struct GamePlayVariables {

    int8_t x = 9;
    int8_t y = 0;
    
    int8_t board[9][9];
    int8_t boardBackup[9][9];
    int8_t boardOffset[9][9];
    int8_t boardPopulate[9][9];
    int8_t boardTop[9];
    int8_t boardBottom[9];
    uint16_t score = 0;
    uint16_t scoreToAdd = 0;
    uint8_t cursor;
    uint8_t gameOverCounter = 0;
    uint8_t timer = Constants::Hexer::TimerMax;
    uint16_t movesLeft = 85;
    uint16_t movesLeft_Orig = 85;
    uint16_t level = 0;
    uint8_t populate = 0;

    bool gameOver = false;
    bool pearlCreated = false;
    FlowerSelected flowerSelected;

    RemovePieces removePieces;
    FoundFlowers foundFlowers;
    FoundFlowers foundBlackPearls;
    LevelUp levelUp;

    Direction prevDirection = Direction::None;

    void reset() {

        this->x = 9;
        this->y = 0;
        
        this->clearBoard(BoardType::Main);
        this->clearBoard(BoardType::Backup);
        this->clearBoard(BoardType::Offset);
        this->clearBoard(BoardType::Populate);

        for (uint8_t i = 0; i < 9; i++) {
            this->boardTop[i];
            this->boardBottom[i];
        }

        this->score = 0;
        this->scoreToAdd = 0;
        this->cursor;
        this->gameOverCounter = 0;
        this->timer = Constants::Hexer::TimerMax;
        this->movesLeft = 85;
        this->movesLeft_Orig = 85;
        this->level = 0;
        this->populate = 0;

        this->gameOver = false;
        this->pearlCreated = false;
        this->flowerSelected.reset();

        this->removePieces.reset();
        this->foundFlowers.reset();
        this->foundBlackPearls.reset();
        this->levelUp.reset();

        Direction prevDirection = Direction::None;


    }


    void backupBoard(BoardType boardType) {

        this->backupBoard(boardType, BoardType::Backup);

    }

    void backupBoard(BoardType from, BoardType to) {

        switch (from) {

            case BoardType::Main:

                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {

                        switch (to) {

                            case BoardType::Backup:
                                this->boardBackup[x][y] = this->board[x][y];
                                break;

                            case BoardType::Offset:
                                this->boardOffset[x][y] = this->board[x][y];
                                break;

                            case BoardType::Populate:
                                this->boardPopulate[x][y] = this->board[x][y];
                                break;

                            default: break;

                        }

                    }

                }
                break;

            case BoardType::Backup:

                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {

                        switch (to) {

                            case BoardType::Main:
                                this->board[x][y] = this->boardBackup[x][y];
                                break;

                            case BoardType::Offset:
                                this->boardOffset[x][y] = this->boardBackup[x][y];
                                break;

                            case BoardType::Populate:
                                this->boardPopulate[x][y] = this->boardBackup[x][y];
                                break;

                            default: break;

                        }

                    }

                }
                break;

            case BoardType::Offset:

                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {

                        switch (to) {

                            case BoardType::Main:
                                this->board[x][y] = this->boardOffset[x][y];
                                break;

                            case BoardType::Backup:
                                this->boardBackup[x][y] = this->boardOffset[x][y];
                                break;

                            case BoardType::Populate:
                                this->boardPopulate[x][y] = this->boardOffset[x][y];
                                break;

                            default: break;

                        }

                    }

                }
                break;

            case BoardType::Populate:

                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {

                        switch (to) {

                            case BoardType::Main:
                                this->board[x][y] = this->boardPopulate[x][y];
                                break;

                            case BoardType::Backup:
                                this->boardBackup[x][y] = this->boardPopulate[x][y];
                                break;

                            case BoardType::Offset:
                                this->boardOffset[x][y] = this->boardPopulate[x][y];
                                break;

                            default: break;

                        }

                    }

                }
                break;

            default: break;

        }

    }

    void clearBoard(BoardType boardType) {

        this->clearBoard(boardType, false);

    }

    void clearBoard(BoardType boardType, bool allCells) {

        switch (boardType) {

            case BoardType::Main:
                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {
                        
                        if (allCells || this->board[x][y] != Constants::InvalidCell) {

                            this->board[x][y] = 0;

                        }

                    }

                }
                break;

            case BoardType::Backup:
                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {
                        
                        if (allCells || this->boardBackup[x][y] != Constants::InvalidCell) {

                            this->boardBackup[x][y] = 0;

                        }

                    }

                }
                break;

            case BoardType::Offset:

                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {

                        this->boardOffset[x][y] = 0;

                    }

                }

                break;

            case BoardType::Populate:

                for (uint8_t y = 0; y < Constants::GridSize; y++) {

                    for (uint8_t x = 0; x < Constants::GridSize; x++) {
                        
                        if (allCells || this->boardPopulate[x][y] != Constants::InvalidCell) {

                            this->boardPopulate[x][y] = 0;

                        }

                    }

                }

                break;

            default: break;

        }

    }

};
