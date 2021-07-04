#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::game_Init_Hexon() {
    
    this->gameState = GameState::Game_Hexon;
    this->gamePlayVariables.reset();

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            this->gamePlayVariables.board[x][y] = 0;

        }

    }


    // Mark invalid cells ..

    this->gamePlayVariables.board[0][0] = 9;
    this->gamePlayVariables.board[1][0] = 9;
    this->gamePlayVariables.board[7][0] = 9;
    this->gamePlayVariables.board[8][0] = 9;

    this->gamePlayVariables.board[0][1] = 9;
    this->gamePlayVariables.board[7][1] = 9;
    this->gamePlayVariables.board[8][1] = 9;

    this->gamePlayVariables.board[0][2] = 9;
    this->gamePlayVariables.board[8][2] = 9;

    this->gamePlayVariables.board[8][3] = 9;
    this->gamePlayVariables.board[8][5] = 9;

    this->gamePlayVariables.board[0][6] = 9;
    this->gamePlayVariables.board[8][6] = 9;

    this->gamePlayVariables.board[0][7] = 9;
    this->gamePlayVariables.board[7][7] = 9;
    this->gamePlayVariables.board[8][7] = 9;

    this->gamePlayVariables.board[0][8] = 9;
    this->gamePlayVariables.board[1][8] = 9;
    this->gamePlayVariables.board[7][8] = 9;
    this->gamePlayVariables.board[8][8] = 9;

    this->populateShapes_Hexon();

    this->selectedShape.setSelectedIndex(0);
    this->selectedShape.setShape(this->shapes[0]);
    this->mode = Mode::ShapeSelection;

    this->gamePlayVariables.x = 2;
    this->gamePlayVariables.y = 0;

    PC::buttons.pollButtons();
    this->fadeIn();
}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game_Hexon() {


    // Handle score ..

    if (this->gamePlayVariables.scoreToAdd > 0) {

        this->gamePlayVariables.scoreToAdd--;
        this->gamePlayVariables.score++;

    }


    //  Handle movements ..

    if (!this->gamePlayVariables.gameOver) {

        if (PC::buttons.released(BTN_C)) {

            this->gameState = GameState::Pause_Hexon_Init;

        }

        if (PC::buttons.held(BTN_C, 16)) {

            this->nextGameState = GameState::Title_Init;
            this->fadeOut();

        }

        switch (this->mode) {

            case Mode::ShapeSelection:

                if (PC::buttons.pressed(BTN_UP)) { 

                    if (this->selectedShape.getSelectedIndex() > 0) {

                        if (this->shapes[this->selectedShape.getSelectedIndex() - 1].getIndex() != 0) {

                            this->selectedShape.setSelectedIndex(this->selectedShape.getSelectedIndex() - 1);
                            this->selectedShape.setShape(this->shapes[this->selectedShape.getSelectedIndex()]);

                        }

                    }

                }

                if (PC::buttons.pressed(BTN_DOWN)) { 

                    if (this->selectedShape.getSelectedIndex() < Constants::Hexon::noOfSideShapes - 1) {

                        if (this->shapes[this->selectedShape.getSelectedIndex() + 1].getIndex() != 0) {

                            this->selectedShape.setSelectedIndex(this->selectedShape.getSelectedIndex() + 1);
                            this->selectedShape.setShape(this->shapes[this->selectedShape.getSelectedIndex()]);

                        }

                    }

                }

                if (PC::buttons.pressed(BTN_A)) { 

                    this->mode = Mode::ShapePlacement;
                    this->gamePlayVariables.x = 4 - (this->selectedShape.getWidth() / 2);
                    this->gamePlayVariables.y = 4 - (this->selectedShape.getHeight() / 2);

                }

                if (PC::buttons.pressed(BTN_B)) { 

                    this->shapes[this->selectedShape.getSelectedIndex()].rotate();
                    this->selectedShape.setShape(this->shapes[this->selectedShape.getSelectedIndex()]);

                }

                break;

            case Mode::ShapePlacement:

                if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, REPEAT_VAL)) { 

                    if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x - 1, this->gamePlayVariables.y)) {

                        this->gamePlayVariables.x--;

                    }

                }

                if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, REPEAT_VAL)) { 

                    if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x + 1, this->gamePlayVariables.y)) {

                        this->gamePlayVariables.x++;

                    }

                }

                if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) { 

                    if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x, this->gamePlayVariables.y - 1)) {

                        this->gamePlayVariables.y--;

                    }

                    else if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x - 1, this->gamePlayVariables.y - 1)) {

                        this->gamePlayVariables.x--;
                        this->gamePlayVariables.y--;

                    }

                    else if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x + 1, this->gamePlayVariables.y - 1)) {

                        this->gamePlayVariables.x++;
                        this->gamePlayVariables.y--;

                    }                

                }

                if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) { 

                    if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x, this->gamePlayVariables.y + 1)) {

                        this->gamePlayVariables.y++;

                    }

                    else if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x - 1, this->gamePlayVariables.y + 1)) {

                        this->gamePlayVariables.x--;
                        this->gamePlayVariables.y++;

                    }

                    else if (this->isValidMovement_Hexon(this->selectedShape, this->gamePlayVariables.x + 1, this->gamePlayVariables.y + 1)) {

                        this->gamePlayVariables.x++;
                        this->gamePlayVariables.y++;

                    }

                }

                if (PC::buttons.pressed(BTN_A) && this->isValidPlacement_Hexon(this->selectedShape)) { 

                    this->placeShape_Hexon();
                    removeWinningLines_Hexon();

                    this->gamePlayVariables.gameOverCounter = 50;
                    this->gamePlayVariables.gameOver = !this->isValidMoveAvailable_Hexon();
                    PC::buttons.pollButtons();
                    
                }

                if (PC::buttons.pressed(BTN_B)) { 

                    this->mode = Mode::ShapeSelection;
                    
                }

                break;

        }

    }

    // Handle rendering ..

    this->renderBackground_Common();
    this->renderScreen_Common();
    this->renderSideBlocks_Hexon();
    
    switch (this->mode) {

        case Mode::ShapePlacement:
            this->renderSelectedShape_Hexon();
            break;

        default:
            break;

    }


    // Game over ?

    if (this->gamePlayVariables.gameOver) {

        this->gameEnd();

    }

    this->fadeInOut();

}
