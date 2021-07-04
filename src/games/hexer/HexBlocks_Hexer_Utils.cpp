#include "../../HexBlocks.h"
#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

bool Game::isValidMovement_Hexer(const int8_t xPlacement, const int8_t yPlacement) {

    if (xPlacement < 0 || xPlacement > 17 || yPlacement < 0 || yPlacement > 7) return false;

    switch (yPlacement) {

        case 0:     return (xPlacement >= 4 && xPlacement <= 12);
        case 1:     return (xPlacement >= 3 && xPlacement <= 13);
        case 2:     return (xPlacement >= 2 && xPlacement <= 14);
        case 3:     return (xPlacement >= 1 && xPlacement <= 15);
        case 4:     return (xPlacement >= 1 && xPlacement <= 15);
        case 5:     return (xPlacement >= 2 && xPlacement <= 14);
        case 6:     return (xPlacement >= 3 && xPlacement <= 13);
        case 7:     return (xPlacement >= 4 && xPlacement <= 12);
        case 8:     return (xPlacement >= 4 && xPlacement <= 12);

    }

    return true;

}

void Game::rotate_Clockwise_Hexer() {

    if (this->gamePlayVariables.y % 2 == 0) { //one top, two bottom

        if (this->gamePlayVariables.x % 2 == 0) {

            uint8_t xCell = this->gamePlayVariables.x / 2;
            uint8_t yCell = this->gamePlayVariables.y;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell - 1][yCell + 1];
            this->gamePlayVariables.board[xCell - 1][yCell + 1] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = saved;

        }
        else {

            uint8_t xCell = this->gamePlayVariables.x / 2; 
            uint8_t yCell = this->gamePlayVariables.y;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = saved;

        }

    }
    else {

        if (this->gamePlayVariables.x % 2 == 0) {

            uint8_t xCell = (this->gamePlayVariables.x / 2) - 1;
            uint8_t yCell = this->gamePlayVariables.y;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = saved;

        }
        else {
            
            uint8_t xCell = this->gamePlayVariables.x / 2; 
            uint8_t yCell = this->gamePlayVariables.y;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = saved;

        }
        
    }   

}

void Game::rotate_AntiClockwise_Hexer() {

    uint8_t xCell = 0;
    uint8_t yCell = 0;

    this->getUpperLeftGridCoords_Hexer(xCell, yCell);
    uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

    if (this->gamePlayVariables.y % 2 == 0) { //one top, two bottom

        if (this->gamePlayVariables.x % 2 == 0) {

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell - 1][yCell + 1];
            this->gamePlayVariables.board[xCell - 1][yCell + 1] = saved;

        }
        else {

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = saved;

        }

    }
    else {

        if (this->gamePlayVariables.x % 2 == 0) {

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = saved;

        }
        else {
            
            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = saved;

        }
        
    }   

}

void Game::getUpperLeftGridCoords_Hexer(/*out*/ uint8_t &x, /*out*/ uint8_t &y) {

    if (this->gamePlayVariables.y % 2 == 1 && this->gamePlayVariables.x % 2 == 0) { 

        x = (this->gamePlayVariables.x / 2) - 1;
        y = this->gamePlayVariables.y;

    }
    else {
        
        x = this->gamePlayVariables.x / 2; 
        y = this->gamePlayVariables.y;

    }

}


