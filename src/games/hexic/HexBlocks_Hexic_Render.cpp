#include "../../HexBlocks.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include "../../images/Images.h"
#include "../../entities/Entities.h"


void Game::renderSidePanel_Hexic() {    

    uint8_t yPosition = 26;

    PD::setColor(5);
    PD::drawLine(171, 0, 171, 188);
    PD::setColor(0);
    PD::fillRect(172, 0, 50, 188);
    PD::drawBitmap(182, 2, Images::Hexic_Vert);


    // Render Score ..

    PD::setColor(13);
    PD::setCursor(176, 48);
    PD::print("Score");
    PD::setColor(6);

    PD::setCursor(176, 59);
    if (this->gamePlayVariables.score < 10000)  PD::print("0");
    if (this->gamePlayVariables.score < 1000)   PD::print("0");
    if (this->gamePlayVariables.score < 100)    PD::print("0");
    if (this->gamePlayVariables.score < 10)     PD::print("0");
    PD::print(this->gamePlayVariables.score);

    PD::setColor(13);
    PD::setCursor(176, 75);
    PD::print("Level");
    PD::setColor(6);

    PD::setCursor(184, 86);
    if (this->gamePlayVariables.level < 100)    PD::print("0");
    if (this->gamePlayVariables.level < 10)     PD::print("0");
    PD::print(this->gamePlayVariables.level);

    PD::setCursor(176, 102);
    PD::setColor(13);
    PD::print("Moves");
    PD::setColor(6);

    if (this->gamePlayVariables.gameOver || this->gamePlayVariables.movesLeft > 10 || Utils::getFrameCountHalf(48)) {

        PD::setCursor(184, 113);
        if (this->gamePlayVariables.movesLeft < 100) PD::print("0");
        if (this->gamePlayVariables.movesLeft < 10) PD::print("0");
        PD::print(this->gamePlayVariables.movesLeft);

    }

    PD::drawBitmap(196, 128, Images::Control_A);
    PD::drawBitmap(177, 144, Images::Control_B);
}


void Game::renderScreen_Hexic() {


    // Top images ..

    if (this->gamePlayVariables.removePieces.pos > 9) {

        uint8_t idx = (17 - this->gamePlayVariables.removePieces.pos) / 2;

        for (uint8_t x = 0; x < Constants::GridSize; x++) {

            uint8_t color = this->gamePlayVariables.boardTop[x];

            if (color != 0) {


                switch (color) {

                    case 1:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_01[idx]);
                        break;

                    case 2:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_02[idx]);
                        break;

                    case 3:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_03[idx]);
                        break;

                    case 4:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_04[idx]);
                        break;

                    case 5:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_05[idx]);
                        break;

                    case 6:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_06[idx]);
                        break;

                    case 7:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_07[idx]);
                        break;

                    case 8:
                        PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yTop[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_08[idx]);
                        break;

                }

            }

        }

    }


    // Bottom images ..

    if (this->gamePlayVariables.levelUp.active) {
        
        if (this->gamePlayVariables.removePieces.pos < 9) {

            uint8_t idx = ((this->gamePlayVariables.removePieces.pos) / 2) + 4;

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                uint8_t color = this->gamePlayVariables.boardBottom[x];

                if (color != 0) {

                    switch (color) {

                        case 1:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_01[idx]);
                            break;

                        case 2:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_02[idx]);
                            break;

                        case 3:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_03[idx]);
                            break;

                        case 4:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_04[idx]);
                            break;

                        case 5:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_05[idx]);
                            break;

                        case 6:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_06[idx]);
                            break;

                        case 7:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_07[idx]);
                            break;

                        case 8:
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rotated_Combined_08[idx]);
                            break;

                    }

                }
                else {

                    PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rot_00_00);

                }

            }

        }
        else {

            for (uint8_t x = 0; x < Constants::GridSize; x++) {

                PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[Constants::Hexic::Cell_yBottom[x]] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rot_00_00);

            }

        }

    }


    // Main board ..

    for (uint8_t y = 9; y > 0; y--) {

        for (uint8_t x = 0; x < 9; x++) {

            if (!this->gamePlayVariables.levelUp.active || y - 1 != Constants::Hexic::Cell_yBottom[x]) {

                uint8_t value = this->getCell(x, y - 1);

                switch (value) {

                    case 0:
                    
                        if (this->gamePlayVariables.removePieces.pos <= 9 || !(this->gamePlayVariables.boardTop[x] != 0 && y - 1 == Constants::Hexic::Cell_yTop[x])) {
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[y - 1] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rot_00_00);
                        }
                        break;

                    case 1 ... 8:

                        if (this->gamePlayVariables.removePieces.pos == 0 || this->getCell(BoardType::Offset, x, y - 1) == 0) {                  
                            PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[y - 1] + (x % 2 == 0 ? 0 : 9) + (this->getCell(BoardType::Offset, x, y - 1) * this->gamePlayVariables.removePieces.pos), Images::Hex_Rotated_Combined[value]);                    
                        }
                        else {

                            if (this->gamePlayVariables.removePieces.pos <= 9 || !(this->gamePlayVariables.boardTop[x] != 0 && y - 1 == Constants::Hexic::Cell_yTop[x])) {
                                PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[y - 1] + (x % 2 == 0 ? 0 : 9), Images::Hex_Rot_00_00);       
                            }             

                            if ((!this->gamePlayVariables.levelUp.active || value != Constants::Hexic::BlackPearl) && y - 1 != Constants::Hexic::Cell_yBottom[x]) {
                                PD::drawBitmap(Constants::Hexic::Cell_Left + (x * 17), Constants::Hexic::Cell_yPos[y - 1] + (x % 2 == 0 ? 0 : 9) + (this->getCell(BoardType::Offset, x, y - 1) * this->gamePlayVariables.removePieces.pos), Images::Hex_Rotated[value]);                    
                            }

                        }
                        break;

                }

            }

        }

    }


    // Render black pearls ..

    if (this->gamePlayVariables.foundBlackPearls.numberActive() > 0) {

        for (FoundFlower &foundBlackPearl : this->gamePlayVariables.foundBlackPearls.flower) {

            if (foundBlackPearl.active) {

                PD::drawBitmap(Constants::Hexic::Cell_Left + (foundBlackPearl.x * 17), Constants::Hexic::Cell_yPos[foundBlackPearl.y] + (foundBlackPearl.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_07_00);                    
            
            }

        }

    }


    // Render rotating piece ..

    if (this->gamePlayVariables.populate == 0 && this->gamePlayVariables.removePieces.state == 0 && this->gamePlayVariables.removePieces.pos > 0) {

        if (this->gamePlayVariables.flowerSelected.mode != SelectionMode::FlowerSelected) {

            if (this->gamePlayVariables.y % 2 == 0) { //one top, two bottom

                if (this->gamePlayVariables.x % 2 == 0) {

                    this->renderScreen_Rotate_Cluster_XEven_YEven_Hexic();

                }
                else {

                    this->renderScreen_Rotate_Cluster_XOdd_YEven_Hexic();

                }

            }
            else {

                if (this->gamePlayVariables.x % 2 == 0) {

                    this->renderScreen_Rotate_Cluster_XEven_YOdd_Hexic();

                }
                else {

                    this->renderScreen_Rotate_Cluster_XOdd_YOdd_Hexic();

                }

            }   

        }
        else {

            uint8_t xCell = 0;
            uint8_t yCell = 0;

            this->selectionOnSilverGem(this->gamePlayVariables.flowerSelected.prevDirection, xCell, yCell);
            
            if (xCell % 2 == 0) {

                this->renderScreen_Rotate_Flower_XEven_Hexic(xCell, yCell);

            }
            else {

                this->renderScreen_Rotate_Flower_XOdd_Hexic(xCell, yCell);

            }

        }

    }

}



