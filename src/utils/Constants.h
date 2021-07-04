#pragma once


// - Debug ------------------------------

#define DEBUG
#define SOUNDS
#define _FPS

#define COOKIE_INITIALISED 35
#define REPEAT_VAL 2
#define REPEAT_VAL_SLOW 2

#define PARTICLE_MAX 200
#define NO_SCORE 255
#define PART_SIZE 12

namespace Constants {

    constexpr uint8_t fallingYOffset[] =   { 2, 3, 5, 7, 9, 10, 12, 14, 15, 16, 16, 16, 16 };

    constexpr uint8_t RemovingPiecesDelay = 4;
    constexpr uint8_t DropSpeed = 3;
    constexpr uint8_t NumberOfPossibleFlowers = 6;
    constexpr uint8_t RotatePiecesIndexStart = 9;
    constexpr uint8_t RandomColorMax = 7;

    constexpr uint8_t Background_xBurgundy[] = { 25, 39, 53, 81, 67, 95, 53,   172, 158, 186,      172, 130, 158, 186, 144, 116,  166, 194,  67 };
    constexpr uint8_t Background_yBurgundy[] = { 28,  7, 28, 28, 49, 49, 70,     7,   28, 28,       70,  91,  91,  91, 112, 112,  141, 141,  141};

    constexpr uint8_t Background_xBlue[] = { 41, 176, 41, 121,   0, 121 };
    constexpr uint8_t Background_yBlue[] = { 8,    8, 61,  61, 138, 115 };

    constexpr uint8_t Cell_Count[] = { 5, 6, 7, 8, 9, 8, 7, 6, 5 };
    constexpr uint8_t Cell_Min_X[] = { 2, 1, 1, 0, 0, 0, 1, 1, 2 };
    constexpr uint8_t Cell_Max_X[] = { 6, 6, 7, 7, 8, 7, 7, 6, 6 };
    constexpr uint8_t Cell_xPos[] = { 42, 33, 24, 15, 6, 15, 24, 33, 42 };
    constexpr uint8_t Cell_yPos[] = { 15, 31, 47, 63, 79, 95, 111, 127, 143 };

    constexpr uint8_t InvalidCell = 127;
    constexpr uint8_t GridSize = 9;

    namespace Hexon {

        constexpr uint8_t noOfSideShapes = 4;
        constexpr uint16_t Scores[] = { 0, 0, 0, 0, 10, 20, 50, 100, 200, 500 };
                                    //  0                             1                          2
                                    //  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0
        constexpr uint8_t noOfHexes[] = { 5, 4, 4, 3, 3, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 3, 4, 4, 5, };

        constexpr uint8_t slash_X[81] =     { 127, 127, 0, 0, 1, 1, 2, 127, 127,
                                            127, 0, 1, 1, 2, 2, 3, 127, 127,
                                            127, 1, 1, 2, 2, 3, 3, 4, 127,
                                            1, 2, 2, 3, 3, 4, 4, 5, 127,
                                            2, 2, 3, 3, 4, 4, 5, 5, 6,
                                            3, 3, 4, 4, 5, 5, 6, 6, 127,
                                            127, 4, 4, 5, 5, 6, 6, 7, 127, 
                                            127, 5, 5, 6, 6, 7, 7, 127, 127,
                                            127, 127, 6, 6, 7, 7, 8, 127, 127,
                                            };

        constexpr uint8_t slash_Y[81] =     { 127, 127, 4, 3, 2, 1, 0, 127, 127,
                                            127, 5, 4, 3, 2, 1, 0, 127, 127,
                                            127, 6, 5, 4, 3, 2, 1, 0, 127,
                                            7, 6, 5, 4, 3, 2, 1, 0, 127,
                                            8, 7, 6, 5, 4, 3, 2, 1, 0,
                                            8, 7, 6, 5, 4, 3, 2, 1, 127,
                                            127, 8, 7, 6, 5, 4, 3, 2, 127, 
                                            127, 8, 7, 6, 5, 4, 3, 127, 127, 
                                            127, 127, 8, 7, 6, 5, 4, 127, 127,
                                            };

        constexpr uint8_t backslash_X[81] = { 127, 127, 6, 6, 7, 7, 8, 127, 127,
                                            127, 5, 5, 6, 6, 7, 7, 127, 127,
                                            127, 4, 4, 5, 5, 6, 6, 7, 127,
                                            3, 3, 4, 4, 5, 5, 6, 6, 127,
                                            2, 2, 3, 3, 4, 4, 5, 5, 6, 
                                            1, 2, 2, 3, 3, 4, 4, 5, 127,
                                            127, 1, 1, 2, 2, 3, 3, 4, 127, 
                                            127, 0, 1, 1, 2, 2, 3, 127, 127, 
                                            127, 127, 0, 0, 1, 1, 2, 127, 127,
                                            };