void Game::removeWinningSequences_Hexer(const uint8_t piece, /*out*/ uint8_t &match) {

    uint8_t xCell = 0;
    uint8_t yCell = 0;
    uint8_t xCell_Orig = 0;
    uint8_t yCell_Orig = 0;
    uint8_t score = 0;
    uint8_t color = 0;
    uint8_t depth = 0;


    // Detect flowers ----------------------------------------------------------------------------

    this->gamePlayVariables.backupBoard(BoardType::Main);

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (y % 2 == 0) {
                    
                uint8_t color = this->getCell(BoardType::Backup, x, y);
                if (color < 0) continue;

                if ((this->getCell(BoardType::Backup, x + 1, y)     == color) && 
                    (this->getCell(BoardType::Backup, x - 1, y + 1) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 1)     != color) && 
                    (this->getCell(BoardType::Backup, x + 1, y + 1) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 2)     == color) &&
                    (this->getCell(BoardType::Backup, x + 1, y + 2) == color)) {

                    bool flowerFound = false;

                    this->getUpperLeftGridCoords_Hexer(xCell, yCell);
                    this->getUpperLeftGridCoords_Hexer(xCell_Orig, yCell_Orig);
                    
                    if (xCell == x && yCell == y)           { flowerFound = true; }
                    if (xCell == x + 1 && yCell == y)       { flowerFound = true; }
                    if (xCell == x - 1 && yCell == y + 1)   { flowerFound = true; }
                    if (xCell == x + 1 && yCell == y + 1)   { flowerFound = true; }
                    if (xCell == x && yCell == y + 2)       { flowerFound = true; }
                    if (xCell == x + 1 && yCell == y + 2)   { flowerFound = true; }
 
                    if (flowerFound) {  

                        this->gamePlayVariables.boardBackup[x][y] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                        this->gamePlayVariables.boardBackup[x - 1][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 1] = -this->getCell(BoardType::Backup, x, y + 1);
                        this->gamePlayVariables.boardBackup[x + 1][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 2] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundFlower.active = true;
                        foundFlower.x = x;
                        foundFlower.y = y + 1;

                    }

                    if (this->gamePlayVariables.x % 2 == 0) {

                        xCell = xCell - 1;
                        yCell++;

                    }
                    else {

                        xCell++;

                    }

                    xCell_Orig = xCell;
                    yCell_Orig = yCell;
                    
                    if (xCell == x && yCell == y)           flowerFound = true;
                    if (xCell == x + 1 && yCell == y)       flowerFound = true;
                    if (xCell == x - 1 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x && yCell == y + 2)       flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 2)   flowerFound = true;
 
                    if (flowerFound && this->getCell(BoardType::Backup, x, y) > 0) {  // Test to see if a previous flower has invalidated this test ..   

                        this->gamePlayVariables.boardBackup[x][y] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                        this->gamePlayVariables.boardBackup[x - 1][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 1] = -this->getCell(BoardType::Backup, x, y + 1);
                        this->gamePlayVariables.boardBackup[x + 1][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 2] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundFlower.active = true;
                        foundFlower.x = x;
                        foundFlower.y = y + 1;

                    }

                    if (this->gamePlayVariables.x % 2 == 0) {

                        xCell = xCell + 1;
                        yCell++;
                    }
                    else {

                        xCell = xCell - 1;
                        yCell++;
                        
                    }
                    
                    xCell_Orig = xCell;
                    yCell_Orig = yCell;
                    
                    if (xCell == x && yCell == y)           flowerFound = true;
                    if (xCell == x + 1 && yCell == y)       flowerFound = true;
                    if (xCell == x - 1 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x && yCell == y + 2)       flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 2)   flowerFound = true;
 
                    if (flowerFound && this->getCell(BoardType::Backup, x, y) > 0) {  // Test to see if a previous flower has invalidated this test ..     

                        this->gamePlayVariables.boardBackup[x][y] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                        this->gamePlayVariables.boardBackup[x - 1][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 1] = -this->getCell(BoardType::Backup, x, y + 1);
                        this->gamePlayVariables.boardBackup[x + 1][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 2] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundFlower.active = true;
                        foundFlower.x = x;
                        foundFlower.y = y + 1;

                    }

                }

            }
            else {
 
                int8_t color = this->getCell(BoardType::Backup, x, y);
                if (color < 0) continue;

                if ((this->getCell(BoardType::Backup, x + 1, y)     == color) &&
                    (this->getCell(BoardType::Backup, x, y + 1)     == color) &&
                    (this->getCell(BoardType::Backup, x + 1, y + 1) != color) &&
                    (this->getCell(BoardType::Backup, x + 2, y + 1) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 2)     == color) &&
                    (this->getCell(BoardType::Backup, x + 1, y + 2) == color)) {

                    bool flowerFound = false;

                    this->getUpperLeftGridCoords_Hexer(xCell, yCell);
                    this->getUpperLeftGridCoords_Hexer(xCell_Orig, yCell_Orig);

                    if (xCell == x && yCell == y)           flowerFound = true;
                    if (xCell == x + 1 && yCell == y)       flowerFound = true;
                    if (xCell == x && yCell == y + 1)       flowerFound = true;
                    if (xCell == x + 2 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x && yCell == y + 2)       flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 2)   flowerFound = true;

                    if (flowerFound) {  

                        this->gamePlayVariables.boardBackup[x][y] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 1] = -this->getCell(BoardType::Backup, x + 1, y + 1);
                        this->gamePlayVariables.boardBackup[x + 2][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 2] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundFlower.active = true;
                        foundFlower.x = x + 1;
                        foundFlower.y = y + 1;

                    }

                    if (this->gamePlayVariables.x % 2 == 0) {

                        xCell++;

                    }
                    else {

                        xCell++;
                        yCell++;

                    }

                    xCell_Orig = xCell;
                    yCell_Orig = yCell;

                    flowerFound = false;
                    if (xCell == x && yCell == y)           flowerFound = true;
                    if (xCell == x + 1 && yCell == y)       flowerFound = true;
                    if (xCell == x && yCell == y + 1)       flowerFound = true;
                    if (xCell == x + 2 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x && yCell == y + 2)       flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 2)   flowerFound = true;

                    if (flowerFound && this->getCell(BoardType::Backup, x, y) > 0) {  // Test to see if a previous flower has invalidated this test ..  

                        this->gamePlayVariables.boardBackup[x][y] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 1] = -this->getCell(BoardType::Backup, x + 1, y + 1);
                        this->gamePlayVariables.boardBackup[x + 2][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 2] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundFlower.active = true;
                        foundFlower.x = x + 1;
                        foundFlower.y = y + 1;

                    }

                    if (this->gamePlayVariables.x % 2 == 0) {

                        yCell++;

                    }
                    else {

                        xCell = xCell - 1;
                        
                    }

                    xCell_Orig = xCell;
                    yCell_Orig = yCell;

                    flowerFound = false;
                    if (xCell == x && yCell == y)           flowerFound = true;
                    if (xCell == x + 1 && yCell == y)       flowerFound = true;
                    if (xCell == x && yCell == y + 1)       flowerFound = true;
                    if (xCell == x + 2 && yCell == y + 1)   flowerFound = true;
                    if (xCell == x && yCell == y + 2)       flowerFound = true;
                    if (xCell == x + 1 && yCell == y + 2)   flowerFound = true;
 
                    if (flowerFound && this->getCell(BoardType::Backup, x, y) > 0) { // Test to see if a previous flower has invalidated this test ..  
 
                        this->gamePlayVariables.boardBackup[x][y] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 1] = -this->getCell(BoardType::Backup, x + 1, y + 1);
                        this->gamePlayVariables.boardBackup[x + 2][y + 1] = -color;
                        this->gamePlayVariables.boardBackup[x][y + 2] = -color;
                        this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundFlower.active = true;
                        foundFlower.x = x + 1;
                        foundFlower.y = y + 1;

                    }

                }

            }

        }

    }

    if (this->gamePlayVariables.foundFlowers.anyActive()) {

        return;

    }



    // Normal matches ----------------------------------------------------------------


    this->getUpperLeftGridCoords_Hexer(xCell, yCell);

    if (this->gamePlayVariables.y % 2 == 0) { //one top, two bottom

        if (this->gamePlayVariables.x % 2 == 0) {

            switch (piece) {

                case 0:
                    color = this->gamePlayVariables.board[xCell][yCell];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell, color, match);
                    }
                    break;

                case 1:
                    color = this->gamePlayVariables.board[xCell - 1][yCell + 1];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell - 1, yCell + 1, color, match);
                    }
                    break;

                case 2:
                    color = this->gamePlayVariables.board[xCell][yCell + 1];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell + 1, color, match);
                    }
                    break;
            }

        }
        else {

            switch (piece) {

                case 0:
                    color = this->gamePlayVariables.board[xCell][yCell];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell, color, match);
                    }
                    break;

                case 1:
                    color = this->gamePlayVariables.board[xCell + 1][yCell];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell + 1, yCell, color, match);
                    }
                    break;

                case 2:
                    color = this->gamePlayVariables.board[xCell][yCell + 1];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell + 1, color, match);
                    }
                    break;

            }

        }

    }
    else {

        if (this->gamePlayVariables.x % 2 == 0) {

            switch (piece) {

                case 0:
                    color = this->gamePlayVariables.board[xCell][yCell];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell, color, match);
                    }
                    break;

                case 1:            
                    color = this->gamePlayVariables.board[xCell + 1][yCell];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell + 1, yCell, color, match);
                    }
                    break;

                case 2:
                    color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell + 1, yCell + 1, color, match);
                    }
                    break;

            }

        }
        else {

            switch (piece) {

                case 0:
                    color = this->gamePlayVariables.board[xCell][yCell];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell, color, match);
                    }
                    break;

                case 1:
                    color = this->gamePlayVariables.board[xCell][yCell + 1];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell, yCell + 1, color, match);
                    }
                    break;

                case 2:
                    color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
                    if (color >= 1) {
                        removeWinningSequences_Recurse_Hexer(depth, xCell + 1, yCell + 1, color, match);
                    }
                    break;

            }
            
        }
        
    }   

}

