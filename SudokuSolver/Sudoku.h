#pragma once

#include <stdio.h>

#include "ConsoleText.h"
#include "InputManager.h"

/// Constructor and Destructor for the sudoku puzzle
void CreateSudoku(int _size);
void DestroySudoku(void);
void GetSudokuInformation(unsigned short* _size, unsigned short* _width, unsigned short* _height);

/// Thread function for moving around the sudoku puzzle
void ProcessInput(void* stop);
void SetSudokuNumber(unsigned short id, unsigned short number);
unsigned short GetSudokuNumber(unsigned short id);
bool TestHintSudokuNumber(unsigned short id);
void SetHoverPosition(unsigned short id);
/// Functions for solving and testing numbers
bool CompareSudokuNumbers(unsigned short id1, unsigned short id2);

/// Create the numbers that are in the sukudok puzzle
void CreateNumbers(int amount);

/// Functions for display the sudoku puzzle
void Display(void);
void UpdateNumber(int id);
void ShowNumbers(void);
void ShowBorders(void);
void ShowControls(void);