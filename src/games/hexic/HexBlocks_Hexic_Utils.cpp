#include "../../HexBlocks.h"
#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::levelUp_Hexic() {

    PD::drawBitmap(45, 50, Images::LevelUp);

    uint16_t bonus = 25 * this->gamePlayVariables.movesLeft;
    uint8_t left = 23 + (bonus <= 999 ? 4 : 0) + (bonus <= 99 ? 4 : 0);
    uint8_t width = 124 - (bonus <= 999 ? 7 : 0) - (bonus <= 99 ? 7 : 0);

    if (!this->gamePlayVariables.levelUp.bonusAdded) {

        this->gamePlayVariables.scoreToAdd = bonus;
        this->gamePlayVariables.levelUp.bonusAdded = true;

    }

    PD::setColor(0);
    PD::fillRect(left, 90, width, 9);

    PD::setColor(6, 14);
    PD::setCursor(left + 2, 91);
    PD::adjustCharStep = -1;
    PD::print("Bonus Points: ");
    PD::print(bonus);
    PD::adjustCharStep = 0;

    if (PC::buttons.pressed(BTN_A)) {

        this->populateBoard_Hexic();

        if (this->gamePlayVariables.foundBlackPearls.numberActive() > 0) {

            for (FoundFlower &foundBlackPearl : this->gamePlayVariables.foundBlackPearls.flower) {

                if (foundBlackPearl.active) {

                    this->setCell(BoardType::Populate, foundBlackPearl.x, foundBlackPearl.y, Constants::Hexic::BlackPearl);
                
                }

            }

        }

        this->gamePlayVariables.foundBlackPearls.reset();
        this->gamePlayVariables.levelUp.active = false;
        this->gamePlayVariables.removePieces.state = 0;
        this->gamePlayVariables.removePieces.pos = 0;

    }

}

void Game::removeWinningSequence_AddPoints_Hexic() {

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            switch (this->gamePlayVariables.boardBackup[x][y]) {

                case -127 ... -1:
                    {
                        this->gamePlayVariables.board[x][y] = 0;

                        uint8_t xCentre = 0;
                        uint8_t yCentre = 0;

                        this->getCentreOfTile_Common(x, y, xCentre, yCentre);

                        for (uint8_t i = 0; i < 5; i++) {
                            this->launchParticles(xCentre, yCentre, ExplosionSize::Large);
                        }
                        
                    }

                    break;

                case Constants::Hexic::SilverGem:

                    this->gamePlayVariables.board[x][y] = Constants::Hexic::SilverGem;
                    break;

                case Constants::Hexic::BlackPearl:

                    this->gamePlayVariables.board[x][y] = Constants::Hexic::BlackPearl;
                    break;

                default: break;

            }

        }

    }

    this->gamePlayVariables.removePieces.state++;

}

bool Game::floodFill_Hexic() {

    bool inserted = false;

    for (uint8_t y = Constants::GridSize - 1; y > 0; y--) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (this->getCell(BoardType::Backup, x, y) == 0) {

                if (this->getCell(BoardType::Backup, x, y - 1) != Constants::InvalidCell && this->getCell(BoardType::Backup, x, y - 1) != 0) {

                    this->setCell(BoardType::Offset, x, y - 1, 1);
                    this->setCell(BoardType::Backup, x, y - 1, 0);
                    inserted = true;

                }

            }

        }

    }

    for (uint8_t x = 0; x < Constants::GridSize; x++) {

        if (this->getCell(BoardType::Backup, x, Constants::Hexic::Cell_yTop[x]) == 0) {

            this->gamePlayVariables.boardTop[x] = random(1, Constants::RandomColorMax);
            inserted = true;

        }

    }

    return inserted;

}