void Game::renderSelection_Hexic() {

    if (this->gamePlayVariables.flowerSelected.mode == SelectionMode::None || this->gamePlayVariables.flowerSelected.mode == SelectionMode::FlowerTouched) {
            
        if (this->gamePlayVariables.y % 2 == 0) { //one left, two right

            if (this->gamePlayVariables.x % 2 == 0) {

                this->renderSelection_Right_EvenX_Hexic(); 

            }
            else {

                this->renderSelection_Left_OddX_Hexic();

            }

        }
        else {

            if (this->gamePlayVariables.x % 2 == 0) {

                this->renderSelection_Left_EvenX_Hexic(); 

            }
            else {

                this->renderSelection_Right_OddX_Hexic();

            }

        }   

    }
    else {

        if (this->gamePlayVariables.flowerSelected.x % 2 == 0) {

            this->renderSelection_Flower_EvenX_Hexic();

        }
        else {

            this->renderSelection_Flower_OddX_Hexic();

        }

    }

}

void Game::renderSelection_Left_EvenX_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = (this->gamePlayVariables.y / 2) + 1;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell - 1] + (this->gamePlayVariables.x % 2 == 1 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 1 ? 0 : 9), Images::Hex_Rot_Highlight);

}

void Game::renderSelection_Left_OddX_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = this->gamePlayVariables.y / 2;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 1 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.x % 2 == 1 ? 0 : 9), Images::Hex_Rot_Highlight);

}

void Game::renderSelection_Right_EvenX_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = this->gamePlayVariables.y / 2;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 1 ? 0 : 9), Images::Hex_Rot_Highlight);

}

void Game::renderSelection_Right_OddX_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = this->gamePlayVariables.y / 2;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.x % 2 == 0 ? 0 : 9), Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.x % 2 == 1 ? 0 : 9), Images::Hex_Rot_Highlight);

}

void Game::renderScreen_Rotate_Cluster_XEven_YEven_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = this->gamePlayVariables.y / 2;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), 
                       Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), 
                       Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);


    }
    
}

void Game::renderScreen_Rotate_Cluster_XOdd_YEven_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = this->gamePlayVariables.y / 2;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);


    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.y % 2 == 1 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

    }

}

