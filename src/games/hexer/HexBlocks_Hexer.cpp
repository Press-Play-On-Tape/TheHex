#include "../../HexBlocks.h"
#include "../../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::game_Init_Hexer() {
    
    this->gameState = GameState::Game_Hexer;

    this->gamePlayVariables.reset();

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            this->gamePlayVariables.board[x][y] = random(1, 7); 

        }

    }


    this->gamePlayVariables.x = 4;
    this->gamePlayVariables.y = 0;

    this->gamePlayVariables.board[0][0] = Constants::InvalidCell;
    this->gamePlayVariables.board[1][0] = Constants::InvalidCell;
    this->gamePlayVariables.board[7][0] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][0] = Constants::InvalidCell;
    this->gamePlayVariables.board[0][1] = Constants::InvalidCell;
    this->gamePlayVariables.board[7][1] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][1] = Constants::InvalidCell;
    this->gamePlayVariables.board[0][2] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][2] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][3] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][5] = Constants::InvalidCell;
    this->gamePlayVariables.board[0][6] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][6] = Constants::InvalidCell;
    this->gamePlayVariables.board[0][7] = Constants::InvalidCell;
    this->gamePlayVariables.board[7][7] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][7] = Constants::InvalidCell;
    this->gamePlayVariables.board[0][8] = Constants::InvalidCell;
    this->gamePlayVariables.board[1][8] = Constants::InvalidCell;
    this->gamePlayVariables.board[7][8] = Constants::InvalidCell;
    this->gamePlayVariables.board[8][8] = Constants::InvalidCell;

    this->fadeIn();
    PC::buttons.pollButtons();

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game_Hexer() {


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


    if (!this->gamePlayVariables.gameOver) {


        // Handle timer ..

        if (Utils::isFrameCount(30)) {

            this->gamePlayVariables.timer--;

            if (this->gamePlayVariables.timer == 0) {

                this->gamePlayVariables.gameOver = true;
                this->gamePlayVariables.gameOverCounter = 50;

            }

        }


        //  Handle movements ..

        if (PC::buttons.released(BTN_C)) {

            this->gameState = GameState::Pause_Hexer_Init;

        }

        if (PC::buttons.held(BTN_C, 16)) {

            this->nextGameState = GameState::Title_Init;
            this->fadeOut();

        }

        if (!this->gamePlayVariables.removePieces.active) {

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, REPEAT_VAL)) { 

                if (this->isValidMovement_Hexer(this->gamePlayVariables.x - 1, this->gamePlayVariables.y)) {

                    this->gamePlayVariables.x--;

                }

            }

            if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, REPEAT_VAL)) { 

                if (this->isValidMovement_Hexer(this->gamePlayVariables.x + 1, this->gamePlayVariables.y)) {

                    this->gamePlayVariables.x++;

                }

            }

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) { 

                if (this->isValidMovement_Hexer(this->gamePlayVariables.x, this->gamePlayVariables.y - 1)) {

                    this->gamePlayVariables.y--;

                }

            }

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) { 

                if (this->isValidMovement_Hexer(this->gamePlayVariables.x, this->gamePlayVariables.y + 1)) {

                    this->gamePlayVariables.y++;

                }

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->rotate_Clockwise_Hexer();
                this->gamePlayVariables.removePieces.active = true;
                this->gamePlayVariables.removePieces.state = 0;
                this->gamePlayVariables.removePieces.pos = Constants::RotatePiecesIndexStart;
                this->gamePlayVariables.removePieces.rotateDirection = RotateDirection::Clockwise;

            }

            if (PC::buttons.pressed(BTN_B)) {

                this->rotate_AntiClockwise_Hexer();
                this->gamePlayVariables.removePieces.active = true;
                this->gamePlayVariables.removePieces.state = 0;
                this->gamePlayVariables.removePieces.pos = Constants::RotatePiecesIndexStart;
                this->gamePlayVariables.removePieces.rotateDirection = RotateDirection::AntiClockwise;

            }

        }

    }


    // Remove pieces ..

    if (this->gamePlayVariables.removePieces.active) {

        uint8_t matches = 0;

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
                this->removeWinningSequences_Hexer(0, matches);

                // Did we have any 'flower' matches?

                if (this->gamePlayVariables.foundFlowers.anyActive()) {

                    this->gamePlayVariables.removePieces.state = 8; 
                    this->gamePlayVariables.scoreToAdd = this->gamePlayVariables.foundFlowers.numberActive() * 500;
                    this->gamePlayVariables.timer = this->min(this->gamePlayVariables.timer + 15, Constants::Hexer::TimerMax);
                    this->playSoundEffect(SoundTheme::LevelUp2);

                }
                else {

                    // Any other points?

                    this->gamePlayVariables.removePieces.state = this->gamePlayVariables.removePieces.state + (matches >= 3 ? 1 : 3); 
                    this->gamePlayVariables.scoreToAdd = (matches >= 3 ? matches * 2 : 0); 
                    if (matches >= 8) {
                        this->gamePlayVariables.timer = this->min(this->gamePlayVariables.timer + matches + 3, Constants::Hexer::TimerMax);
                        this->playSoundEffect(SoundTheme::LevelUp2);
                    }
                    else if (matches >= 3) {
                        this->playSoundEffect(SoundTheme::Bubble1);
                    }

                }

                break;

            case 2:

                this->removeWinningSequence_AddPoints_Hexer();
                this->gamePlayVariables.removePieces.delay = 2; 
                break;

            case 3:

                if (this->gamePlayVariables.removePieces.delay > 0) {
                    this->gamePlayVariables.removePieces.delay--;
                }
                else {
                    this->gamePlayVariables.removePieces.state++;
                }
                break;

            case 4:

                this->removeWinningSequences_Hexer(1, matches);
                this->gamePlayVariables.removePieces.state = this->gamePlayVariables.removePieces.state + (matches >= 3 ? 1 : 3); 
                this->gamePlayVariables.scoreToAdd = (matches >= 3 ? matches * 2 : 0); 
                if (matches >= 8) {
                    this->gamePlayVariables.timer = this->min(this->gamePlayVariables.timer + matches + 3, Constants::Hexer::TimerMax);
                    this->playSoundEffect(SoundTheme::LevelUp1);
                }
                else if (matches >= 3) {
                    this->playSoundEffect(SoundTheme::Bubble1);
                }
                break;

            case 5:

                this->removeWinningSequence_AddPoints_Hexer();
                this->gamePlayVariables.removePieces.delay = Constants::RemovingPiecesDelay;
                break;

            case 6:

                if (this->gamePlayVariables.removePieces.delay > 0) {
                    this->gamePlayVariables.removePieces.delay--;
                }
                else {
                    this->gamePlayVariables.removePieces.state++;
                }
                break;

            case 7:

                this->removeWinningSequences_Hexer(2, matches);
                this->gamePlayVariables.removePieces.state = this->gamePlayVariables.removePieces.state + (matches >= 3 ? 1 : 3); 
                this->gamePlayVariables.scoreToAdd = (matches >= 3 ? matches * 2 : 0); 
                if (matches >= 8) this->gamePlayVariables.timer = this->min(this->gamePlayVariables.timer + matches + 3, Constants::Hexer::TimerMax);
                if (matches >= 3) this->playSoundEffect(SoundTheme::Bubble1);
                break;

            case 8:

                this->removeWinningSequence_AddPoints_Hexer();
                this->gamePlayVariables.removePieces.delay = Constants::RemovingPiecesDelay;
                break;

            case 9:

                if (this->gamePlayVariables.removePieces.delay > 0) {
                    this->gamePlayVariables.removePieces.delay--;
                }
                else {
                    this->gamePlayVariables.removePieces.state++;
                }
                break;

            case 10:

                if (this->gamePlayVariables.removePieces.pos > 0 && this->gamePlayVariables.removePieces.pos < 9) {

                    this->gamePlayVariables.removePieces.pos = this->gamePlayVariables.removePieces.pos + Constants::DropSpeed;

                }
                else {

                    this->persistFallingObjects_Hexer();
                    this->gamePlayVariables.backupBoard(BoardType::Main);

                    if (!this->floodFill_Hexer()) { 
                        this->gamePlayVariables.removePieces.state++; 
                    }
                    else {
                        this->gamePlayVariables.removePieces.pos = 1;
                        this->gamePlayVariables.removePieces.state = 9;
                    }

                } 

                break;

            default: 

                this->gamePlayVariables.removePieces.active = false;
                this->gamePlayVariables.foundFlowers.reset();
                break;

        }

    }

    // Handle rendering ..

    this->renderBackground_Common();
    this->renderScreen_Hexer();
    this->renderSidePanel_Hexer();
    if (!this->gamePlayVariables.removePieces.active && !this->gamePlayVariables.gameOver) this->renderSelection_Hexer();


    // Game over ?

    if (this->gamePlayVariables.gameOver) {

        this->gameEnd();

    }

    this->fadeInOut();

}
