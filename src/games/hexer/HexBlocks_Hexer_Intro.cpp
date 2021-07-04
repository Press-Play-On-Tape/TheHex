#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::intro_Init_Hexer() {
    
    this->gameState = GameState::Intro_Hexer;
    this->selectedShape.setSelectedIndex(0);

    PD::adjustCharStep = -1;
    PC::buttons.pollButtons();
    this->fadeIn();
}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::intro_Hexer() {


    //  Handle movements ..

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_RIGHT)) {

        switch (this->selectedShape.getSelectedIndex()) {

            case 0 ... 2:
                this->selectedShape.setSelectedIndex(this->selectedShape.getSelectedIndex() + 1);
                break; 

            case 3:
                this->nextGameState = GameState::Game_Hexer_Init;
                this->fadeOut();
                PD::adjustCharStep = 0;
                break;

        }

    }

    if (PC::buttons.pressed(BTN_LEFT)) {

        switch (this->selectedShape.getSelectedIndex()) {

            case 1 ... 3:
                this->selectedShape.setSelectedIndex(this->selectedShape.getSelectedIndex() - 1);
                break; 

        }

    }

    if (PC::buttons.held(BTN_C, 16)) {

        this->nextGameState = GameState::Title_Init;
        this->fadeOut();

    }


    // Handle rendering ..

    this->renderBackground_Common();

    PD::adjustCharStep = -1;
    PD::setColor(5, 14);
    PD::drawFastHLine(38, 37, 40);
    PD::drawFastHLine(142, 37, 40);
    PD::setColor(6, 14);
    PD::drawBitmap(86, 24, Images::Hexer);

    switch (this->selectedShape.getSelectedIndex()) {

        case 0:
            PD::setCursor(17, 67);
            PD::printf("You have two minutes to score");
            PD::setCursor(16, 80);
            PD::printf("as many points as possible by");
            PD::setCursor(13, 93);
            PD::printf("rotating the gems highlighted");
            PD::setCursor(6, 106);
            PD::printf("by your cursor to match colours.");

            PD::drawBitmap(85, 140, Images::Bullet_Light);
            PD::drawBitmap(99, 140, Images::Bullet_Dark);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 1:
            PD::setCursor(17, 73);
            PD::printf("Create a flower - a coloured");
            PD::setCursor(16, 86);
            PD::printf("gem surrounded by six gems of");
            PD::setCursor(12, 99);
            PD::printf("another colour - to score big!");

            PD::drawBitmap(85, 140, Images::Bullet_Dark);
            PD::drawBitmap(99, 140, Images::Bullet_Light);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 2:
            PD::setCursor(21, 67);
            PD::printf("Clearing eight or more of a");
            PD::setCursor(6, 80);
            PD::printf("single colour in a move will add");
            PD::setCursor(8, 93);
            PD::printf("time back to the clock allowing");
            PD::setCursor(32, 106);
            PD::printf("you to continue scoring.");

            PD::drawBitmap(85, 140, Images::Bullet_Dark);
            PD::drawBitmap(99, 140, Images::Bullet_Dark);
            PD::drawBitmap(113, 140, Images::Bullet_Light);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 3:
            PD::setCursor(19, 67);
            PD::printf("Press the C button to change");
            PD::setCursor(15, 80);
            PD::printf("tapes. Hold down the C button");
            PD::setCursor(30, 93);
            PD::printf("to quit the game and exit");
            PD::setCursor(42, 106);
            PD::printf("back to the main menu.");

            PD::drawBitmap(85, 140, Images::Bullet_Dark);
            PD::drawBitmap(99, 140, Images::Bullet_Dark);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Light);

    }

    PD::adjustCharStep = 0;


    // Fade Out?

    this->fadeInOut();

}