bool Game::isValidMovement_Hexic(const int8_t xPlacement, const int8_t yPlacement) {

    if (xPlacement < 0 || xPlacement > 7 || yPlacement < 0 || yPlacement > 14) return false;

    switch (yPlacement) {

        case 0:     return (xPlacement >= 3 && xPlacement <= 4);
        case 1:     return (xPlacement >= 2 && xPlacement <= 5);
        case 2:     return (xPlacement >= 1 && xPlacement <= 6);
        case 3:     return (xPlacement >= 0 && xPlacement <= 7);
        case 4:     return (xPlacement >= 0 && xPlacement <= 7);
        case 5:     return (xPlacement >= 0 && xPlacement <= 7);
        case 6:     return (xPlacement >= 0 && xPlacement <= 7);
        case 7:     return (xPlacement >= 0 && xPlacement <= 7);
        case 8:     return (xPlacement >= 0 && xPlacement <= 7);
        case 9:     return (xPlacement >= 0 && xPlacement <= 7);
        case 10:    return (xPlacement >= 0 && xPlacement <= 7);
        case 11:    return (xPlacement >= 0 && xPlacement <= 7);
        case 12:    return (xPlacement >= 1 && xPlacement <= 6);
        case 13:    return (xPlacement >= 2 && xPlacement <= 5);
        case 14:    return (xPlacement >= 3 && xPlacement <= 4);

    }

    return true;

}


void Game::rotate_Clockwise_Cluster_Hexic() {

    if (this->gamePlayVariables.y % 2 == 0) { 

        if (this->gamePlayVariables.x % 2 == 0) {

            uint8_t xCell = this->gamePlayVariables.x;
            uint8_t yCell = this->gamePlayVariables.y / 2;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = saved;

        }
        else {

            uint8_t xCell = this->gamePlayVariables.x; 
            uint8_t yCell = this->gamePlayVariables.y / 2;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = saved;

        }

    }
    else {

        if (this->gamePlayVariables.x % 2 == 0) {

            uint8_t xCell = this->gamePlayVariables.x;
            uint8_t yCell = (this->gamePlayVariables.y / 2) + 1;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell + 1][yCell - 1];
            this->gamePlayVariables.board[xCell + 1][yCell - 1] = saved;

        }
        else {
            
            uint8_t xCell = this->gamePlayVariables.x; 
            uint8_t yCell = this->gamePlayVariables.y / 2;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = saved;

        }
        
    }   

}

void Game::rotate_AntiClockwise_Cluster_Hexic() {

    uint8_t xCell = 0;
    uint8_t yCell = 0;

    this->getUpperLeftGridCoords_Hexer(xCell, yCell);
    uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

    if (this->gamePlayVariables.y % 2 == 0) { 

        if (this->gamePlayVariables.x % 2 == 0) {

            uint8_t xCell = this->gamePlayVariables.x;
            uint8_t yCell = this->gamePlayVariables.y / 2;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = saved;

        }
        else {

            uint8_t xCell = this->gamePlayVariables.x; 
            uint8_t yCell = this->gamePlayVariables.y / 2;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = saved;

        }

    }
    else {

        if (this->gamePlayVariables.x % 2 == 0) {

            uint8_t xCell = this->gamePlayVariables.x;
            uint8_t yCell = (this->gamePlayVariables.y / 2) + 1;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell - 1];
            this->gamePlayVariables.board[xCell + 1][yCell - 1] = this->gamePlayVariables.board[xCell + 1][yCell];
            this->gamePlayVariables.board[xCell + 1][yCell] = saved;

        }
        else {
            
            uint8_t xCell = this->gamePlayVariables.x; 
            uint8_t yCell = this->gamePlayVariables.y / 2;
            uint8_t saved = this->gamePlayVariables.board[xCell][yCell];

            this->gamePlayVariables.board[xCell][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
            this->gamePlayVariables.board[xCell + 1][yCell + 1] = this->gamePlayVariables.board[xCell][yCell + 1];
            this->gamePlayVariables.board[xCell][yCell + 1] = saved;

        }
        
    }   

}

