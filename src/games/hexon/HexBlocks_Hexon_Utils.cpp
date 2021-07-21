#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "../../utils/Constants.h"
#include "../../sounds/Sounds.h"

bool Game::isValidMovement_Hexon(SelectedShape &selectedShape) {
    
    return isValidMovement_Hexon(selectedShape, this->gamePlayVariables.x, this->gamePlayVariables.y);

}

bool Game::isValidMovement_Hexon(SelectedShape &selectedShape, const int16_t xPlacement, const uint16_t yPlacement) {

    if (yPlacement + selectedShape.getHeight() > Constants::GridSize) return false;


    // Hanging over the left ..

    for (uint8_t y = 0; y < selectedShape.getHeight(); y++) {

        if (y == 0) {

            if (selectedShape.isUpperLeftCellBlank()) {

                if (xPlacement < Constants::Cell_Min_X[yPlacement + y] - 1) {
                 
                    return false;

                }

            }
            else {

                if (xPlacement < Constants::Cell_Min_X[yPlacement + y]) return false;

            }

        }
        else if (y == selectedShape.getHeight() - 1) {

            if (selectedShape.isLowerLeftCellBlank()) {

                if (xPlacement < Constants::Cell_Min_X[yPlacement + y] - 1) return false;

            }
            else {

                if (y % 2 == 0) {

                    if (xPlacement <= Constants::Cell_Min_X[yPlacement + y] - 1) return false;

                }
                else {

                    if (xPlacement < Constants::Cell_Min_X[yPlacement + y] + ((yPlacement+ y) % 2 == 0 ? -1 : 0)) return false;

                }

            }

        }

    }



    // Hanging over the right ..

    for (uint8_t y = 0; y < selectedShape.getHeight(); y++) {

        if (y == 0) {

            if (selectedShape.isUpperRightCellBlank()) {

                if (xPlacement + selectedShape.getWidth() - 2 > Constants::Cell_Max_X[yPlacement + y]) return false;

            }
            else {

                if (xPlacement + selectedShape.getWidth() - 1 > Constants::Cell_Max_X[yPlacement + y]) return false;

            }

        }
        else if (y == selectedShape.getHeight() - 1) {

            if (selectedShape.isLowerRightCellBlank()) {

                if (xPlacement + selectedShape.getWidth() - 2 > Constants::Cell_Max_X[yPlacement + y]) return false;

            }
            else {

                if (y % 2 == 0) {

                    if (xPlacement + selectedShape.getWidth() - 1 > Constants::Cell_Max_X[yPlacement + y]) return false;

                }
                else {

                    if (xPlacement + selectedShape.getWidth() - 1 > Constants::Cell_Max_X[yPlacement + y] + ((yPlacement+ y) % 2 == 0 ? -1 : 0)) return false;

                }

            }

        }

    }
    return true;

}

bool Game::isValidPlacement_Hexon(SelectedShape &selectedShape) {

    return this->isValidPlacement_Hexon(selectedShape, this->gamePlayVariables.x, this->gamePlayVariables.y);

}

bool Game::isValidPlacement_Hexon(SelectedShape &selectedShape, const uint8_t xPlacement, const uint8_t yPlacement) {

    for (int8_t y = 0; y < selectedShape.getHeight(); y++) {

        for (int8_t x = 0; x < selectedShape.getWidth(); x++) {

            int8_t xPos = xPlacement + x + (((yPlacement % 2 == 1) && ((yPlacement + y) % 2) == 0) ? 1 : 0);
            int8_t yPos = (yPlacement + y); 

            if (selectedShape.getCell(x, y) != 0 && xPos < 0 || xPos > 8 || yPos < 0 || yPos > 8) {

                return false;

            }

            if (selectedShape.getCell(x, y) != 0 && this->gamePlayVariables.board[xPos][yPos] != 0) {

                return false;

            }

        }

    }

    return true;

}