void Game::removeWinningSequences_Recurse_Hexer(const uint8_t depth, const uint8_t xCell, const uint8_t yCell, uint8_t const color, uint8_t &matches) {

    if (xCell < 0 || xCell > 8 || yCell < 0 || yCell > 8) return;

    if (yCell % 2 == 1) {

        if (this->getCell(BoardType::Backup, xCell, yCell - 1) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell][yCell - 1] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell, yCell - 1, color, matches); }
        if (this->getCell(BoardType::Backup, xCell + 1, yCell - 1) == color)       { matches++;      this->gamePlayVariables.boardBackup[xCell + 1][yCell - 1] = -color;   removeWinningSequences_Recurse_Hexer(depth + 1, xCell + 1, yCell - 1, color, matches);  }
        if (this->getCell(BoardType::Backup, xCell - 1, yCell) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell - 1][yCell] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell - 1, yCell, color, matches);  }
        if (this->getCell(BoardType::Backup, xCell + 1, yCell) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell + 1][yCell] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell + 1, yCell, color, matches);  }
        if (this->getCell(BoardType::Backup, xCell, yCell + 1) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell][yCell + 1] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell, yCell + 1, color, matches);  }
        if (this->getCell(BoardType::Backup, xCell + 1, yCell + 1) == color)       { matches++;      this->gamePlayVariables.boardBackup[xCell + 1][yCell + 1] = -color;   removeWinningSequences_Recurse_Hexer(depth + 1, xCell + 1, yCell + 1, color, matches);  }

    }
    else {

        if (this->getCell(BoardType::Backup, xCell - 1, yCell - 1) == color)       { matches++;      this->gamePlayVariables.boardBackup[xCell - 1][yCell - 1] = -color;   removeWinningSequences_Recurse_Hexer(depth + 1, xCell - 1, yCell - 1, color, matches); }
        if (this->getCell(BoardType::Backup, xCell, yCell - 1) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell][yCell - 1] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell, yCell - 1, color, matches); }
        if (this->getCell(BoardType::Backup, xCell - 1, yCell) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell - 1][yCell] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell - 1, yCell, color, matches); }
        if (this->getCell(BoardType::Backup, xCell + 1, yCell) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell + 1][yCell] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell + 1, yCell, color, matches); }
        if (this->getCell(BoardType::Backup, xCell - 1, yCell + 1) == color)       { matches++;      this->gamePlayVariables.boardBackup[xCell - 1][yCell + 1] = -color;   removeWinningSequences_Recurse_Hexer(depth + 1, xCell - 1, yCell + 1, color, matches); }
        if (this->getCell(BoardType::Backup, xCell, yCell + 1) == color)           { matches++;      this->gamePlayVariables.boardBackup[xCell][yCell + 1] = -color;       removeWinningSequences_Recurse_Hexer(depth + 1, xCell, yCell + 1, color, matches); }

    }

}

