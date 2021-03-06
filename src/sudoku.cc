#include "sudoku.hpp"
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <exception>

using std::cerr;
using std::endl;
using std::initializer_list;
using std::array;
using std::cout;

Sudoku::Sudoku(const int map[9][9]) : flag(false), numberMap({0}) {

    for (VALUE i = 0; i < 9; ++i) 
        for (VALUE j = 0; j < 9; ++j)
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

array<array<VALUE, 9>, 9> Sudoku::getMap() const {
    return this->_answer;
}



bool Sudoku::reaction() {

    // this->flag = this->_reaction();
    Answer answer;
    answer.setMap(this->numberMap);
    this-> flag = answer.getAnswer();
    if (flag) 
        this->_answer = answer.getMap();

    return this->flag;

}

/*
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
            if (this->numberMap[i][j] == 0)
                return false;
    }

    return true;
} 

// dfs
bool Sudoku::_reaction() {

    unsigned short i, j, k;

    if (this->judgeWin()) {
        this->flag = true;
        return true;
    }
    else {
        for (i = 0; i < 9; ++i) {
            for (j = 0; j < 9; ++j) {
                // there is no number in this location
                if (this->numberMap[i][j] != 0)
                    continue;
                else {
                    for (k = 1; k < 10; k++) {
                        this->numberMap[i][j] = k;
                        if (judgeCol(i) && judgeRow(j) && judgeBck(i, j)) {
                            return _reaction();#include "sudoku.hpp"
2
#include <iterator>
3
#include <iostream>
4
#include <stdexcept>
5
#include <exception>
6
​
7
using std::cerr;
8
using std::endl;
9
using std::initializer_list;
10
using std::array;
11
using std::cout;
12
​
13
Sudoku::Sudoku(const int map[9][9]) : flag(false), numberMap({0}) {
14
​
15
    for (unsigned short i = 0; i < 9; ++i) 
16
        for (unsigned short j = 0; j < 9; ++j)
17
            this->numberMap[i][j] = map[i][j];
18
​
19
    time(&start);
20
​
21
}
22
​
23
Sudoku::Sudoku(const Sudoku &rhs)
24
: numberMap(rhs.numberMap), flag(false) {
25
    time(&start);
26
​
27
}
28
​
29
Sudoku::Sudoku(const array<array<unsigned short, 9>, 9> numberMap) 
30
: numberMap(numberMap), flag(false) { 
31
    time(&start);
32
​
33
}
34
​
35
Sudoku::Sudoku(const std::initializer_list<unsigned short> numberMap) : numberMap({0}) {
36
    unsigned short len = numberMap.size();
37
    if (len != 81) {
38
        cerr << "This map is not correct!" << endl;
39
        throw "Constrution Error";
40
    } else {
41
        auto item = numberMap.begin();
42
        for (unsigned short i = 0; i < 9; ++i) {
43
​
44
            for (unsigned short j = 0; j < 9; ++j) 
45
                this->numberMap[i][j] = *item++;
46
            // this->numberMap.emplace_back(vec);
47
        }
48
    }
49

                        }
                        else {
                            this->numberMap[i][j] = 0;
                            continue;
                        }
                        // loop and reset
                    }
                    this->numberMap[i][j] = 0;
                }

                // return false;
            }
        }
        if (this->judgeWin()) {
            this->flag = true;
            return true;
        }

        else return flag;
    }

    if (i >= 9 && j >= 9) {
        this->flag = true;
        return true;
    }
}
*/