void Game::rotate_Clockwise_Flower_Hexic(uint8_t xCell, uint8_t yCell) {

    this->selectionOnSilverGem(this->gamePlayVariables.flowerSelected.prevDirection, xCell, yCell);

    if (xCell % 2 == 0) {

        uint8_t saved = this->gamePlayVariables.board[xCell - 1][yCell - 1];

        this->gamePlayVariables.board[xCell - 1][yCell - 1] = this->gamePlayVariables.board[xCell - 1][yCell];
        this->gamePlayVariables.board[xCell - 1][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
        this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell];
        this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell + 1][yCell - 1];
        this->gamePlayVariables.board[xCell + 1][yCell - 1] = this->gamePlayVariables.board[xCell][yCell - 1];
        this->gamePlayVariables.board[xCell][yCell - 1] = saved;

    }
    else {

        uint8_t saved = this->gamePlayVariables.board[xCell][yCell - 1];

        this->gamePlayVariables.board[xCell][yCell - 1] = this->gamePlayVariables.board[xCell - 1][yCell];
        this->gamePlayVariables.board[xCell - 1][yCell] = this->gamePlayVariables.board[xCell - 1][yCell + 1];
        this->gamePlayVariables.board[xCell - 1][yCell + 1] = this->gamePlayVariables.board[xCell][yCell + 1];
        this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        this->gamePlayVariables.board[xCell + 1][yCell + 1] = this->gamePlayVariables.board[xCell + 1][yCell];
        this->gamePlayVariables.board[xCell + 1][yCell] = saved;
 
    }

}

void Game::rotate_AntiClockwise_Flower_Hexic(uint8_t xCell, uint8_t yCell) {

    if (xCell % 2 == 0) {

        uint8_t saved = this->gamePlayVariables.board[xCell][yCell - 1];

        this->gamePlayVariables.board[xCell][yCell - 1] = this->gamePlayVariables.board[xCell + 1][yCell - 1];
        this->gamePlayVariables.board[xCell + 1][yCell - 1] = this->gamePlayVariables.board[xCell + 1][yCell];
        this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell][yCell + 1];
        this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell - 1][yCell];
        this->gamePlayVariables.board[xCell - 1][yCell] = this->gamePlayVariables.board[xCell - 1][yCell - 1];
        this->gamePlayVariables.board[xCell - 1][yCell - 1] = saved;

    }
    else {

        uint8_t saved = this->gamePlayVariables.board[xCell][yCell - 1];

        this->gamePlayVariables.board[xCell][yCell - 1] = this->gamePlayVariables.board[xCell + 1][yCell];
        this->gamePlayVariables.board[xCell + 1][yCell] = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        this->gamePlayVariables.board[xCell + 1][yCell + 1] = this->gamePlayVariables.board[xCell][yCell + 1];
        this->gamePlayVariables.board[xCell][yCell + 1] = this->gamePlayVariables.board[xCell - 1][yCell + 1];
        this->gamePlayVariables.board[xCell - 1][yCell + 1] = this->gamePlayVariables.board[xCell - 1][yCell];
        this->gamePlayVariables.board[xCell - 1][yCell] = saved;

    }

}

void Game::getUpperLeftGridCoords_Hexic(/*out*/ uint8_t &x, /*out*/ uint8_t &y) {

    this->getUpperLeftGridCoords_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y, x, y);

}

void Game::getUpperLeftGridCoords_Hexic(uint8_t xCursor, uint8_t yCursor, /*out*/ uint8_t &x, /*out*/ uint8_t &y) {

    if (yCursor % 2 == 1 && xCursor % 2 == 0) { 

        x = xCursor;
        y = (yCursor / 2) + 1;

    }
    else {
        
        x = xCursor; 
        y = yCursor / 2;

    }

}

bool Game::isSelectionFacingLeft_Hexic() {

    return this->isSelectionFacingLeft_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y);

}

bool Game::isSelectionFacingLeft_Hexic(uint8_t x, uint8_t y) {

    return ((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0));

}

