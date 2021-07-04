#pragma once

#include "Pokitto.h"
#include "Base.h"
#include "../utils/Constants.h"
#include "../shapes/Shapes.h"

class SelectedShape : public Base {

    private: 
    
        uint8_t width = 0;
        uint8_t height = 0;
        uint8_t selectedIndex = 0;

    public:

        uint8_t getWidth()                          { return this->width; }
        uint8_t getHeight()                         { return this->height; }
        uint8_t getSelectedIndex()                  { return this->selectedIndex; }

        void setSelectedIndex(uint8_t val)          { this->selectedIndex = val; }

    public:

        void setShape(SelectableShape val) { 
            
            this->setIndex(val.getIndex()); 
            this->setColor(val.getColor()); 

            this->width = Shapes::ShapeReferences[val.getIndex()][0];
            this->height = Shapes::ShapeReferences[val.getIndex()][1]; 
        }

        uint8_t getCell(uint8_t x, uint8_t y) {
            
            return Shapes::ShapeReferences[this->getIndex()][2 + ((y * this->width) + x)] * this->getColor();

        }

        bool isUpperLeftCellBlank() {
            
            return this->getCell(0, 0) == 0;

        }

        bool isUpperLeftCellPlusOneBlank() {
            
            return this->getCell(this->width > 1 ? 1 : 0, 0) == 0;

        }

        bool isUpperRightCellBlank() {
            
            return this->getCell(this->width - 1, 0) == 0;

        }

        bool isUpperRightCellPlusOneBlank() {
            
            return this->getCell(this->width > 2 ? this->width - 2 : this->width - 1, 0) == 0;

        }

        bool isLowerLeftCellBlank() {
            
            return this->getCell(0, this->height - 1) == 0;

        }

        bool isLowerLeftCellPlusOneBlank() {
            
            return this->getCell(this->width > 1 ? 1 : 0, this->height - 1) == 0;

        }

        bool isLowerRightCellBlank() {
            
            return this->getCell(this->width - 1, this->height - 1) == 0;

        }

        bool isLowerRightCellPlusOneBlank() {
            
            return this->getCell(this->width > 2 ? this->width - 2 : this->width - 1, this->height - 1) == 0;

        }

};