void Game::placeShape_Hexon() {

    this->mode = Mode::ShapeSelection;
    this->shapes[this->selectedShape.getSelectedIndex()].setIndex(0);

    for (uint8_t y = 0; y < this->selectedShape.getHeight(); y++) {

        for (uint8_t x = 0; x < this->selectedShape.getWidth(); x++) {

            if (this->selectedShape.getCell(x, y) != 0) {

                uint8_t xPos = this->gamePlayVariables.x + x + ((this->gamePlayVariables.y % 2 == 1) && (y % 2 == 1) ? 1 : 0);
                this->gamePlayVariables.board[xPos][this->gamePlayVariables.y + y] = this->selectedShape.getCell(x, y);

            }

        }

    }


    // Shuffle shpaes up ..

    for (uint8_t i = 0; i < Constants::Hexon::noOfSideShapes - 1; i++) {
    
        if (this->shapes[i].getIndex() == 0) {

            for (uint8_t j = i; j < Constants::Hexon::noOfSideShapes - 1; j++) {

                this->shapes[j].setIndex(this->shapes[j + 1].getIndex());
                this->shapes[j].setColor(this->shapes[j + 1].getColor());
                this->shapes[j].setMinRange(this->shapes[j + 1].getMinRange());
                this->shapes[j].setMaxRange(this->shapes[j + 1].getMaxRange());

            }

            this->shapes[Constants::Hexon::noOfSideShapes - 1].setIndex(0);

        }

    }


    // Reset selected item index ..

    for (uint8_t i = 0; i < Constants::Hexon::noOfSideShapes; i++) {

        if (this->shapes[i].getIndex() != 0) {

            this->selectedShape.setSelectedIndex(i);
            this->selectedShape.setShape(this->shapes[i]);

            return;

        }

    }


    // No shapes left, get random items ..

    this->populateShapes_Hexon();

}

void Game::populateShapes_Hexon() {

    uint8_t minColor = 0;
    uint8_t maxColor = 0;

    switch (this->gamePlayVariables.score) {

        case 0 ... 50:
            minColor = 3;
            maxColor = 7;
            break;

        case 51 ... 100:
            minColor = 2;
            maxColor = 7;
            break;

        case 101 ... 250:
            minColor = 1;
            maxColor = 7;
            break;

        default:
            minColor = 1;
            maxColor = 7;
            break;

    }

    for (uint8_t i = 0; i < Constants::Hexon::noOfSideShapes; i++) {

        uint8_t rndShape = random(1, Shapes::Count);
        uint8_t index = Shapes::ShapeIndexes[rndShape];

        this->shapes[i].setIndex(index);
        this->shapes[i].setColor(random(minColor, maxColor));
        this->shapes[i].setMinRange(Shapes::RotMin[index]);
        this->shapes[i].setMaxRange(Shapes::RotMax[index]);

    }

    this->selectedShape.setSelectedIndex(0);
    this->selectedShape.setShape(this->shapes[0]);

}

void Game::removeWinningLines_Hexon() {

    uint8_t winningLines = 0;


    // Horizontal lines ..

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t l = 9; l >= 4; l--) {

            if (l > Constants::Cell_Count[y]) {

                continue;

            }
            else {

                int8_t color = 0;
                int8_t count = 0;

                for (uint8_t range = Constants::Cell_Min_X[y]; range < Constants::Cell_Max_X[y]; range++) {

                    for (uint8_t startingPos = range; startingPos <= Constants::Cell_Max_X[y]; startingPos++) {

                        if (startingPos == range) {

                            color = abs(this->gamePlayVariables.board[startingPos][y]);

                            if (color == 0) {

                                break;

                            }
                            else {

                                count = 1;

                            }

                        }
                        else if (abs(this->gamePlayVariables.board[startingPos][y]) == color) {

                            count++;

                            if (count == l) {

                                this->gamePlayVariables.scoreToAdd = this->gamePlayVariables.scoreToAdd + Constants::Hexon::Scores[l];
                                winningLines = winningLines + 1;
                                for (uint8_t fill = range; fill < range + l; fill++) {
                                    this->gamePlayVariables.board[fill][y] = -abs(this->gamePlayVariables.board[fill][y]);
                                }

                                break;

                            }

                        }
                        else {

                            break;

                        }

                    }

                }

            }

        }

    }


    // Slash /

   for (uint8_t d = 0; d < Constants::GridSize; d++) {

        for (uint8_t l = Constants::GridSize; l >= 4; l--) {

            if (l > Constants::Cell_Count[d]) {

                continue;

            }
            else {

                int8_t color = 0;
                int8_t count = 0;

                for (uint8_t range = Constants::Cell_Min_X[d]; range < Constants::Cell_Max_X[d]; range++) {

                    for (uint8_t startingPos = range; startingPos <= Constants::Cell_Max_X[d]; startingPos++) {

                        if (startingPos == range) {

                            color = abs(this->getCellSlash_Hexon(startingPos, d));

                            if (color == 0) {

                                break;

                            }
                            else {

                                count = 1;

                            }

                        }
                        else if (abs(this->getCellSlash_Hexon(startingPos, d)) == color) {

                            count++;

                            if (count == l) {

                                this->gamePlayVariables.scoreToAdd = this->gamePlayVariables.scoreToAdd + Constants::Hexon::Scores[l];
                                winningLines = winningLines + 1;

                                for (uint8_t fill = range; fill < range + l; fill++) {
                                    this->setCellSlash_Hexon(fill, d, -abs(this->getCellSlash_Hexon(fill, d)));
                                }

                                break;

                            }

                        }

                        else {

                            break;

                        }

                    }

                }

            }

        }

    }

    // Backslash top left,bottom

   for (uint8_t d = 0; d < Constants::GridSize; d++) {

        for (uint8_t l = 9; l >= 4; l--) {

            if (l > Constants::Cell_Count[d]) {

                continue;

            }
            else {

                int8_t color = 0;
                int8_t count = 0;

                for (uint8_t range = Constants::Cell_Min_X[d]; range < Constants::Cell_Max_X[d]; range++) {

                    for (uint8_t startingPos = range; startingPos <= Constants::Cell_Max_X[d]; startingPos++) {

                        if (startingPos == range) {

                            color = abs(this->getCellBackslash_Hexon(startingPos, d));

                            if (color == 0) {

                                break;

                            }
                            else {

                                count = 1;

                            }

                        }
                        else if (abs(this->getCellBackslash_Hexon(startingPos, d)) == color) {

                            count++;

                            if (count == l) {

                                this->gamePlayVariables.scoreToAdd = this->gamePlayVariables.scoreToAdd + Constants::Hexon::Scores[l];
                                winningLines = winningLines + 1;

                                for (uint8_t fill = range; fill < range + l; fill++) {
                                    this->setCellBackslash_Hexon(fill, d, -abs(this->getCellBackslash_Hexon(fill, d)));
                                }

                                break;

                            }

                        }

                        else {

                            break;

                        }

                    }

                }

            }

        }

    }


    // launch particles ..

    for (uint8_t y = 0; y < Constants::GridSize; y++) {

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                if (this->gamePlayVariables.board[x][y] < 0) {

                    for (uint8_t i = 0; i < 15; i++) {

                        uint8_t xCentre = 0;
                        uint8_t yCentre = 0;

                        this->getCentreOfTile_Common(x, y, xCentre, yCentre);
                        this->launchParticles(xCentre, yCentre, ExplosionSize::Medium);
                        this->gamePlayVariables.board[x][y] = 0;

                    }

                }

            }

        }

    }


    // Play sounds ..

    switch (winningLines) {

        case 1:
            this->playSoundEffect(SoundTheme::Bubble1);
            break;

        case 2:
            this->playSoundEffect(SoundTheme::LevelUp1);
            break;

        case 3 ... 10:
            this->playSoundEffect(SoundTheme::LevelUp2);
            break;

    }

}