void Game::persistFallingObjects_Hexic() {

    for (int8_t y = Constants::GridSize - 2; y > -1; y--) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (this->getCell(BoardType::Offset, x, y) > 0) {

                this->setCell(x, y + 1, this->getCell(x, y));
                this->setCell(x, y, 0);
                this->setCell(BoardType::Offset, x, y, 0);

            }
            
        }

    }

    // Top cells ..

    for (uint8_t x = 0; x < Constants::GridSize; x++) {

        if (this->gamePlayVariables.boardTop[x] > 0) {

            this->setCell(x, Constants::Hexic::Cell_yTop[x], this->gamePlayVariables.boardTop[x]);
            this->gamePlayVariables.boardTop[x] = 0;

        }

    }

    this->gamePlayVariables.clearBoard(BoardType::Offset);

}

uint8_t Game::checkForCluster(BoardType boardType) {


    // Detect flowers ----------------------------------------------------------------------------

    this->gamePlayVariables.backupBoard(boardType);

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (x % 2 == 0) {

                uint8_t color = this->getCell(BoardType::Backup, x, y);
                if (color < 0) continue;

                if ((this->getCell(BoardType::Backup, x - 1, y)     == color) && 
                    (this->getCell(BoardType::Backup, x + 1, y)     == color) &&
                    (this->getCell(BoardType::Backup, x - 1, y + 1) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 1)     != color) && 
                    (this->getCell(BoardType::Backup, x + 1, y + 1) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 2)     == color)) {

                    this->gamePlayVariables.boardBackup[x][y] = -color;
                    this->gamePlayVariables.boardBackup[x - 1][y] = -color;
                    this->gamePlayVariables.boardBackup[x + 1][y] = -color;
                    this->gamePlayVariables.boardBackup[x - 1][y + 1] = -color;
                    this->gamePlayVariables.boardBackup[x][y + 1] = (abs(color) == Constants::Hexic::SilverGem ? Constants::Hexic::BlackPearl : Constants::Hexic::SilverGem);
                    this->gamePlayVariables.boardBackup[x + 1][y + 1] = -color;
                    this->gamePlayVariables.boardBackup[x][y + 2] = -color;

                    FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                    foundFlower.color = color;
                    foundFlower.active = true;
                    foundFlower.x = x;
                    foundFlower.y = y + 1;

                    if (color == Constants::Hexic::SilverGem) {

                        FoundFlower &foundBlackPearl = this->gamePlayVariables.foundBlackPearls.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                        foundBlackPearl.color = color;
                        foundBlackPearl.active = true;
                        foundBlackPearl.x = x;
                        foundBlackPearl.y = y + 1;

                    }

                }

            }
            else {

                uint8_t color = this->getCell(BoardType::Backup, x, y);
                if (color < 0) continue;

                if ((this->getCell(BoardType::Backup, x - 1, y + 1) == color) && 
                    (this->getCell(BoardType::Backup, x + 1, y + 1) == color) &&
                    (this->getCell(BoardType::Backup, x - 1, y + 2) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 1)     != color) && 
                    (this->getCell(BoardType::Backup, x + 1, y + 2) == color) &&
                    (this->getCell(BoardType::Backup, x, y + 2)     == color)) {

                    this->gamePlayVariables.boardBackup[x][y] = -color;
                    this->gamePlayVariables.boardBackup[x - 1][y + 1] = -color;
                    this->gamePlayVariables.boardBackup[x + 1][y + 1] = -color;
                    this->gamePlayVariables.boardBackup[x - 1][y + 2] = -color;
                    this->gamePlayVariables.boardBackup[x][y + 1] = (abs(color) == Constants::Hexic::SilverGem ? Constants::Hexic::BlackPearl : Constants::Hexic::SilverGem);
                    this->gamePlayVariables.boardBackup[x + 1][y + 2] = -color;
                    this->gamePlayVariables.boardBackup[x][y + 2] = -color;

                    FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[this->gamePlayVariables.foundFlowers.nextAvailable()];
                    foundFlower.color = color;
                    foundFlower.active = true;
                    foundFlower.x = x;
                    foundFlower.y = y + 1;

                }

            }

        }

    }

    if (this->gamePlayVariables.foundFlowers.anyActive()) {

        return Constants::Hexic::FlowerScore * this->gamePlayVariables.foundFlowers.numberActive();

    }


    // Detect Clusters ---------------------------------------------------------

    uint8_t match = 0;

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (x % 2 == 0) { 


                // Piece 1

                uint8_t color = this->getCell(BoardType::Backup, x, y);
                if (color >= 1 && color < Constants::InvalidCell) {

                    for (uint8_t i = 0; i < 6; i++) {

                        if ((this->getCell(boardType, x + Constants::Hexic::ClusterX_Common[i * 2], y + Constants::Hexic::ClusterY_Even[i * 2], true) == color) &&
                            (this->getCell(boardType, x + Constants::Hexic::ClusterX_Common[(i * 2) + 1], y + Constants::Hexic::ClusterY_Even[(i * 2) + 1], true) == color)) {

                            this->setCell(BoardType::Backup, x, y, -color);
                            this->setCell(BoardType::Backup, x + Constants::Hexic::ClusterX_Common[i * 2], y + Constants::Hexic::ClusterY_Even[i * 2], -color);
                            this->setCell(BoardType::Backup, x + Constants::Hexic::ClusterX_Common[(i * 2) + 1], y + Constants::Hexic::ClusterY_Even[(i * 2) + 1], -color);
                            match = match + 3;

                        }

                    }

                }

            }
            else {

                uint8_t color = this->getCell(BoardType::Backup, x, y);

                if (color >= 1 && color < Constants::InvalidCell) {

                    for (uint8_t i = 0; i < 6; i++) {

                        if ((this->getCell(boardType, x + Constants::Hexic::ClusterX_Common[i * 2], y + Constants::Hexic::ClusterY_Odd[i * 2], true) == color) &&
                            (this->getCell(boardType, x + Constants::Hexic::ClusterX_Common[(i * 2) + 1], y + Constants::Hexic::ClusterY_Odd[(i * 2) + 1], true) == color)) {

                            this->setCell(BoardType::Backup, x, y, -color);
                            this->setCell(BoardType::Backup, x + Constants::Hexic::ClusterX_Common[i * 2], y + Constants::Hexic::ClusterY_Odd[i * 2], -color);
                            this->setCell(BoardType::Backup, x + Constants::Hexic::ClusterX_Common[(i * 2) + 1], y + Constants::Hexic::ClusterY_Odd[(i * 2) + 1], -color);
                            match = match + 3;

                        }

                    }

                }

            }
            
        }
        
    }   

    return match;

}