void Game::renderScreen_Rotate_Cluster_XEven_YOdd_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = (this->gamePlayVariables.y / 2) + 1;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17),
                       Constants::Hexic::Cell_yPos[yCell] - 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Constants::Hexic::Cell_yPos[yCell] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Constants::Hexic::Cell_yPos[yCell] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Images::Hex_Rotated[color]);
    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17),
                       Constants::Hexic::Cell_yPos[yCell] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 18 - (this->gamePlayVariables.removePieces.pos * 2)), 
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                       Constants::Hexic::Cell_yPos[yCell] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                       Images::Hex_Rotated[color]);

    }

}

void Game::renderScreen_Rotate_Cluster_XOdd_YOdd_Hexic() {

    uint8_t xCell = this->gamePlayVariables.x;
    uint8_t yCell = (this->gamePlayVariables.y / 2);

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1] + 9, Images::Hex_Rot_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                    Constants::Hexic::Cell_yPos[yCell] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                    Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                    Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                    Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left  + (xCell * 17), 
                    Constants::Hexic::Cell_yPos[yCell + 1] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                    Images::Hex_Rotated[color]);

    }
    else {

        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                    Constants::Hexic::Cell_yPos[yCell + 1] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                    Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos],
                    Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos), 
                    Images::Hex_Rotated[color]);

        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left  + (xCell * 17), 
                    Constants::Hexic::Cell_yPos[yCell] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                    Images::Hex_Rotated[color]);


    }

}

void Game::renderSelection_Flower_EvenX_Hexic() {

    uint8_t xCell = this->gamePlayVariables.flowerSelected.x;
    uint8_t yCell = this->gamePlayVariables.flowerSelected.y;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell - 1], Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_Highlight);
}

void Game::renderSelection_Flower_OddX_Hexic() {

    uint8_t xCell = this->gamePlayVariables.flowerSelected.x;
    uint8_t yCell = this->gamePlayVariables.flowerSelected.y;

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1] + 9, Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_Highlight);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_Highlight);

}

void Game::renderScreen_Rotate_Flower_XEven_Hexic(uint8_t xCell, uint8_t yCell) {

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell - 1], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        // move tl-br
        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell - 1] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move down
        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move tr-bl
        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move br-tl
        color = this->gamePlayVariables.board[xCell - 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);


        // move up
        color = this->gamePlayVariables.board[xCell - 1][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move bl - tr
        color = this->gamePlayVariables.board[xCell][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

    }
    else {

        // move tr-bl
        uint8_t color = this->gamePlayVariables.board[xCell - 1][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell - 1] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move down
        color = this->gamePlayVariables.board[xCell - 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move tl-br
        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move bl - tr
        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move up
        color = this->gamePlayVariables.board[xCell + 1][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move br-tl
        color = this->gamePlayVariables.board[xCell][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

    }
    
}


void Game::renderScreen_Rotate_Flower_XOdd_Hexic(uint8_t xCell, uint8_t yCell) {

    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell - 1] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17), Constants::Hexic::Cell_yPos[yCell + 1] + 9, Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell + 1], Images::Hex_Rot_00_01);
    PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), Constants::Hexic::Cell_yPos[yCell], Images::Hex_Rot_00_01);

    if (this->gamePlayVariables.removePieces.rotateDirection == RotateDirection::Clockwise) {

        // move tl-br
        uint8_t color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move down
        color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell] + (yCell == 0 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move tr-bl
        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move br-tl
        color = this->gamePlayVariables.board[xCell - 1][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);


        // move up
        color = this->gamePlayVariables.board[xCell - 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell + 1] + (yCell == 0 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move bl - tr
        color = this->gamePlayVariables.board[xCell][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

    }
    else {

        // move tr-bl
        uint8_t color = this->gamePlayVariables.board[xCell - 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell - 1] + 9 + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move down
        color = this->gamePlayVariables.board[xCell - 1][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell] + (yCell == 0 ? 9 : 0) + (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move tl-br
        color = this->gamePlayVariables.board[xCell][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell - 1) * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] + (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move bl - tr
        color = this->gamePlayVariables.board[xCell + 1][yCell + 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + (xCell * 17) + Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell + 1] + 9 - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

        // move up
        color = this->gamePlayVariables.board[xCell + 1][yCell];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17), 
                       Constants::Hexic::Cell_yPos[yCell + 1] + (yCell == 0 ? 9 : 0) - (this->gamePlayVariables.removePieces.pos > 9 ? 18 : 18 - (this->gamePlayVariables.removePieces.pos * 2)),
                       Images::Hex_Rotated[color]);

        // move br-tl
        color = this->gamePlayVariables.board[xCell][yCell - 1];
        PD::drawBitmap(Constants::Hexic::Cell_Left + ((xCell + 1) * 17) - Constants::fallingYOffset[this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos], 
                       Constants::Hexic::Cell_yPos[yCell] - (this->gamePlayVariables.removePieces.pos > 9 ? 9 : 9 - this->gamePlayVariables.removePieces.pos),
                       Images::Hex_Rotated[color]);

    }

}
