#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../images/Images.h"
#include "../../entities/Entities.h"


void Game::renderSelection_Hexer() {

    if (this->gamePlayVariables.y % 2 == 0) { //one top, two bottom

        if (this->gamePlayVariables.x % 2 == 0) {

            this->renderSelection_Upright_Hexer();

        }
        else {

            this->renderSelection_Inverted_Hexer();

        }

    }
    else {

        if (this->gamePlayVariables.x % 2 == 0) {

            this->renderSelection_Inverted_Hexer();

        }
        else {

            this->renderSelection_Upright_Hexer();

        }

    }   

}

void Game::renderSelection_Upright_Hexer() {


    // Render top

    uint8_t xCell = this->gamePlayVariables.x / 2;
    uint8_t yCell = this->gamePlayVariables.y;

    PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell], Images::Hex_Highlight);


    // Render bottom ..

    PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell - 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell + 1], Images::Hex_Highlight);
    PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell + 1], Images::Hex_Highlight);

}

void Game::renderSelection_Inverted_Hexer() {


    // Render top

    uint8_t xCell = (this->gamePlayVariables.x / 2);
    uint8_t yCell = this->gamePlayVariables.y;

    PD::drawBitmap(Constants::Cell_xPos[5]+ (xCell * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell], Images::Hex_Highlight);
    PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell], Images::Hex_Highlight);


    // Render bottom ..

    PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell + 1], Images::Hex_Highlight);

}

void Game::renderSidePanel_Hexer() {    

    uint8_t yPosition = 26;

    PD::setColor(5);
    PD::drawLine(171, 0, 171, 188);
    PD::setColor(0);
    PD::fillRect(172, 0, 50, 188);
    PD::drawBitmap(182, 2, Images::Hexer_Vert);


    // Render Score ..

    PD::setColor(13);
    PD::setCursor(176, 48);
    PD::print("Score");
    PD::setColor(6);

    PD::setCursor(176, 60);
    if (this->gamePlayVariables.score < 10000) PD::print("0");
    if (this->gamePlayVariables.score < 1000)  PD::print("0");
    if (this->gamePlayVariables.score < 100)   PD::print("0");
    if (this->gamePlayVariables.score < 10)    PD::print("0");
    PD::print(this->gamePlayVariables.score);

    PD::setColor(13);
    PD::setCursor(180, 76);
    PD::print("Time");
    PD::setColor(6);

    PD::setCursor(176, 88);
    uint8_t mins = this->gamePlayVariables.timer / 60;
    uint8_t secs = this->gamePlayVariables.timer % 60;
    if (mins < 10)  PD::print("0");
    PD::print(static_cast<uint16_t>(mins));
    PD::print(":");
    
    if (secs < 10)   PD::print("0");
    PD::print(static_cast<uint16_t>(secs));

    PD::drawBitmap(196, 110, Images::Control_A);
    PD::drawBitmap(177, 126, Images::Control_B);

}

