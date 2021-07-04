#pragma once

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};

struct FadeVariables {

    FadeDirection direction = FadeDirection::None;
    uint8_t size = 0;

};

struct TitleScreenVariables {

    TitleScreenMode mode = TitleScreenMode::Game;

};

struct RemovePieces {

    bool active = false;
    uint8_t state = 0;          
    uint8_t delay = 0;
    int8_t pos = 0;
    RotateDirection rotateDirection = RotateDirection::Clockwise;

    void reset() {

        this->active = false;
        this->state = 0;          
        this->delay = 0;
        this->pos = 0;
        this->rotateDirection = RotateDirection::Clockwise;

    }

};

struct BackgroundVariables {

    int16_t titleOffsetTop = 0;
    int16_t titleOffsetBottom = -240;

};

struct HighScoreVariables {

    uint8_t scoreGameBoard[16][16];

};


struct FoundFlower {

    bool active = false;
    uint8_t x;
    uint8_t y;
    uint8_t color;

    void reset() {

        active = false;

    }

};

struct FoundFlowers {

    FoundFlower flower[Constants::NumberOfPossibleFlowers];

    uint8_t nextAvailable() {

        for (uint8_t i = 0; i < Constants::NumberOfPossibleFlowers; i++) {

            if (!this->flower[i].active) {

                return i;

            }

        }
        return 0;

    }

    void reset() {

        for (uint8_t i = 0; i < Constants::NumberOfPossibleFlowers; i++) {

            this->flower[i].reset();

        }
        
    }

    bool anyActive() {

        return this->flower[0].active;
        
    }

    uint8_t numberActive() {

        uint8_t count = 0;

        for (uint8_t i = 0; i < Constants::NumberOfPossibleFlowers; i++) {

            if (this->flower[i].active) count++;

        }

        return count;

    }

};

struct FlowerSelected {

    SelectionMode mode = SelectionMode::None;
    Direction prevDirection = Direction::None;
    uint8_t x = 0;
    uint8_t y = 0;

    void reset() {

        this->mode = SelectionMode::None;
        this->prevDirection = Direction::None;
        this->x = 0;
        this->y = 0;

    }

};

struct LevelUp {

    bool active = false;
    bool bonusAdded = false;
    uint8_t counter = 0;

    void reset() {

        this->active = false;
        this->bonusAdded = false;
        this->counter = 0;
        
    }

};