bool Game::selectionOnSilverGem(Direction prevDirection, uint8_t &xCell_Found, uint8_t &yCell_Found) {

    return this->selectionOnSilverGem(prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y, xCell_Found, yCell_Found);

}

bool Game::selectionOnSilverGem(Direction prevDirection, uint8_t xCursor, uint8_t yCursor, uint8_t &xCell_Found, uint8_t &yCell_Found) {

    bool found = false;
    uint8_t color = 0;
    uint8_t xCell = 0;
    uint8_t yCell = 0;

    this->getUpperLeftGridCoords_Hexic(xCursor, yCursor, xCell, yCell);

    if (xCursor % 2 == 0) { 

        if (this->isSelectionFacingLeft_Hexic(xCursor, yCursor)) {

            color = this->getCell(xCell, yCell);
            if (color >= 1 && color < Constants::InvalidCell) {

                if (prevDirection != Direction::Right && prevDirection != Direction::Down && this->getCell(xCell, yCell) == 8)              { found = true; xCell_Found = xCell; yCell_Found = yCell; } 
                if (prevDirection != Direction::Left &&  prevDirection != Direction::Down && this->getCell(xCell + 1, yCell - 1) == 8)      { found = true; xCell_Found = xCell + 1; yCell_Found = yCell - 1; }
                if (prevDirection != Direction::Left && prevDirection != Direction::Up &&  this->getCell(xCell + 1, yCell) == 8)            { found = true; xCell_Found = xCell + 1; yCell_Found = yCell; }

            }


        }
        else {

            color = this->getCell(xCell, yCell);
            if (color >= 1 && color < Constants::InvalidCell) {

                if (prevDirection != Direction::Right && prevDirection != Direction::Down &&  this->getCell(xCell, yCell) == 8)             { found = true; xCell_Found = xCell; yCell_Found = yCell; }
                if (prevDirection != Direction::Left &&  prevDirection != Direction::Down && this->getCell(xCell + 1, yCell) == 8)          { found = true; xCell_Found = xCell + 1; yCell_Found = yCell; }
                if (prevDirection != Direction::Right && prevDirection != Direction::Up &&  this->getCell(xCell, yCell + 1) == 8)           { found = true; xCell_Found = xCell; yCell_Found = yCell + 1; }

            }

        }

    }
    else {

        if (this->isSelectionFacingLeft_Hexic(xCursor, yCursor)) {

            color = this->getCell(xCell, yCell);
            if (color >= 1 && color < Constants::InvalidCell) {

                if (prevDirection != Direction::Right && prevDirection != Direction::Down &&  this->getCell(xCell, yCell) == 8)             { found = true; xCell_Found = xCell; yCell_Found = yCell; }
                if (prevDirection != Direction::Left && prevDirection != Direction::Down &&  this->getCell(xCell + 1, yCell) == 8)          { found = true; xCell_Found = xCell + 1; yCell_Found = yCell; }
                if (prevDirection != Direction::Left &&  prevDirection != Direction::Up && this->getCell(xCell + 1, yCell + 1) == 8)        { found = true; xCell_Found = xCell + 1; yCell_Found = yCell + 1; }

            }


        }
        else {

            color = this->getCell(xCell, yCell);
            if (color >= 1 && color < Constants::InvalidCell) {

                if (prevDirection != Direction::Right &&  prevDirection != Direction::Down && this->getCell(xCell, yCell) == 8)             { found = true; xCell_Found = xCell; yCell_Found = yCell; }
                if (prevDirection != Direction::Left && prevDirection != Direction::Down &&  this->getCell(xCell + 1, yCell + 1) == 8)      { found = true; xCell_Found = xCell + 1; yCell_Found = yCell + 1; }
                if (prevDirection != Direction::Right && prevDirection != Direction::Up &&  this->getCell(xCell, yCell + 1) == 8)           { found = true; xCell_Found = xCell; yCell_Found = yCell + 1; }

            }

        }
        
    }   

    // if we are on a silver gem, is there a full flower around it?

    if (found) {

        xCell = xCell_Found;
        yCell = yCell_Found;

        if (xCell_Found % 2 == 0) {

            if ((this->getCell(BoardType::Backup, xCell, yCell - 1)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell + 1, yCell - 1)     != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell + 1, yCell)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell, yCell + 1)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell - 1, yCell)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell - 1, yCell - 1)     != Constants::InvalidCell)) {

                found = true;

            }
            else {

                found = false;

            }

        }
        else {

            if ((this->getCell(BoardType::Backup, xCell, yCell - 1)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell + 1, yCell)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell + 1, yCell + 1)     != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell, yCell + 1)         != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell - 1, yCell + 1)     != Constants::InvalidCell) && 
                (this->getCell(BoardType::Backup, xCell - 1, yCell)         != Constants::InvalidCell)) {

                found = true;

            }
            else {

                found = false;

            }

        }

    }

    return found;

}

