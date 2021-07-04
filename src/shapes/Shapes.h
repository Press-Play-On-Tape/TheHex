#pragma once

namespace Shapes {

    constexpr uint8_t shape_01[] = { 1, 1,
                                     1, };                //  X

    constexpr uint8_t shape_02[] = { 2, 2,
                                     0, 1,                //  . X
                                     1, 0 };              //   X .

    constexpr uint8_t shape_03[] = { 1, 2,
                                     1,                   //  X
                                     1, };                //   X

    constexpr uint8_t shape_04[] = { 4, 2,
                                     0, 1, 1, 1,          //  . X X X
                                     1, 0, 0, 0 };        //   X . . .

    constexpr uint8_t shape_05[] = { 3, 2,
                                     1, 1, 1,             //  X X X
                                     0, 0, 1 };           //   . . X

    constexpr uint8_t shape_06[] = { 3, 2,
                                     1, 0, 0,             //  X . .
                                     1, 1, 1 };           //   X X X

    constexpr uint8_t shape_07[] = { 4, 2,
                                     0, 0, 0, 1,          //  . . . X
                                     1, 1, 1, 0 };        //   X X X .

    constexpr uint8_t shape_08[] = { 3, 2,
                                     1, 1, 1,             //  X X X 
                                     1, 0, 0 };           //   X . . 

    constexpr uint8_t shape_09[] = { 3, 2,
                                     1, 1, 1,             //  X X X 
                                     0, 1, 0 };           //   . X .  

    constexpr uint8_t shape_10[] = { 3, 2,
                                     0, 1, 0,             //  . X . 
                                     1, 1, 1 };           //   X X X 

    constexpr uint8_t shape_11[] = { 3, 2,
                                     0, 0, 1,             //  . . X 
                                     1, 1, 1 };           //   X X X 

    constexpr uint8_t shape_12[] = { 2, 3,
                                     1, 0,                //  X .  
                                     1, 1,                //   X X 
                                     0, 1 };              //  . X

    constexpr uint8_t shape_13[] = { 3, 3,
                                     0, 0, 1,             //  . . X  
                                     1, 1, 0,             //   X X .
                                     0, 1, 0 };           //  . X .

    constexpr uint8_t shape_14[] = { 2, 3,
                                     0, 1,                //  . X
                                     1, 1,                //   X X 
                                     1, 0 };              //  X .  

    constexpr uint8_t shape_15[] = { 3, 3,
                                     0, 1, 0,             //  . X .
                                     1, 1, 0,             //   X X .
                                     0, 0, 1 };           //  . . X  

    constexpr uint8_t shape_16[] = { 2, 2,
                                     0, 1,                //  . X
                                     1, 1 };              //   X X

    constexpr uint8_t shape_17[] = { 2, 2,
                                     1, 1,                //  X X
                                     1, 0 };              //   X .

    constexpr uint8_t shape_18[] = { 1, 3,
                                     1,                   //  X 
                                     1,                   //   X
                                     1 };                 //  X  

    constexpr uint8_t shape_19[] = { 2, 3,
                                     0, 1,                //  . X
                                     1, 0,                //   X .
                                     0, 1 };              //  . X 

    constexpr uint8_t shape_20[] = { 2, 2,
                                     1, 1,                //  X X
                                     1, 1 };              //   X X

    constexpr uint8_t shape_21[] = { 3, 2,
                                     0, 1, 1,             //  . X X
                                     1, 1, 0 };           //   X X .

    constexpr uint8_t shape_22[] = { 2, 3,
                                     1, 0,                //  X .
                                     1, 0,                //   X .
                                     0, 1 };              //  . X

    constexpr uint8_t shape_23[] = { 2, 3,
                                     0, 1,                //  . X
                                     1, 0,                //   X .
                                     1, 0 };              //  X .

    constexpr uint8_t shape_24[] = { 2, 1,
                                     1, 1 };              //  X X

    constexpr uint8_t Count = 35;

                                    //  00 01  02       03  04       05  06  07       08  09  10       11       12  13       14  15       16       17  18  19       20  21       22  23  24                                  
    constexpr uint8_t shapeWidths[] = {  0, 4, 10 + 12, 10, 36 + 12, 36, 36, 36 + 12, 28, 28, 28 + 12, 28 + 12, 22, 22 + 12, 22, 22 + 12, 16 + 12, 16, 10, 10 + 12, 16, 16 + 12, 16, 16, 16 };

    constexpr uint8_t ShapeIndexes[] = {
        0,
        1,
        1,
        1,
        2,
        2,
        2,
        3,
        3,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
        21,
        22,
        23,
        22,
        23,
        24,
        24,
        24,
    };


    const uint8_t * const ShapeReferences[] = { 
        shape_01, shape_01, shape_02, shape_03, shape_04,
        shape_05, shape_06, shape_07, shape_08, shape_09,
        shape_10, shape_11, shape_12, shape_13, shape_14,
        shape_15, shape_16, shape_17, shape_18, shape_19,
        shape_20, shape_21, shape_22, shape_23, shape_24,
    };
                                // 0                                1                                       2
                               //  0  1  2  3  4  5  6  7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4 
    constexpr uint8_t RotMin[] = { 0, 1, 2, 2, 4, 4, 4, 4,  8,  8,  8,  8, 12, 12, 12, 12, 16, 16, 18, 18, 20, 20, 22, 22, 24 };
    constexpr uint8_t RotMax[] = { 0, 1, 3, 3, 7, 7, 7, 7, 11, 11, 11, 11, 15, 15, 15, 15, 17, 17, 19, 19, 21, 21, 23, 23, 24 };

}
