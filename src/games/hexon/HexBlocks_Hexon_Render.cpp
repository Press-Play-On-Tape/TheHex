#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../images/Images.h"
#include "../../entities/Entities.h"


void Game::renderSideBlocks_Hexon() {    

    uint8_t yPosition = 26;

    PD::setColor(5);
    PD::drawLine(171, 0, 171, 188);
    PD::setColor(0);
    PD::fillRect(172, 0, 50, 188);



    // Render Score ..

    PD::setColor(6);
    PD::setCursor(176, 1);
    PD::print("Score");

    PD::setCursor(176, 12);
    if (this->gamePlayVariables.score < 10000) PD::print("0");
    if (this->gamePlayVariables.score < 1000)  PD::print("0");
    if (this->gamePlayVariables.score < 100)   PD::print("0");
    if (this->gamePlayVariables.score < 10)    PD::print("0");
    PD::print(this->gamePlayVariables.score);

    for (uint8_t i = 0; i < Constants::Hexon::noOfSideShapes; i++) {

        if (this->shapes[i].getIndex() > 0) {

            SelectedShape shape;
            shape.setShape(shapes[i]);

            uint8_t leftPos = 193 - (Shapes::shapeWidths[shape.getIndex()] / 2);

            for (uint8_t y = 0; y < shape.getHeight(); y++) {

                for (uint8_t x = 0; x < shape.getWidth(); x++) {

                    uint8_t value = shape.getCell(x, y);


                    // Highlight selection?

                    if (value != 0) {
                            
                        if (i == this->selectedShape.getSelectedIndex() && !this->gamePlayVariables.gameOver) {

                            if (this->mode == Mode::ShapeSelection && Utils::getFrameCountHalf(32)) {

                                PD::drawBitmap(leftPos + (x * 12) + (y % 2 == 0 ? 0 : 6), yPosition, Images::Hex_Small[value]);
                                PD::drawBitmap(leftPos + (x * 12) + (y % 2 == 0 ? 0 : 6), yPosition, Images::Hex_Small_Highlight);

                            }
                            else {

                                if (this->mode == Mode::ShapeSelection) {

                                    PD::drawBitmap(leftPos + (x * 12) + (y % 2 == 0 ? 0 : 6), yPosition, Images::Hex_Small[value]);

                                }

                                PD::drawBitmap(leftPos + (x * 12) + (y % 2 == 0 ? 0 : 6), yPosition, Images::Hex_Small_Lowlight);
                            }

                        }
                        else {

                            PD::drawBitmap(leftPos + (x * 12) + (y % 2 == 0 ? 0 : 6), yPosition, Images::Hex_Small[value]);
                            PD::drawBitmap(leftPos + (x * 12) + (y % 2 == 0 ? 0 : 6), yPosition, Images::Hex_Small_Lowlight);

                        }

                    }
                                        
                }

                yPosition = yPosition + 10;

            }

            yPosition = yPosition + 9;
            
        }

    }

}


void Game::renderSelectedShape_Hexon() {

    int16_t xPosition = 0;
    int16_t yPosition = 0;
    bool addInitNine = this->gamePlayVariables.y % 2 == 1;
    bool addNine = false;
                
    xPosition = 6 + (this->gamePlayVariables.x * 18);
    yPosition = Constants::Cell_yPos[this->gamePlayVariables.y];

    for (uint8_t y = 0; y < this->selectedShape.getHeight(); y++) {

        for (uint8_t x = 0; x < this->selectedShape.getWidth(); x++) {

            uint8_t value = this->selectedShape.getCell(x, y);

            if (value > 0 && x >= 0 && y >= 0) {

               PD::drawBitmap(xPosition + (x * 18) + (addInitNine ? 9 : 0) + (addNine ? 9 : 0), yPosition, Images::Hex[value]);

                // Highlight selection?

                if (this->isValidMovement_Hexon(this->selectedShape) && this->isValidPlacement_Hexon(this->selectedShape)) {
                    PD::drawBitmap(xPosition + (x * 18) + (addInitNine ? 9 : 0) + (addNine ? 9 : 0), yPosition, Images::Hex_Highlight);
                }
                else {
                    PD::drawBitmap(xPosition + (x * 18) + (addInitNine ? 9 : 0) + (addNine ? 9 : 0), yPosition, Images::Hex_Error);
                }

            }
                                
        }

        yPosition = yPosition + 16;
        addNine = !addNine;

    }

}

