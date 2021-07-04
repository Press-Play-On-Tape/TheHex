#pragma once

#include "Pokitto.h"
#include "Base.h"
#include "../utils/Constants.h"
#include "../shapes/Shapes.h"

class SelectableShape : public Base {

    private: 
    
        uint8_t minRange = 0;
        uint8_t maxRange = 0;

    public:

        uint8_t getMinRange()                   { return this->minRange; }
        uint8_t getMaxRange()                   { return this->maxRange; }

        void setMinRange(uint8_t val)           { this->minRange = val; }
        void setMaxRange(uint8_t val)           { this->maxRange = val; }

    public:

        void rotate() {

            if (this->minRange == this->maxRange) return;

            if (this->getIndex() < this->maxRange) {

                this->setIndex(this->getIndex() + 1);

            }
            else {

                this->setIndex(this->minRange);

            }

            this->setMinRange(Shapes::RotMin[this->getIndex()]);
            this->setMaxRange(Shapes::RotMax[this->getIndex()]);

        }

};