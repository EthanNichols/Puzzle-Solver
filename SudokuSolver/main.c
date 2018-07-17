#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB 

#include <stdio.h>
#include <Windows.h>
#include <pthread.h>

#include "../GeneralScripts/ConsoleText.h"
#include "../GeneralScripts/InputManager.h"

#include "Sudoku.h"
#include "Solvers.h"

int main(int argc, char* argv[]) {
	
	//Set the window that is active
	SetWindow(GetStdHandle(STD_OUTPUT_HANDLE));

	//Create and display the start of a sudoku puzzle
	CreateSudoku(3);
	SetSudokuInfo();
	Display();

	bool stop = false;

	//Edit the sudoku puzzle
	ProcessInput(stop);

	BackTracing();
	//TestSolve();

	ResetConsoleColor();

	//Wait for user input before exiting the program
	getchar();

	//Destroy any memory allocated for the sudoku puzzle
	DestroySudoku();

	return 0;
}