void Game::removeWinningSequence_AddPoints_Hexer() {

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (this->gamePlayVariables.boardBackup[x][y] < 0) {
                
                this->gamePlayVariables.board[x][y] = 0;

                uint8_t xCentre = 0;
                uint8_t yCentre = 0;

                this->getCentreOfTile_Common(x, y, xCentre, yCentre);

                for (uint8_t i = 0; i < 5; i++) {
                    this->launchParticles(xCentre, yCentre, ExplosionSize::Large);
                }

            }

        }

    }

    // PC::wait(1000);    
    this->gamePlayVariables.removePieces.state++;

}


bool Game::floodFill_Hexer() {

    bool inserted = false;

    for (uint8_t y = Constants::GridSize - 1; y > 0; y--) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (this->gamePlayVariables.boardBackup[x][y] == 0) {

                inserted = true;
                int8_t rand = random(0, 2);
                if (rand == 0) rand = -1;
                

                if (y % 2 == 1) {
                    
                    // Fall from the left ..

                    if (rand == -1) {
                            
                        if (this->getCell(BoardType::Backup, x, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x][y - 1] = -rand;
                            this->gamePlayVariables.boardBackup[x][y - 1] = 0;

                        }
                        else if (this->getCell(BoardType::Backup, x + 1, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x + 1, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x + 1][y - 1] = rand;
                            this->gamePlayVariables.boardBackup[x + 1][y - 1] = 0;

                        }

                    }
                    else {
                    
                        // Fall from the right ..

                        if (this->getCell(BoardType::Backup, x + 1, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x + 1, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x + 1][y - 1] = -rand;
                            this->gamePlayVariables.boardBackup[x + 1][y - 1] = 0;

                        }
                        else if (this->getCell(BoardType::Backup, x, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x][y - 1] = rand;
                            this->gamePlayVariables.boardBackup[x][y - 1] = 0;

                        }                       

                    }

                }
                else {

                    // Fall from the left ..

                    if (rand == -1) {
                        
                        if (this->getCell(BoardType::Backup, x - 1, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x - 1, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x - 1][y - 1] = -rand;
                            this->gamePlayVariables.boardBackup[x - 1][y - 1] = 0;

                        }
                        else if (this->getCell(BoardType::Backup, x, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x][y - 1] = rand;
                            this->gamePlayVariables.boardBackup[x][y - 1] = 0;

                        }

                    }
                    else {
                    
                        // Fall from the right ..
                        
                        if (this->getCell(BoardType::Backup, x, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x][y - 1] = -rand;
                            this->gamePlayVariables.boardBackup[x][y - 1] = 0;

                        }
                        else if (this->getCell(BoardType::Backup, x - 1, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x - 1, y - 1) != 0) {

                            this->gamePlayVariables.boardOffset[x - 1][y - 1] = rand;
                            this->gamePlayVariables.boardBackup[x - 1][y - 1] = 0;

                        }                       

                    }

                }

            }

        }

    }

    for (uint8_t x = 0; x < Constants::GridSize; x++) {

        if (this->getCell(BoardType::Main, x, 0) == 0 || this->getCell(BoardType::Offset, x, 0) != 0) {

            this->gamePlayVariables.boardTop[x] = random(1, Constants::RandomColorMax);
            inserted = true;

        }

    }

    return inserted;

}


