#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB 

#include <stdio.h>
#include <Windows.h>
#include <pthread.h>

#include "ConsoleText.h"
#include "InputManager.h"

#include "Sudoku.h"
#include "Solvers.h"

int main(int argc, char* argv) {
	
	//Set the window that is active
	SetWindow(GetStdHandle(STD_OUTPUT_HANDLE));

	int num = 0;
	while (num == 0) {
		ClearScreen(4);
		SetCursorPosition(0, 0);
		ResetConsoleColor();
		printf("Welcome to the Sudoku Solver!\n");
		printf("Size of the Sudoku Puzzle (Normal is 3): ");
		num = InputInt();
	}

	//Clear the screen
	ClearScreen(4);

	//Create and display the start of a sudoku puzzle
	CreateSudoku(num);
	SetSudokuInfo();
	Display();

	bool* stop = malloc(sizeof(bool));
	*stop = false;

	//Edit the sudoku puzzle
	ProcessInput(stop);

	*stop = false;
	ProcessInput(stop);

	BackTracing();

	ResetConsoleColor();

	//Wait for user input before exiting the program
	getchar();

	//Destroy any memory allocated for the sudoku puzzle
	DestroySudoku();
}