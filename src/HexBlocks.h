#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "entities/Entities.h"
#include "images/Images.h"
#include "shapes/Shapes.h"
#include "utils/Constants.h"
#include "utils/Structs.h"
#include "utils/GameCookie.h"
#include "utils/GamePlayVariables.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        TitleScreenVariables titleScreenVariables;
        GamePlayVariables gamePlayVariables;
        BackgroundVariables backgroundVariables;
        HighScoreVariables highScoreVariables;
        FadeVariables fadeVariables;
        Particle particles[PARTICLE_MAX];

        GameCookie *cookie;

        GameState gameState = GameState::Splash;
        GameState nextGameState = GameState::Splash;
        Mode mode = Mode::ShapeSelection;

        Audio::RAWFileSource *music;
        File mainThemeFile;

        SelectedShape selectedShape;
        SelectableShape shapes[4];

        #ifdef FPS
        long fpsCounter;
        long lastMillis;
        int fpsCount=0;
        #endif

    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void doSplashScreen();
        void doTitle_Init();
        void doTitle();


        // Hexon

        void intro_Init_Hexon();
        void intro_Hexon();
        void game_Init_Hexon();
        void game_Hexon();
        void renderSideBlocks_Hexon();
        void renderSelectedShape_Hexon();
        bool isValidMovement_Hexon(SelectedShape &selectedShape);
        bool isValidMovement_Hexon(SelectedShape &selectedShape, const int16_t xPlacement, const uint16_t yPlacement);
        bool isValidPlacement_Hexon(SelectedShape &selectedShape);
        bool isValidPlacement_Hexon(SelectedShape &selectedShape, const uint8_t xPlacement, const uint8_t yPlacement);
        void placeShape_Hexon();
        void removeWinningLines_Hexon();
        void populateShapes_Hexon();
        int8_t getCellSlash_Hexon(const uint8_t x, const uint8_t d);
        void setCellSlash_Hexon(const uint8_t x, const uint8_t d, const int8_t val);
        int8_t getCellBackslash_Hexon(const uint8_t x, const uint8_t d);
        void setCellBackslash_Hexon(const uint8_t x, const uint8_t d, const int8_t val);
        bool isValidMoveAvailable_Hexon();
        void drawHexagon(uint8_t width);
        void drawHexagonAlt(uint8_t width);
        void fadeIn();
        void fadeOut();
        void fadeInOut();


        // Hexer

        void intro_Init_Hexer();
        void intro_Hexer();
        void game_Init_Hexer();
        void game_Hexer();
        bool isValidMovement_Hexer(const int8_t xPlacement, const int8_t yPlacement);
        void renderSelection_Hexer();
        void renderSelection_Upright_Hexer();
        void renderSelection_Inverted_Hexer();
        void rotate_Clockwise_Hexer();
        void rotate_AntiClockwise_Hexer();
        void renderSidePanel_Hexer();
        void removeWinningSequences_Hexer(const uint8_t piece, uint8_t &matches);
        void removeWinningSequences_Recurse_Hexer(const uint8_t depth, const uint8_t x, const uint8_t y, const uint8_t color, uint8_t &matches);
        void getUpperLeftGridCoords_Hexer(uint8_t &x, uint8_t &y);
        void removeWinningSequence_AddPoints_Hexer();
        bool floodFill_Hexer();
        void renderScreen_Hexer();
        void persistFallingObjects_Hexer();
        void renderScreen_Rotate_XEven_YEven_Hexer();
        void renderScreen_Rotate_XOdd_YEven_Hexer();
        void renderScreen_Rotate_XEven_YOdd_Hexer();
        void renderScreen_Rotate_XOdd_YOdd_Hexer();


        // Hexic

        void intro_Init_Hexic();
        void intro_Hexic();
        void game_Init_Hexic();
        void game_Hexic();
        void rotate_Clockwise_Cluster_Hexic();
        void rotate_AntiClockwise_Cluster_Hexic();
        void rotate_Clockwise_Flower_Hexic(uint8_t xCell, uint8_t yCell);
        void rotate_AntiClockwise_Flower_Hexic(uint8_t xCell, uint8_t yCell);
        void renderSidePanel_Hexic();
        void removeWinningSequences_Hexic(uint8_t &matches);
        void removeWinningSequence_AddPoints_Hexic();
        bool floodFill_Hexic();
        void renderScreen_Hexic();
        void renderSelection_Hexic();
        void renderSelection_Left_EvenX_Hexic();
        void renderSelection_Left_OddX_Hexic();
        void renderSelection_Right_EvenX_Hexic();
        void renderSelection_Right_OddX_Hexic();
        bool isValidMovement_Hexic(const int8_t xPlacement, const int8_t yPlacement);
        void renderScreen_Rotate_Cluster_XEven_YEven_Hexic();
        void renderScreen_Rotate_Cluster_XOdd_YEven_Hexic();
        void renderScreen_Rotate_Cluster_XEven_YOdd_Hexic();
        void renderScreen_Rotate_Cluster_XOdd_YOdd_Hexic();
        void renderScreen_Rotate_Flower_XEven_Hexic(uint8_t xCell, uint8_t yCell);
        void renderScreen_Rotate_Flower_XOdd_Hexic(uint8_t xCell, uint8_t yCell);
        void getUpperLeftGridCoords_Hexic(uint8_t &x, uint8_t &y);
        void getUpperLeftGridCoords_Hexic(uint8_t xCursor, uint8_t yCursor, uint8_t &x, uint8_t &y);
        bool isSelectionFacingLeft_Hexic();
        bool isSelectionFacingLeft_Hexic(uint8_t x, uint8_t y);
        void persistFallingObjects_Hexic();
        uint8_t checkForCluster(BoardType boardType);
        bool selectionOnSilverGem(Direction prevDirection, uint8_t &xFound, uint8_t &yFound);
        bool selectionOnSilverGem(Direction prevDirection, uint8_t xCursor, uint8_t yCursor, uint8_t &xFound, uint8_t &yFound);
        void renderSelection_Flower_OddX_Hexic();
        void renderSelection_Flower_EvenX_Hexic();
        void populateBoard_Hexic();
        void prepareToClearBoard_Hexic();
        void levelUp_Hexic();


        // All games ..

        void printBoard();
        void renderScreen_Common();
        void renderBackground_Common();
        void highScore_Init();
        void highScore();
        void renderParticles();
        void renderFlowers();
        void launchParticles(const uint16_t x, const uint16_t y, const ExplosionSize explosionSize);
        int8_t getCell(const int8_t x, const int8_t y);
        int8_t getCell(const BoardType boardType, const int8_t x, const int8_t y);
        int8_t getCell(const BoardType boardType, const int8_t x, const int8_t y, const bool absolute);
        void setCell(const int8_t x, const int8_t y, const int8_t val);
        void setCell(const BoardType boardType, const int8_t x, const int8_t y, const int8_t val);
        void getCentreOfTile_Common(const uint8_t x, const uint8_t y, uint8_t &xCentre, uint8_t &yCentre);

        void gameEnd();
        void pause_Init();
        void pause();
        void playTheme(uint8_t trackNumber);
        void muteTheme();
        void playSoundEffect(SoundTheme soundEffect);
        uint8_t min(const uint8_t x, const uint8_t y);

};

