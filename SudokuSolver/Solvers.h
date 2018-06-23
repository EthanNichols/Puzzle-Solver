#pragma once

#include <pthread.h>

#include "Sudoku.h"

/// Initialization function
void SetSudokuInfo(void);

/// Thread functions
void* RowThread(void* row);
void* ColumnThread(void* column);
void* BlockThread(void* block);

/// Compare function
bool CompareRow(unsigned short x, unsigned short y);
bool CompareColumn(unsigned short x, unsigned short y);
bool CompareBlock(unsigned short x, unsigned short y);

/// Solving Fuctions
void BackTracing(void);