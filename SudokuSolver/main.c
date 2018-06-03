
#include <stdio.h>
#include <Windows.h>

#include "ConsoleText.h"

#include "Sudoku.h"

int main(int argc, char* argv) {
	
	//Set the window that is active
	SetWindow(GetStdHandle(STD_OUTPUT_HANDLE));

	//Create and display the start of a sudoku puzzle
	CreateSudoku(3);
	Display();

	//Wait for user input before exiting the program
	getchar();

	//Destroy any memory allocated for the sudoku puzzle
	DestroySudoku();
}