#include "../../HexBlocks.h"
#include "../../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::game_Init_Hexic() {
    
    this->gameState = GameState::Game_Hexic;

    this->gamePlayVariables.reset();
    this->gamePlayVariables.level = 0;
    this->gamePlayVariables.x = 4;
    this->gamePlayVariables.y = 3;

    this->gamePlayVariables.clearBoard(BoardType::Main, true);
    this->populateBoard_Hexic();

    PC::buttons.pollButtons();
    this->fadeIn();
    
}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game_Hexic() {


    // Handle score ..

    if (this->gamePlayVariables.scoreToAdd > 0) {

        if (this->gamePlayVariables.scoreToAdd >= 50) {

            this->gamePlayVariables.scoreToAdd = this->gamePlayVariables.scoreToAdd - 50;
            this->gamePlayVariables.score = this->gamePlayVariables.score + 50;

        }
        else {

            this->gamePlayVariables.scoreToAdd--;
            this->gamePlayVariables.score++;

        }

    }


    if (!this->gamePlayVariables.gameOver && !this->gamePlayVariables.levelUp.active && this->gamePlayVariables.populate == 0) {


        //  Handle movements ..

        if (PC::buttons.released(BTN_C)) {

            this->gameState = GameState::Pause_Hexic_Init;

        }

        if (PC::buttons.held(BTN_C, 16)) {

            this->nextGameState = GameState::Title_Init;
            this->fadeOut();

        }

        if (!this->gamePlayVariables.removePieces.active) {

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, REPEAT_VAL)) { 

                uint8_t xFound = 0;
                uint8_t yFound = 0;

                if (this->gamePlayVariables.prevDirection != Direction::None && this->gamePlayVariables.prevDirection != Direction::Left) this->gamePlayVariables.prevDirection = Direction::None;

                if ((this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x - 1, this->gamePlayVariables.y, xFound, yFound)) ||
                    (this->gamePlayVariables.flowerSelected.mode == SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y, xFound, yFound))) {

                    switch (this->gamePlayVariables.flowerSelected.mode) {

                        case SelectionMode::None:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x - 1, this->gamePlayVariables.y)) {

                                this->gamePlayVariables.x--;
                                this->gamePlayVariables.prevDirection = Direction::Left;

                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerTouched;         
                            break;


                        case SelectionMode::FlowerTouched:

                            this->gamePlayVariables.prevDirection = Direction::None;
                            this->gamePlayVariables.flowerSelected.x = xFound;
                            this->gamePlayVariables.flowerSelected.y = yFound;
                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerSelected;

                            break;

                        case SelectionMode::FlowerSelected:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x - 1, this->gamePlayVariables.y)) {

                                this->gamePlayVariables.x--;
                                this->gamePlayVariables.prevDirection = Direction::Left;

                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;         
                            break;

                    }

                }
                else {

                    if (this->isValidMovement_Hexic(this->gamePlayVariables.x - 1, this->gamePlayVariables.y)) {

                        this->gamePlayVariables.x--;
                        this->gamePlayVariables.prevDirection = Direction::Left;

                    }

                    this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;

                }

            }

            if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, REPEAT_VAL)) { 

                uint8_t xFound = 0;
                uint8_t yFound = 0;

                if (this->gamePlayVariables.prevDirection != Direction::None && this->gamePlayVariables.prevDirection != Direction::Right) this->gamePlayVariables.prevDirection = Direction::None;

                if ((this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x + 1, this->gamePlayVariables.y, xFound, yFound)) ||
                    (this->gamePlayVariables.flowerSelected.mode == SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y, xFound, yFound))) {

                    switch (this->gamePlayVariables.flowerSelected.mode) {

                        case SelectionMode::None:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x + 1, this->gamePlayVariables.y)) {

                                this->gamePlayVariables.x++;
                                this->gamePlayVariables.prevDirection = Direction::Right;

                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerTouched;         
                            break;


                        case SelectionMode::FlowerTouched:

                            this->gamePlayVariables.prevDirection = Direction::None;
                            this->gamePlayVariables.flowerSelected.x = xFound;
                            this->gamePlayVariables.flowerSelected.y = yFound;
                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerSelected;         

                            break;

                        case SelectionMode::FlowerSelected:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x + 1, this->gamePlayVariables.y)) {

                                this->gamePlayVariables.x++;
                                this->gamePlayVariables.prevDirection = Direction::Right;

                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;      
                            break;

                    }

                }
                else {

                    if (this->isValidMovement_Hexic(this->gamePlayVariables.x + 1, this->gamePlayVariables.y)) {

                        this->gamePlayVariables.x++;
                        this->gamePlayVariables.prevDirection = Direction::Right;

                    }

                    this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;

                }

            }

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) { 

                uint8_t xFound = 0;
                uint8_t yFound = 0;

                if (this->gamePlayVariables.prevDirection != Direction::None && this->gamePlayVariables.prevDirection != Direction::Up) this->gamePlayVariables.prevDirection = Direction::None;

                if ((this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y - 1, xFound, yFound)) ||
                    (this->gamePlayVariables.flowerSelected.mode == SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y, xFound, yFound))) {

                    switch (this->gamePlayVariables.flowerSelected.mode) {

                        case SelectionMode::None:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y - 1)) {
                                this->gamePlayVariables.y--;
                                this->gamePlayVariables.prevDirection = Direction::Up;
                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerTouched;         
                            break;


                        case SelectionMode::FlowerTouched:

                            this->gamePlayVariables.prevDirection = Direction::None;
                            this->gamePlayVariables.flowerSelected.x = xFound;
                            this->gamePlayVariables.flowerSelected.y = yFound;
                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerSelected;         

                            break;

                        case SelectionMode::FlowerSelected:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y - 1)) {
                                this->gamePlayVariables.y--;
                                this->gamePlayVariables.prevDirection = Direction::Up;
                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;     
                            break;

                    }


                }
                else {

                    if (this->isValidMovement_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y - 1)) {

                        this->gamePlayVariables.y--;
                        this->gamePlayVariables.prevDirection = Direction::Up;

                    }

                    this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;

                }

            }

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) { 

                uint8_t xFound = 0;
                uint8_t yFound = 0;

                if (this->gamePlayVariables.prevDirection != Direction::None && this->gamePlayVariables.prevDirection != Direction::Down) this->gamePlayVariables.prevDirection = Direction::None;

                if ((this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y + 1, xFound, yFound)) ||
                    (this->gamePlayVariables.flowerSelected.mode == SelectionMode::FlowerTouched && this->selectionOnSilverGem(this->gamePlayVariables.prevDirection, this->gamePlayVariables.x, this->gamePlayVariables.y, xFound, yFound))) {

                    switch (this->gamePlayVariables.flowerSelected.mode) {

                        case SelectionMode::None:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y + 1)) {

                                this->gamePlayVariables.y++;
                                this->gamePlayVariables.prevDirection = Direction::Down;

                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerTouched;    
                            break;


                        case SelectionMode::FlowerTouched:

                            this->gamePlayVariables.prevDirection = Direction::None;
                            this->gamePlayVariables.flowerSelected.x = xFound;
                            this->gamePlayVariables.flowerSelected.y = yFound;
                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::FlowerSelected;         

                            break;

                        case SelectionMode::FlowerSelected:

                            if (this->isValidMovement_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y + 1)) {

                                this->gamePlayVariables.y++;
                                this->gamePlayVariables.prevDirection = Direction::Down;

                            }             

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;        
                            break;

                    }


                }
                else {

                    if (this->isValidMovement_Hexic(this->gamePlayVariables.x, this->gamePlayVariables.y + 1)) {

                        this->gamePlayVariables.y++;
                        this->gamePlayVariables.prevDirection = Direction::Down;

                    }

                    this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;

                }

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->gamePlayVariables.movesLeft--;

                if (this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerSelected) {

                    this->rotate_Clockwise_Cluster_Hexic();

                }
                else {

                    uint8_t xCell = 0;
                    uint8_t yCell = 0;

                    this->selectionOnSilverGem(this->gamePlayVariables.flowerSelected.prevDirection, xCell, yCell);
                    this->rotate_Clockwise_Flower_Hexic(xCell, yCell);

                }

                this->gamePlayVariables.removePieces.active = true;
                this->gamePlayVariables.removePieces.state = 0;
                this->gamePlayVariables.removePieces.pos = Constants::RotatePiecesIndexStart;
                this->gamePlayVariables.removePieces.rotateDirection = RotateDirection::Clockwise;

            }

            if (PC::buttons.pressed(BTN_B)) {

                this->gamePlayVariables.movesLeft--;
                
                if (this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerSelected) {

                    this->rotate_AntiClockwise_Cluster_Hexic();

                }
                else {

                    uint8_t xCell = 0;
                    uint8_t yCell = 0;

                    this->selectionOnSilverGem(this->gamePlayVariables.flowerSelected.prevDirection, xCell, yCell);
                    this->rotate_AntiClockwise_Flower_Hexic(xCell, yCell);

                }

                this->gamePlayVariables.removePieces.active = true;
                this->gamePlayVariables.removePieces.state = 0;
                this->gamePlayVariables.removePieces.pos = Constants::RotatePiecesIndexStart;
                this->gamePlayVariables.removePieces.rotateDirection = RotateDirection::AntiClockwise;

            }

        }

    }


    // Remove pieces ..

    if (this->gamePlayVariables.removePieces.active) {

        uint8_t xBackup = this->gamePlayVariables.flowerSelected.x;
        uint8_t yBackup = this->gamePlayVariables.flowerSelected.y; 
        uint8_t matches = 0;

        this->gamePlayVariables.foundFlowers.reset();

        switch (this->gamePlayVariables.removePieces.state) {

            case 0: // Finish rotating the piece ..

                if (this->gamePlayVariables.removePieces.pos > 0) {
                    
                    this->gamePlayVariables.removePieces.pos = this->gamePlayVariables.removePieces.pos - 2;


                }
                else {

                   this->gamePlayVariables.removePieces.state++;

                }

                break;

            case 1:

                this->gamePlayVariables.clearBoard(BoardType::Offset);
                matches = this->checkForCluster(BoardType::Main);

                // Did we have any 'flower' matches?

                if (this->gamePlayVariables.foundFlowers.anyActive()) {

                    this->gamePlayVariables.removePieces.state = 2; 
                    this->gamePlayVariables.scoreToAdd = this->gamePlayVariables.foundFlowers.numberActive() * 500;
                    this->playSoundEffect(SoundTheme::Bubble1);

                    for (uint8_t i = 0; i < this->gamePlayVariables.foundFlowers.numberActive(); i++) {

                        FoundFlower &foundFlower = this->gamePlayVariables.foundFlowers.flower[i];

                        if (foundFlower.color == Constants::Hexic::SilverGem) {

                            this->gamePlayVariables.movesLeft++;
                            this->gamePlayVariables.levelUp.active = true;
                            this->gamePlayVariables.levelUp.counter = 9;
                            this->playSoundEffect(SoundTheme::LevelUp1);

                        }

                        if (foundFlower.color == Constants::Hexic::BlackPearl) {

                            this->gamePlayVariables.gameOver = true;
                            this->gamePlayVariables.gameOverCounter = 50;
                            this->gamePlayVariables.pearlCreated = true;

                            uint16_t bonus = 25 * this->gamePlayVariables.movesLeft;

                            if (!this->gamePlayVariables.levelUp.bonusAdded) {

                                this->gamePlayVariables.scoreToAdd = bonus;
                                this->gamePlayVariables.levelUp.bonusAdded = true;
                                this->playSoundEffect(SoundTheme::LevelUp2);

                            }

                        }

                    }

                }
                else {

                    // Any other points?

                    this->gamePlayVariables.removePieces.state = this->gamePlayVariables.removePieces.state + (matches >= 3 ? 1 : 3); 
                    
                    if (matches >= 3) {

                        this->gamePlayVariables.scoreToAdd = matches * 2; 
                        this->playSoundEffect(SoundTheme::Bubble1);

                    }

                }

                break;

            case 2:

                this->removeWinningSequence_AddPoints_Hexic();
                this->gamePlayVariables.removePieces.delay = Constants::RemovingPiecesDelay;
                break;

            case 3:

                if (this->gamePlayVariables.removePieces.delay > 0) {
                    this->gamePlayVariables.removePieces.delay--;
                }
                else {
                    this->gamePlayVariables.removePieces.state++;
                    this->gamePlayVariables.removePieces.pos = 0; 
                }
                break;

            case 4:

                if (this->gamePlayVariables.removePieces.pos > 0 && this->gamePlayVariables.removePieces.pos < 16) {

                    this->gamePlayVariables.removePieces.pos = this->gamePlayVariables.removePieces.pos + 3;

                }
                else {

                    this->persistFallingObjects_Hexic();

                    if (!this->gamePlayVariables.levelUp.active && this->gamePlayVariables.populate == 0) {

                        this->gamePlayVariables.backupBoard(BoardType::Main);

                        if (!this->floodFill_Hexic()) { 

                            this->gamePlayVariables.foundFlowers.reset();
                            uint8_t matches = this->checkForCluster(BoardType::Main);

                            if (matches > 0) {

                                this->gamePlayVariables.removePieces.state = 2; 
                                this->gamePlayVariables.scoreToAdd = (matches >= 3 ? matches * 2 : 0); 
                                this->playSoundEffect(SoundTheme::Bubble1);

                            }
                            else {
                            
                                this->gamePlayVariables.removePieces.state++; 
                            
                            }

                        }
                        else {

                            this->gamePlayVariables.removePieces.pos = 1; 
                            this->gamePlayVariables.removePieces.state = 4; 

                        }

                    }

                }

                break;

            default: 

                if (this->gamePlayVariables.flowerSelected.mode == SelectionMode::FlowerSelected) {

                    uint8_t xFound = 0;
                    uint8_t yFound = 0;

                    if (this->selectionOnSilverGem(this->gamePlayVariables.flowerSelected.prevDirection, xFound, yFound)) {

                        if (xFound != xBackup || yFound != yBackup) {

                            this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;

                        }

                    }
                    else {
 
                        this->gamePlayVariables.flowerSelected.mode = SelectionMode::None;
                       
                    }

                }

                this->gamePlayVariables.removePieces.pos = 0; 
                this->gamePlayVariables.removePieces.active = false;
                break;

        }

    }


    // Populate board ..

    if (this->gamePlayVariables.populate > 0) {

        if (this->gamePlayVariables.removePieces.pos > 0 && this->gamePlayVariables.removePieces.pos < 16) {

            this->gamePlayVariables.removePieces.pos = this->gamePlayVariables.removePieces.pos + 3;

        }
        else {

            persistFallingObjects_Hexic();

            //Clear top ..
            for (uint8_t i = 0; i < Constants::GridSize; i++) { this->gamePlayVariables.boardTop[i] = 0; }

            switch (this->gamePlayVariables.populate) {

                case 12:
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 8);
                    break;

                case 11:
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 7);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 7);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 7);
                    break;

                case 10:
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 7);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 6);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 6);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 6);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 7);
                    break;

                case 9:
                    this->gamePlayVariables.boardTop[1] = this->getCell(BoardType::Populate, 1, 6);
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 6);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 5);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 5);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 5);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 6);
                    this->gamePlayVariables.boardTop[7] = this->getCell(BoardType::Populate, 7, 6);
                    break;

                case 8:
                    this->gamePlayVariables.boardTop[0] = this->getCell(BoardType::Populate, 0, 6);
                    this->gamePlayVariables.boardTop[1] = this->getCell(BoardType::Populate, 1, 5);
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 5);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 4);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 4);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 4);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 5);
                    this->gamePlayVariables.boardTop[7] = this->getCell(BoardType::Populate, 7, 5);
                    this->gamePlayVariables.boardTop[8] = this->getCell(BoardType::Populate, 8, 6);
                    break;

                case 7:
                    this->gamePlayVariables.boardTop[0] = this->getCell(BoardType::Populate, 0, 5);
                    this->gamePlayVariables.boardTop[1] = this->getCell(BoardType::Populate, 1, 4);
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 4);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 3);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 3);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 3);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 4);
                    this->gamePlayVariables.boardTop[7] = this->getCell(BoardType::Populate, 7, 4);
                    this->gamePlayVariables.boardTop[8] = this->getCell(BoardType::Populate, 8, 5);
                    break;

                case 6:
                    this->gamePlayVariables.boardTop[0] = this->getCell(BoardType::Populate, 0, 4);
                    this->gamePlayVariables.boardTop[1] = this->getCell(BoardType::Populate, 1, 3);
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 3);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 2);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 2);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 2);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 3);
                    this->gamePlayVariables.boardTop[7] = this->getCell(BoardType::Populate, 7, 3);
                    this->gamePlayVariables.boardTop[8] = this->getCell(BoardType::Populate, 8, 4);
                    break;

                case 5:
                    this->gamePlayVariables.boardTop[0] = this->getCell(BoardType::Populate, 0, 3);
                    this->gamePlayVariables.boardTop[1] = this->getCell(BoardType::Populate, 1, 2);
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 2);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 1);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 1);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 1);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 2);
                    this->gamePlayVariables.boardTop[7] = this->getCell(BoardType::Populate, 7, 2);
                    this->gamePlayVariables.boardTop[8] = this->getCell(BoardType::Populate, 8, 3);
                    break;

                case 4:
                    this->gamePlayVariables.boardTop[0] = this->getCell(BoardType::Populate, 0, 3);
                    this->gamePlayVariables.boardTop[1] = this->getCell(BoardType::Populate, 1, 1);
                    this->gamePlayVariables.boardTop[2] = this->getCell(BoardType::Populate, 2, 1);
                    this->gamePlayVariables.boardTop[3] = this->getCell(BoardType::Populate, 3, 0);
                    this->gamePlayVariables.boardTop[4] = this->getCell(BoardType::Populate, 4, 0);
                    this->gamePlayVariables.boardTop[5] = this->getCell(BoardType::Populate, 5, 0);
                    this->gamePlayVariables.boardTop[6] = this->getCell(BoardType::Populate, 6, 1);
                    this->gamePlayVariables.boardTop[7] = this->getCell(BoardType::Populate, 7, 1);
                    this->gamePlayVariables.boardTop[8] = this->getCell(BoardType::Populate, 8, 3);
                    break;

                default: break;

            }

            for (uint8_t y = 0; y < Constants::GridSize; y++) { 

                for (uint8_t x = 0; x < Constants::GridSize; x++) { 

                    if (this->gamePlayVariables.boardTop[x] != 0) {
                    
                        if (Constants::Hexic::Cell_yTop[x] - 1 != y  && Constants::Hexic::Cell_yBottom[x] > y && this->getCell(BoardType::Main, x, y) != Constants::InvalidCell) {
                            this->setCell(BoardType::Offset, x, y, 1);
                        }

                    }

                }
                
            }

            this->gamePlayVariables.populate--;
            this->gamePlayVariables.removePieces.pos = (this->gamePlayVariables.populate == 0 ? 0 : 1); 

        }

    }


    // Handle rendering ..

    this->renderBackground_Common();

    if (this->gamePlayVariables.levelUp.active) {

        PC::buttons.pollButtons();

        if (this->gamePlayVariables.levelUp.counter > 0 && (this->gamePlayVariables.removePieces.pos <= 0 || this->gamePlayVariables.removePieces.pos >= 16)) {
            this->persistFallingObjects_Hexic();
            this->prepareToClearBoard_Hexic();
            this->gamePlayVariables.levelUp.counter--;
            this->gamePlayVariables.removePieces.pos = 1;
        }
        else if (this->gamePlayVariables.levelUp.counter > 0 && this->gamePlayVariables.levelUp.counter != 9) {
            this->gamePlayVariables.removePieces.pos = this->gamePlayVariables.removePieces.pos + 3;
        }

    }

    this->renderScreen_Hexic();
    this->renderSidePanel_Hexic();
    if (!this->gamePlayVariables.removePieces.active && !this->gamePlayVariables.gameOver && this->gamePlayVariables.populate == 0) this->renderSelection_Hexic();


    // Game over ?

    if (this->gamePlayVariables.movesLeft == 0 || this->gamePlayVariables.gameOver) {

        this->gamePlayVariables.gameOver = true;
        this->gameEnd();

    }

    // Level up ?

    if (this->gamePlayVariables.levelUp.active) {

        this->levelUp_Hexic();

    }

    this->fadeInOut();

}
