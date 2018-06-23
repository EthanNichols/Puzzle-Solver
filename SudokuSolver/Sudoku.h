#pragma once

#include <stdio.h>

#include "../GeneralScripts/ConsoleText.h"
#include "../GeneralScripts/InputManager.h"

/// Constructor and Destructor for the sudoku puzzle
void CreateSudoku(int _size);
void DestroySudoku(void);
void CreateNumbers(int amount);

/// Getter Functions
unsigned short GetSudokuSize();
unsigned short GetSudokuWidth();
unsigned short GetSudokuHeight();
unsigned short GetSudokuNumber(unsigned short id);
bool* GetPossibleNumbers(unsigned short id);

/// Thread function for moving around the sudoku puzzle
void ProcessInput(void* stop);
void SetSudokuNumber(unsigned short id, unsigned short number);
bool TestHintSudokuNumber(unsigned short id);
void SetHoverPosition(unsigned short id);

/// Functions for solving and testing numbers
void SetPossibleNumsTrue(unsigned short id);
void SetPossibleNumsFalse(unsigned short id);
void SetPossibleNumValue(unsigned short id, unsigned short val, bool possible);
bool CompareSudokuNumbers(unsigned short id1, unsigned short id2);

/// Functions for display the sudoku puzzle
void Display(void);
void UpdateNumber(int id);
void ShowNumbers(void);
void ShowBorders(void);
void ShowControls(void);