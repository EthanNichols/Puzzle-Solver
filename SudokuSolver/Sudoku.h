#pragma once

#include <stdio.h>

#include "ConsoleText.h"
#include "InputManager.h"

/// Constructor and Destructor for the sudoku puzzle
void CreateSudoku(int _size);
void DestroySudoku(void);

/// Thread function for moving around the sudoku puzzle
void* MoveHover(void* stop);

/// Create the numbers that are in the sukudok puzzle
void CreateNumbers(int amount);

/// Functions for display the sudoku puzzle
void Display(void);
void UpdateNumber(int id);
void ShowNumbers(void);
void ShowBorders(void);