void Game::prepareToClearBoard_Hexic() {

    // Capture black pearl details

    this->gamePlayVariables.foundBlackPearls.reset();

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            uint8_t color = this->getCell(BoardType::Backup, x, y);

            if (color == Constants::Hexic::BlackPearl) {

                FoundFlower &foundBlackPearl = this->gamePlayVariables.foundBlackPearls.flower[this->gamePlayVariables.foundBlackPearls.nextAvailable()];
                foundBlackPearl.color = color;
                foundBlackPearl.active = true;
                foundBlackPearl.x = x;
                foundBlackPearl.y = y;

            }

        }

    }


    for (uint8_t x = 0; x < Constants::GridSize; x++) {

        this->gamePlayVariables.boardBottom[x] = this->getCell(x, Constants::Hexic::Cell_yBottom[x]);

    }

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (this->getCell(BoardType::Main, x, y) == Constants::Hexic::BlackPearl) {

                this->setCell(BoardType::Main, x, y, 0);

            }

            if (this->getCell(BoardType::Offset, x, y) != Constants::InvalidCell && y >= Constants::Hexic::Cell_yTop[x] && y < Constants::Hexic::Cell_yBottom[x]) {

                this->setCell(BoardType::Offset, x, y, 1);

            }

        }

    }

}

