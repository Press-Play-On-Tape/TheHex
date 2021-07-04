#pragma once

#include "Pokitto.h"
#include "../utils/Constants.h"
#include "../shapes/Shapes.h"

class Base {

    private: 
    
        uint8_t index = 0;
        uint8_t color = 0;

    public:

        uint8_t getIndex()                  { return this->index; }
        uint8_t getColor()                  { return this->color; }

        void setIndex(uint8_t val)          { this->index = val; }
        void setColor(uint8_t val)          { this->color = val; }

};