#pragma once

#include <stdio.h>

#include "ConsoleText.h"

/// Constructor and Destructor for the sudoku puzzle
void CreateSudoku(int _size);
void DestroySudoku(void);

/// Create the numbers that are in the sukudok puzzle
void CreateNumbers(int amount);

/// Functions for display the sudoku puzzle
void Display(void);
void ShowNumbers(void);
void ShowBorders(void);