void Game::populateBoard_Hexic() {

    this->setCell(BoardType::Main, 0, 0, Constants::InvalidCell);
    this->setCell(BoardType::Main, 1, 0, Constants::InvalidCell);
    this->setCell(BoardType::Main, 2, 0, Constants::InvalidCell);
    this->setCell(BoardType::Main, 6, 0, Constants::InvalidCell);
    this->setCell(BoardType::Main, 7, 0, Constants::InvalidCell);
    this->setCell(BoardType::Main, 8, 0, Constants::InvalidCell);
    this->setCell(BoardType::Main, 0, 1, Constants::InvalidCell);
    this->setCell(BoardType::Main, 8, 1, Constants::InvalidCell);
    this->setCell(BoardType::Main, 0, 7, Constants::InvalidCell);
    this->setCell(BoardType::Main, 1, 7, Constants::InvalidCell);
    this->setCell(BoardType::Main, 7, 7, Constants::InvalidCell);
    this->setCell(BoardType::Main, 8, 7, Constants::InvalidCell);
    this->setCell(BoardType::Main, 0, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 1, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 2, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 3, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 5, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 6, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 7, 8, Constants::InvalidCell);
    this->setCell(BoardType::Main, 8, 8, Constants::InvalidCell);


    this->gamePlayVariables.backupBoard(BoardType::Main, BoardType::Populate);
    this->gamePlayVariables.clearBoard(BoardType::Offset);
    this->gamePlayVariables.clearBoard(BoardType::Main);
    // this->gamePlayVariables.foundBlackPearls.reset();
    // this->gamePlayVariables.levelUp = false;

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            if (this->getCell(BoardType::Populate, x, y) != Constants::InvalidCell && this->getCell(BoardType::Populate, x, y) != Constants::Hexic::BlackPearl) {

                for (uint8_t i = 0; i < 10; i++) {
                    this->setCell(BoardType::Populate, x, y, random(1, 7)); 
                    if (this->checkForCluster(BoardType::Populate) == 0) break;
                }

            }

        }

    }

    this->gamePlayVariables.level++;
    this->gamePlayVariables.movesLeft = this->gamePlayVariables.movesLeft_Orig - 5;
    this->gamePlayVariables.movesLeft_Orig = this->gamePlayVariables.movesLeft_Orig - 5;
    this->gamePlayVariables.levelUp.bonusAdded = false;
    this->gamePlayVariables.populate = 12;

    // this->setCell(BoardType::Populate, 4, 7, Constants::Hexic::BlackPearl);
    // this->setCell(BoardType::Populate, 4, 8, 3);
    // this->setCell(BoardType::Populate, 3, 7, 4);

}