void Game::renderScreen_Hexer() {


    // Top images ..

    for (uint8_t x = 0; x < Constants::GridSize; x++) {

        uint8_t color = this->gamePlayVariables.boardTop[x];

        if (color != 0) {

            switch (color) {

                case 1:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_01[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 2:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_02[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 3:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_03[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 4:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_04[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 5:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_05[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 6:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_06[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 7:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_07[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

                case 8:
                    PD::drawBitmap(Constants::Cell_xPos[4] + (x * 18), Constants::Cell_yPos[0], Images::Hex_Combined_08[10 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos)]);
                    break;

            }

        }

    }

    for (uint8_t y = 9; y > 0; y--) {

        for (uint8_t x = 0; x < 9; x++) {

            // uint8_t xCell = Constants::Cell_Min_X[y - 1] + x;
            uint8_t xLeft = (y % 2 == 0 ? Constants::Cell_xPos[5] : Constants::Cell_xPos[4]);
            uint8_t value = gamePlayVariables.board[x][y - 1];

            switch (value) {

                case 0:

                    PD::drawBitmap(xLeft + (x * 18), Constants::Cell_yPos[y - 1], Images::Hex[0]);
                    break;

                case 1 ... 8:

                    if (this->gamePlayVariables.removePieces.pos <= 0 || this->getCell(BoardType::Offset, x, y - 1) == 0) {                  
                        PD::drawBitmap(xLeft + (x * 18) + ((this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos) * this->getCell(BoardType::Offset, x, y - 1)), Constants::Cell_yPos[y - 1] + (this->getCell(BoardType::Offset, x, y - 1, true) * Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos]), Images::Hex_Combined[value]);
                    }
                    else {

                        if (this->gamePlayVariables.removePieces.pos > 0) {

                            if (this->getCell(BoardType::Offset, x, y - 1, false) != 0) {

                                if (y - 1 > 0) {
    
                                    PD::drawBitmap(xLeft + (x * 18), Constants::Cell_yPos[y - 1], Images::Hex_00_00);

                                }

                                PD::drawBitmap(xLeft + (x * 18) + ((this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos) * this->getCell(BoardType::Offset, x, y - 1)), 
                                    Constants::Cell_yPos[y - 1] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos], 
                                    Images::Hex[value]);

                            }
                            else {

                                PD::drawBitmap(xLeft + (x * 18) + ((this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos) * this->getCell(BoardType::Offset, x, y - 1)), Constants::Cell_yPos[y - 1] + (this->getCell(BoardType::Offset, x, y - 1, true) * Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos]), Images::Hex_Combined[value]);

                            }

                        }
                        else {

                            PD::drawBitmap(xLeft + (x * 18) + ((this->gamePlayVariables.removePieces.pos > 9 ? 9 : this->gamePlayVariables.removePieces.pos) * this->getCell(BoardType::Offset, x, y - 1)), Constants::Cell_yPos[y - 1] + (this->getCell(BoardType::Offset, x, y - 1, true) * Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos]), Images::Hex_Combined[value]);

                        }

                    }

                    break;

            }

        }

    }


    // Render rotating piece ..

    if (this->gamePlayVariables.removePieces.state == 0 && this->gamePlayVariables.removePieces.pos > 0) {

        if (this->gamePlayVariables.y % 2 == 0) { //one top, two bottom

            if (this->gamePlayVariables.x % 2 == 0) {

                this->renderScreen_Rotate_XEven_YEven_Hexer();

            }
            else {

                this->renderScreen_Rotate_XOdd_YEven_Hexer();

            }

        }
        else {

            if (this->gamePlayVariables.x % 2 == 0) {

                this->renderScreen_Rotate_XEven_YOdd_Hexer();

            }
            else {

                this->renderScreen_Rotate_XOdd_YOdd_Hexer();

            }

        }   

    }

}

void Game::renderScreen_Rotate_XEven_YEven_Hexer() {

    
    // Render top

    uint8_t xCell = this->gamePlayVariables.x / 2;
    uint8_t yCell = this->gamePlayVariables.y;

    PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell], Images::Hex_00_01);


    // Render bottom ..

    PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell - 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell + 1], Images::Hex_00_01);
    PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell + 1], Images::Hex_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell - 1][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Constants::Cell_yPos[yCell + 1],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell-1) * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell - 1][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell - 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Constants::Cell_yPos[yCell + 1],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);


    }

}

void Game::renderScreen_Rotate_XOdd_YEven_Hexer() {


    // Render top

    uint8_t xCell = (this->gamePlayVariables.x / 2);
    uint8_t yCell = this->gamePlayVariables.y;

    PD::drawBitmap(Constants::Cell_xPos[5]+ (xCell * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell], Images::Hex_00_01);
    PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell], Images::Hex_00_01);


    // Render bottom ..

    PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell + 1], Images::Hex_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Constants::Cell_yPos[yCell],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Constants::Cell_yPos[yCell],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);


    }

}


void Game::renderScreen_Rotate_XEven_YOdd_Hexer() {
     

    // Render top

    uint8_t xCell = (this->gamePlayVariables.x / 2) - 1;
    uint8_t yCell = this->gamePlayVariables.y;

    PD::drawBitmap(Constants::Cell_xPos[5]+ ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell], Images::Hex_00_01);
    PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell + 2) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell], Images::Hex_00_01);


    // Render bottom ..

    PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 2) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 18), Constants::Cell_yPos[yCell + 1], Images::Hex_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Constants::Cell_yPos[yCell],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Constants::Cell_yPos[yCell],
                       Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 0 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Images::Hex[color]);

    }

}



void Game::renderScreen_Rotate_XOdd_YOdd_Hexer() {
    
    // Render top

    uint8_t xCell = this->gamePlayVariables.x / 2;
    uint8_t yCell = this->gamePlayVariables.y;

    PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell], Images::Hex_00_01);


    // Render bottom ..

    PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell - 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell + 1], Images::Hex_00_01);
    PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0), Constants::Cell_yPos[yCell + 1], Images::Hex_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                    Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                    Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                    Constants::Cell_yPos[yCell + 1],
                    Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + (xCell * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                    Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                    Images::Hex[color]);

    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[4] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                    Constants::Cell_yPos[yCell] + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                    Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell - 1) * 18) + (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                    Constants::Cell_yPos[yCell + 1],
                    Images::Hex[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Cell_xPos[5] + ((xCell + 1) * 18) - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                    Constants::Cell_yPos[yCell + 1] - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                    Images::Hex[color]);


    }

}
