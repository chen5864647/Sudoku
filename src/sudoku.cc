#include "sudoku.hpp"
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <exception>

using std::cerr;
using std::endl;
using std::initializer_list;
using std::array;

Sudoku::Sudoku(const int map[9][9]) : flag(false), numberMap({0}) {

    for (unsigned short i = 0; i < 9; ++i) 
        for (unsigned short j = 0; j < 9; ++j)
            this->numberMap[i][j] = map[i][j];

    time(&start);

}

Sudoku::Sudoku(const Sudoku &rhs)
: numberMap(rhs.numberMap), flag(false) {
    time(&start);

}

Sudoku::Sudoku(const array<array<unsigned short, 9>, 9> numberMap) 
: numberMap(numberMap), flag(false) { 
    time(&start);

}

Sudoku::Sudoku(const std::initializer_list<unsigned short> numberMap) : numberMap({0}) {
    unsigned short len = numberMap.size();
    if (len != 81) {
        cerr << "This map is not correct!" << endl;
        throw "Constrution Error";
    } else {
        auto item = numberMap.begin();
        for (unsigned short i = 0; i < 9; ++i) {

            for (unsigned short j = 0; j < 9; ++j) 
                this->numberMap[i][j] = *item++;
            // this->numberMap.emplace_back(vec);
        }
    }

    time(&start);
}

Sudoku::~Sudoku() {
    win = flag;
    if (win) {
        time(&finish);
        // timev = finish - start;
    }
    else 
        cerr << "This is no answer!" << endl;
}

bool Sudoku::reaction() {

    this->flag = this->_reaction();
    return this->flag;

}

bool Sudoku::judgeRow(unsigned short col) {
    unsigned short i, j;
    for (i = 0; i < 9; ++i) 
        for (j = 0; j < 9; ++j) {
            if (i == j)
                continue;
            else {
                if ((numberMap[col][i] == numberMap[col][j]) && (numberMap[col][i] != 0) && (numberMap[col][j] != 0))
                    return false;
            }
        }
    
    return true;
}

bool Sudoku::judgeBck(unsigned short col, unsigned short row) {
    unsigned short block;
    unsigned short startCol, startRow, finishCol, finishRow;

    if (col < 3 && row < 3) {
        block = 1;
        startCol = 0; finishCol = 3;
        startRow = 0; finishRow = 3;
    }
    else if (3 <= col && col < 6 && row < 3) {
        block = 2;
        startCol = 3; finishCol = 6;
        startRow = 0; finishRow = 3;
    }
    else if (6 <= col && col < 9 && row < 3) {
        block = 3;
        startCol = 6; finishCol = 9;
        startRow = 0; finishRow = 3;
    }
    else if (col < 3 && 3 <= row  && row < 6) {
        block = 4;
        startCol = 0; finishCol = 3;
        startRow = 3; finishRow = 6;
    }
    else if (3 <= col && col < 6 && 3 <= row && row < 6) {
        block = 5;
        startCol = 3; finishCol = 6;
        startRow = 3; finishRow = 6;
    }
    else if (6 <= col && col < 9 && 3 <= row && row < 6) {
        block = 6;
        startCol = 6; finishCol = 9;
        startRow = 3; finishRow = 6;
    }
    else if (col < 3 && 6 <= row && row < 9) {
        block = 7;
        startCol = 0; finishCol = 3;
        startRow = 6; finishRow = 9;
    }
    else if (3 <= col && col < 6 && 6 <= row && row < 9) {
        block = 8;
        startCol = 3; finishCol = 6;
        startRow = 6; finishRow = 9;
    }
    else {
        block = 9;
        startCol = 6; finishCol = 9;
        startRow = 6; finishRow = 9;
    }

    unsigned short i, j, x, y;
    for (i = startCol; i < finishCol; ++i) 
        for (j = startRow; j < finishRow; ++j) 
            for (x = startCol; x < finishCol; ++x) 
                for (y = startRow; y < finishRow; ++y) {
                    if (i == x && y == j)
                        continue;
                    else {
                        if ((numberMap[i][j] == numberMap[x][y]) && (numberMap[i][j] != 0) && (numberMap[x][y] != 0))
                            return false;
                    }
                }

    return true;
}

bool Sudoku::judgeCol(unsigned short row) {
    unsigned short i, j;
    for (i = 0; i < 9; ++i) 
        for (j = 0; j < 9; ++j) {
            if (i == j)
                continue;
            else {
                if ((numberMap[i][row] == numberMap[j][row]) && (numberMap[i][row] != 0) && (numberMap[j][row] != 0))
                    return false;
            }
        }

    return true;
}

bool Sudoku::judgeWin() {
    for (unsigned short i = 0; i < 9; ++i) {
        for (unsigned short j = 0; j < 9; ++j)
            if (this->numberMap[i][j] != 0)
                return false;
    }

    return true;
} 

// dfs
bool Sudoku::_reaction() {

    unsigned short i, j, k;

    if (this->judgeWin())
        return true;
    else {
        for (i = 0; i < 9; ++i) {
            for (j = 0; j < 9; ++j) {
                // there is no number in this location
                if (this->numberMap[i][j] == 0)
                for (k = 1; k < 10; k++) {
                    this->numberMap[i][j] = k;
                    if (judgeCol(i) && judgeRow(j) && judgeBck(i, j))
                        _reaction();
                    else 
                        this->numberMap[i][j] = 0;

                    // loop and reset
                    this->numberMap[i][j] = 0;
                }

                // return false;
            }
        }
        return false;
    }
    return false;
}
