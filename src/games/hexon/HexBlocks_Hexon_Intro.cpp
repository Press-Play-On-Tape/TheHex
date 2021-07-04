#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::intro_Init_Hexon() {
    
    this->gameState = GameState::Intro_Hexon;
    this->selectedShape.setSelectedIndex(0);

    PD::adjustCharStep = -1;
    PC::buttons.pollButtons();
    this->fadeIn();

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::intro_Hexon() {


    //  Handle movements ..

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_RIGHT)) {

        switch (this->selectedShape.getSelectedIndex()) {

            case 0 ... 2:
                this->selectedShape.setSelectedIndex(this->selectedShape.getSelectedIndex() + 1);
                break; 

            case 3:
                this->nextGameState = GameState::Game_Hexon_Init;
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
    PD::drawBitmap(86, 24, Images::Hexon);

    switch (this->selectedShape.getSelectedIndex()) {

        case 0:
            PD::setCursor(14, 67);
            PD::printf("Place the shapes available in");
            PD::setCursor(20, 80);
            PD::printf("the right-hand toolbox onto");
            PD::setCursor(12, 93);
            PD::printf("the play field to create lines");
            PD::setCursor(45, 106);
            PD::printf("of four or more gems.");

            PD::drawBitmap(85, 140, Images::Bullet_Light);
            PD::drawBitmap(99, 140, Images::Bullet_Dark);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 1:
            PD::setCursor(10, 73);
            PD::printf("Lines can be either horizontal,");
            PD::setCursor(18, 86);
            PD::printf("diagonal or both with longer");
            PD::setCursor(23, 99);
            PD::printf("lines scoring more points!");

            PD::drawBitmap(85, 140, Images::Bullet_Dark);
            PD::drawBitmap(99, 140, Images::Bullet_Light);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 2:
            PD::setCursor(31, 67);
            PD::printf("Rotate the shapes in the");
            PD::setCursor(23, 80);
            PD::printf("toolbox using the B button.");
            PD::setCursor(14, 93);
            PD::printf("Toggle between the play field");
            PD::setCursor(10, 106);
            PD::printf("and toolbox using the B button.");

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

            break;
    }

    PD::adjustCharStep = 0;
    

    // Fade Out?

    this->fadeInOut();
    
}
