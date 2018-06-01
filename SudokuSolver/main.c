
#include <stdio.h>
#include <Windows.h>

#include "ConsoleText.h"

#include "Sudoku.h"

int main(int argc, char* argv) {

	SetWindow(GetStdHandle(STD_OUTPUT_HANDLE));

	CreateSudoku(5);
	Display();

	getchar();
}