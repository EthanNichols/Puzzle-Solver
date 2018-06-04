#include <stdio.h>
#include <Windows.h>
#include <thread>

#include "ConsoleText.h"
#include "InputManager.h"

#include "Sudoku.h"

int main(int argc, char* argv) {
	
	//Set the window that is active
	SetWindow(GetStdHandle(STD_OUTPUT_HANDLE));

	printf("Welcome to the Sudoku Solver!\n");
	printf("Size of the Sudoku Puzzle (Normal is 3): ");

	int num = 0;
	while (num == 0) {
		printf("hi");
	}

	//Clear the screen
	ClearScreen(4);

	//Create and display the start of a sudoku puzzle
	CreateSudoku(num);
	Display();

	SetCursorPosition(0, 15);
	ResetConsoleColor();

	//Wait for user input before exiting the program
	getchar();

	//Destroy any memory allocated for the sudoku puzzle
	DestroySudoku();
}