void Game::persistFallingObjects_Hexer() {

    for (int8_t y = Constants::GridSize - 2; y > -1; y--) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (y % 2 == 0) {

                switch (this->gamePlayVariables.boardOffset[x][y]) {

                    case -1:
                        this->gamePlayVariables.board[x - 1][y + 1] = this->gamePlayVariables.board[x][y];
                        this->gamePlayVariables.board[x][y] = 0;
                        break;

                    case 1:
                        this->gamePlayVariables.board[x][y + 1] = this->gamePlayVariables.board[x][y];
                        this->gamePlayVariables.board[x][y] = 0;
                        break;

                }

            }
            else {

                switch (this->gamePlayVariables.boardOffset[x][y]) {

                    case -1:
                        this->gamePlayVariables.board[x][y + 1] = this->gamePlayVariables.board[x][y];
                        this->gamePlayVariables.board[x][y] = 0;
                        break;

                    case 1:
                        this->gamePlayVariables.board[x + 1][y + 1] = this->gamePlayVariables.board[x][y];
                        this->gamePlayVariables.board[x][y] = 0;
                        break;

                }

            }
            
        }

    }

    // Top cells ..

    for (uint8_t x = 0; x < Constants::GridSize; x++) {

        if (this->gamePlayVariables.boardTop[x] > 0) {

            this->gamePlayVariables.board[x][0] = this->gamePlayVariables.boardTop[x];
            this->gamePlayVariables.boardTop[x] = 0;

        }

    }

    this->gamePlayVariables.clearBoard(BoardType::Offset);

}