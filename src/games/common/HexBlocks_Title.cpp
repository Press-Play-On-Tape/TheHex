#include "../../HexBlocks.h"
#include "../../images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::doTitle_Init() { 

    this->gameState = GameState::Title;
    this->fadeIn();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::doTitle() { 

    PD::adjustCharStep = -1;
    this->renderBackground_Common();
    PD::drawBitmap(40, 10, Images::Title);
    PD::drawBitmap(148, 13, Images::Title_Sides);
    PD::drawBitmap(8, 94, Images::Title_Sides);

    PD::setColor(this->titleScreenVariables.mode == TitleScreenMode::Game ? 7 : 5, 14);
    PD::setCursor(16, 159);

    switch (this->cookie->gameInPlay) {

        case GameInPlay::Hexon:
            PD::printf("Hexon");
            break;

        case GameInPlay::Hexer:
            PD::printf("Hexer");
            break;

        case GameInPlay::Hexic:
            PD::printf("Hexic");
            break;

    }

    PD::drawBitmap(56, 159, this->titleScreenVariables.mode == TitleScreenMode::Game ? Images::UpDown_White : Images::UpDown_Grey);

    PD::setColor(this->titleScreenVariables.mode == TitleScreenMode::HighScores ? 7 : 5, 14);
    PD::setCursor(78, 159);
    PD::printf("High");
    PD::setCursor(111, 159);
    PD::printf("Scores");

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::drawBitmap(171, 159, this->titleScreenVariables.mode == TitleScreenMode::SoundEffects ? Images::Sound_Music_White: Images::Sound_Music_Grey);
            break;

        case SoundEffects::SFX:
            PD::drawBitmap(171, 159, this->titleScreenVariables.mode == TitleScreenMode::SoundEffects ? Images::Sound_SFX_White: Images::Sound_SFX_Grey);
            break;

        case SoundEffects::Both:
            PD::drawBitmap(171, 159, this->titleScreenVariables.mode == TitleScreenMode::SoundEffects? Images::Sound_Both_White: Images::Sound_Both_Grey);
            break;

        default:
            PD::drawBitmap(171, 159, this->titleScreenVariables.mode == TitleScreenMode::SoundEffects ? Images::Sound_None_White: Images::Sound_None_Grey);
            break;
    }

    PD::drawBitmap(202, 159, this->titleScreenVariables.mode == TitleScreenMode::SoundEffects ? Images::UpDown_White : Images::UpDown_Grey);


    if (PC::buttons.pressed(BTN_LEFT) && this->titleScreenVariables.mode != TitleScreenMode::Game) {

        this->titleScreenVariables.mode--;

    }

    if (PC::buttons.pressed(BTN_RIGHT) && this->titleScreenVariables.mode != TitleScreenMode::SoundEffects) {

        this->titleScreenVariables.mode++;

    }

    switch (this->titleScreenVariables.mode) {

        case TitleScreenMode::Game:

            if (PC::buttons.pressed(BTN_UP)) {

                this->cookie->gameInPlay--;
                this->cookie->saveCookie();

            }

            if (PC::buttons.pressed(BTN_DOWN)) {

                this->cookie->gameInPlay++;
                this->cookie->saveCookie();

            }
            
            if ((PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) && this->fadeVariables.direction == FadeDirection::None) {

                switch (this->cookie->gameInPlay) {

                    case GameInPlay::Hexon:
                        this->nextGameState = GameState::Intro_Hexon_Init;
                        break;

                    case GameInPlay::Hexer:
                        this->nextGameState = GameState::Intro_Hexer_Init;
                        break;

                    case GameInPlay::Hexic:
                        this->nextGameState = GameState::Intro_Hexic_Init;
                        break;

                }

                this->fadeOut();

            }

            break;

        case TitleScreenMode::HighScores:

            if ((PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

                this->cookie->setScoreIndex(NO_SCORE);
                this->gameState = GameState::HighScore_Init;

            }

            break;

        case TitleScreenMode::SoundEffects:

            if (PC::buttons.pressed(BTN_UP)) {

                this->cookie->sfx--;
                this->cookie->saveCookie();

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    this->playTheme(this->cookie->track);

                }

            }

            if (PC::buttons.pressed(BTN_DOWN)) {

                this->cookie->sfx++;
                this->cookie->saveCookie();

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    this->playTheme(this->cookie->track);
                    
                }
                
            }

            break;

    }


    // Draw fade out?

    this->fadeInOut();
   
}
