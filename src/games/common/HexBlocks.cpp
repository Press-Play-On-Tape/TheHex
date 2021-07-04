#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "../../utils/Constants.h"
#include "../../images/Images.h"

void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->gameState) {

        case GameState::Splash:
            this->doSplashScreen(); 
            break;

        case GameState::Title_Init:
            this->doTitle_Init(); 
            this->doTitle(); 
            break;

        case GameState::Title:
            this->doTitle(); 
            break;

        case GameState::Intro_Hexon_Init:
            this->intro_Init_Hexon();
            this->intro_Hexon();
            break;

        case GameState::Intro_Hexon:
            this->intro_Hexon();
            break;

        case GameState::Game_Hexon_Init:
            this->game_Init_Hexon();
            this->game_Hexon();
            break;

        case GameState::Game_Hexon:
            this->game_Hexon();
            break;

        case GameState::Intro_Hexer_Init:
            this->intro_Init_Hexer();
            this->intro_Hexer();
            break;

        case GameState::Intro_Hexer:
            this->intro_Hexer();
            break;

        case GameState::Game_Hexer_Init:
            this->game_Init_Hexer();
            this->game_Hexer();
            break;

        case GameState::Game_Hexer:
            this->game_Hexer();
            break;
 
        case GameState::Intro_Hexic_Init:
            this->intro_Init_Hexic();
            this->intro_Hexic();
            break;

        case GameState::Intro_Hexic:
            this->intro_Hexic();
            break;

        case GameState::Game_Hexic_Init:
            this->game_Init_Hexic();
            this->game_Hexic();
            break;

        case GameState::Game_Hexic:
            this->game_Hexic();
            break;
 
        case GameState::HighScore_Init:
            this->highScore_Init();
            break;

        case GameState::HighScore:
            this->highScore();
            break;

        case GameState::Pause_Hexon_Init:
        case GameState::Pause_Hexer_Init:
        case GameState::Pause_Hexic_Init:
            this->pause_Init();
            break;

        case GameState::Pause_Hexon:
        case GameState::Pause_Hexer:
        case GameState::Pause_Hexic:
            this->pause();
            break;

    }

    this->renderParticles();


    // Render flowers if necessary ..

    switch (this->gameState) {

        case GameState::Game_Hexer:
            this->renderFlowers();
            break;

        default: break;

    }


    #ifdef FPS

        fpsCounter++;
        PD::setCursor(0, 164);
        PD::print("FPS:");
        PD::print(fpsCount);

        if (PC::getTime() >= lastMillis + 1000) {
            lastMillis = PC::getTime();
            fpsCount = fpsCounter;
            fpsCounter = 0;
        }
    #endif

}