int8_t Game::getCellSlash_Hexon(const uint8_t x, const uint8_t d) {

    uint8_t xLoc = Constants::Hexon::slash_X[(d * 9) + x];
    uint8_t yLoc = Constants::Hexon::slash_Y[(d * 9) + x];

    return this->gamePlayVariables.board[xLoc][yLoc];

}

void Game::setCellSlash_Hexon(const uint8_t x, const uint8_t d, const int8_t val) {

    uint8_t xLoc = Constants::Hexon::slash_X[(d * 9) + x];
    uint8_t yLoc = Constants::Hexon::slash_Y[(d * 9) + x];

    this->gamePlayVariables.board[xLoc][yLoc] = val;

}

int8_t Game::getCellBackslash_Hexon(const uint8_t x, const uint8_t d) {

    uint8_t xLoc = Constants::Hexon::backslash_X[(d * 9) + x];
    uint8_t yLoc = Constants::Hexon::backslash_Y[(d * 9) + x];

    return this->gamePlayVariables.board[xLoc][yLoc];

}

void Game::setCellBackslash_Hexon(const uint8_t x, const uint8_t d, const int8_t val) {

    uint8_t xLoc = Constants::Hexon::backslash_X[(d * 9) + x];
    uint8_t yLoc = Constants::Hexon::backslash_Y[(d * 9) + x];

    this->gamePlayVariables.board[xLoc][yLoc] = val;

}

bool Game::isValidMoveAvailable_Hexon() {

    bool cont = false;

    for (uint8_t i = 0; i < Constants::Hexon::noOfSideShapes; i++) {

        if (this->shapes[i].getIndex() != 0) {

            SelectableShape shape = shapes[i];
            shape.setIndex(shape.getMinRange());

            for (uint8_t rot = shape.getMinRange(); rot <= shape.getMaxRange(); rot++) {

                SelectedShape selectedShape;
                selectedShape.setShape(shape);

                for (uint8_t y = 0; y <= 9; y++) {
                    
                    for (uint8_t x = 0; x <= 9; x++) {

                        if (this->isValidPlacement_Hexon(selectedShape, x, y)) return true;

                    }

                }

                shape.rotate();

            }

        }

    }

    return false;

}


