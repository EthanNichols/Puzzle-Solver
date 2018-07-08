#pragma once
#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB 

#include <pthread.h>

#include "Sudoku.h"

/// Testing Function
void TestSolve();

/// Initialization function
void SetSudokuInfo(void);

/// Thread functions
void* RowThread(void* row);
void* ColumnThread(void* column);
void* BlockThread(void* block);
void RunThread(void);

/// Compare function
bool CompareRow(unsigned short x, unsigned short y, bool testPossibleNumbers);
bool CompareColumn(unsigned short x, unsigned short y, bool testPossibleNumbers);
bool CompareBlock(unsigned short x, unsigned short y, bool testPossibleNumbers);

void ComparePossibleRowNumbers(unsigned short x, unsigned short y);
void ComparePossibleColumnNumbers(unsigned short x, unsigned short y);
void ComparePossibleBlockNumbers(unsigned short x, unsigned short y);

/// Solving Fuctions
void BackTracing(void);
void BowmanBingo(void);
void SimpleSolve(void);
void AdvancedSolve(void);