        constexpr uint8_t backslash_Y[81] = { 127, 127, 0, 1, 2, 3, 4, 127, 127,
                                            127, 0, 1, 2, 3, 4, 5, 127, 127, 
                                            127, 0, 1, 2, 3, 4, 5, 6, 127,
                                            0, 1, 2, 3, 4, 5, 6, 7, 127,
                                            0, 1, 2, 3, 4, 5, 6, 7, 8,                                           
                                            1, 2, 3, 4, 5, 6, 7, 8, 127,
                                            127, 2, 3, 4, 5, 6, 7, 8, 127, 
                                            127, 3, 4, 5, 6, 7, 8, 127, 127, 
                                            127, 127, 4, 5, 6, 7, 8, 127, 127,
                                            };

    }

    namespace Hexer {

        constexpr uint8_t TimerMax = 120;

    }

    namespace Hexic {

        constexpr uint8_t Cell_yPos[] =     { 8, 26, 44, 62, 80, 98, 116, 134, 152 };
        constexpr uint8_t Cell_yTop[] =     { 2, 1, 1, 0, 0, 0, 1, 1, 2 };            
        constexpr uint8_t Cell_yBottom[] =  { 6, 6, 7, 7, 8, 7, 7, 6, 6 };            
        constexpr uint8_t Cell_Left = 8;

        constexpr int8_t ClusterY_Even[] =   { -1, -1, -1, 0, 0, 1, 1,  0,  0, -1, -1, -1 };
        constexpr int8_t ClusterY_Odd[] =    { -1,  0,  0, 1, 1, 1, 1,  1,  1,  0,  0, -1 };
        constexpr int8_t ClusterX_Common[] = {  0,  1,  1, 1, 1, 0, 0, -1, -1, -1, -1,  0 };

        constexpr uint8_t BlackPearl = 7;
        constexpr uint8_t SilverGem = 8;
        constexpr uint8_t FlowerScore = 100;

    }

}

enum class GameInPlay : uint8_t {
    Hexon,
    Hexer,
    Hexic
};

inline GameInPlay &operator++(GameInPlay &c ) {
    c = static_cast<GameInPlay>( (static_cast<uint8_t>(c) + 1) % 3 );
    return c;
}

inline GameInPlay operator++(GameInPlay &c, int ) {
    GameInPlay result = c;
    ++c;
    return result;
}

inline GameInPlay &operator--(GameInPlay &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<GameInPlay>( (static_cast<uint8_t>(c) - 1) % 3 );
    }
    else {
        c = static_cast<GameInPlay>( 2 );
    }
    return c;
}

inline GameInPlay operator--(GameInPlay &c, int ) {
    GameInPlay result = c;
    --c;
    return result;
}

enum class GameState : uint8_t {
    Splash_Init, // 0
    Splash,
    Title_Init,
    Title,
    Intro_Hexon_Init,
    Intro_Hexon,
    Game_Hexon_Init,
    Game_Hexon,
    Intro_Hexer_Init,
    Intro_Hexer,
    Game_Hexer_Init,
    Game_Hexer,
    Intro_Hexic_Init,
    Intro_Hexic,
    Game_Hexic_Init,
    Game_Hexic,
    HighScore_Init,
    HighScore,
    Pause_Hexon_Init,
    Pause_Hexon,
    Pause_Hexer_Init,
    Pause_Hexer,
    Pause_Hexic_Init,
    Pause_Hexic,
};

enum class Mode : uint8_t {
    ShapePlacement,
    ShapeSelection
};

enum class ParticleType : uint8_t {
    Zero,
    One,
    Two,
    Score,
    Clear,
    ClearStar,
};

enum class ExplosionSize : uint8_t {
    Medium,
    Large,
    None
};

enum class SoundTheme : uint8_t {
    Bubble1,
    LevelUp1,
    LevelUp2
};

enum class RotateDirection : uint8_t {
    Clockwise,
    AntiClockwise,
};

enum class BoardType : uint8_t {
    Main,
    Backup,
    Offset,
    Populate
};

enum class Direction : uint8_t {
    None,
    Left,
    Right,
    Up,
    Down,
};

enum class FadeDirection : uint8_t {
    None,
    In,
    Out,
};

enum class SelectionMode : uint8_t {
    None,
    FlowerTouched,
    FlowerSelected
};


// ------------------------------------------------------------------------

enum class TitleScreenMode : uint8_t {
    Game,
    HighScores,
    SoundEffects
};

inline TitleScreenMode operator++( TitleScreenMode & c ) {

    c = static_cast<TitleScreenMode>( static_cast<uint8_t>(c) + 1 );
    return c;

}

inline TitleScreenMode operator++( TitleScreenMode & c, int ) {

    TitleScreenMode result = c;
    ++c;
    return result;

}

inline TitleScreenMode operator--( TitleScreenMode & c ) {
 
    c = static_cast<TitleScreenMode>( static_cast<uint8_t>(c) - 1 );
    return c;

}

inline TitleScreenMode operator--( TitleScreenMode & c, int ) {

    TitleScreenMode result = c;
    --c;
    return result;

}

// ------------------------------------------------------------------------

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
    --c;
    return result;
}
