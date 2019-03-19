#ifndef _SUDOKU_HPP_
#define _SUDOKU_HPP_

extern bool win;
// size_t timev;

#include <algorithm>
#include <ctime>
#include <array>
#include <initializer_list>

class Sudoku {

private:
    bool judgeRow(unsigned short col);
    bool judgeCol(unsigned short row);
    bool judgeBck(unsigned short col, unsigned short row);
    bool judgeWin();

public:
    Sudoku() = delete;
    Sudoku(const Sudoku &);
    Sudoku(const int map[9][9]);
    Sudoku(const std::array<std::array<unsigned short, 9>, 9> numberMap);
    Sudoku(const std::initializer_list<unsigned short> numberMap);
    virtual ~Sudoku();

    bool reaction();

private:
    // std::vector<std::vector<unsigned int>> numberMap;
    std::array<std::array<unsigned short, 9>, 9> numberMap;
    time_t start, finish;

    bool _reaction();

    bool flag;

};

#endif  // _SUDOKU_HPP_