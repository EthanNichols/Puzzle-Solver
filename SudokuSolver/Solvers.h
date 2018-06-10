#pragma once

#include "Sudoku.h"

/// Initialization function
void SetSudokuInfo(void);

/// Compare function
bool CompareRow(unsigned short x, unsigned short y);
bool CompareColumn(unsigned short x, unsigned short y);
bool CompareSquare(unsigned short x, unsigned short y);

/// Solving Fuctions
void BackTracing(void);