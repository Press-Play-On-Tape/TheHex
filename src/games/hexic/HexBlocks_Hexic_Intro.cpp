#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::intro_Init_Hexic() {
    
    this->gameState = GameState::Intro_Hexic;
    this->selectedShape.setSelectedIndex(0);

    PD::adjustCharStep = -1;
    PC::buttons.pollButtons();
    this->fadeIn();
    
}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::intro_Hexic() {


    //  Handle movements ..

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_RIGHT)) {

        switch (this->selectedShape.getSelectedIndex()) {

            case 0 ... 2:
                this->selectedShape.setSelectedIndex(this->selectedShape.getSelectedIndex() + 1);
                break; 

            case 3:
                this->nextGameState = GameState::Game_Hexic_Init;
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
    PD::drawBitmap(86, 24, Images::Hexic);

    switch (this->selectedShape.getSelectedIndex()) {

        case 0:
            PD::setCursor(5, 67);
            PD::printf("Score points by rotating gems to");
            PD::setCursor(5, 80);
            PD::printf("create clusters of three gems of");
            PD::setCursor(6, 93);
            PD::printf("the same colour.  The three gems");
            PD::setCursor(20, 106);
            PD::printf("must be touching each other.");

            PD::drawBitmap(85, 140, Images::Bullet_Light);
            PD::drawBitmap(99, 140, Images::Bullet_Dark);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 1:
            PD::setCursor(19, 67);
            PD::printf("Create a flower - a coloured");
            PD::setCursor(16, 80);
            PD::printf("gem surrounded by six gems of");
            PD::setCursor(11, 93);
            PD::printf("another colour - to reveal the");
            PD::setCursor(42, 106);
            PD::printf("coveted Silver Gem!");

            PD::drawBitmap(85, 140, Images::Bullet_Dark);
            PD::drawBitmap(99, 140, Images::Bullet_Light);
            PD::drawBitmap(113, 140, Images::Bullet_Dark);
            PD::drawBitmap(127, 140, Images::Bullet_Dark);

            break;

        case 2:
            PD::setCursor(12, 67);
            PD::printf("Create a flower of Silver Gems");
            PD::setCursor(7, 80);
            PD::printf("to reveal a Black Pearl!  Make a");
            PD::setCursor(7, 93);
            PD::printf("flower from six Black Pearls to");
            PD::setCursor(47, 106);
            PD::printf("complete the game.");

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
