#include "Sudoku.h"

//Information that every number in the sudoku puzzle  needs
typedef struct {
	unsigned short number;
	int x;
	int y;
	Color backgroundColor;
	Color textColor;
} sudokuNumber;

#pragma region Codes for the borders characters
char horizontalBorder = 205;
char verticalBorder = 186;

char bottomLeftCorner = 200;
char middleLeftCorner = 204;
char topLeftCorner = 201;

char bottomRightCorner = 188;
char middleRightCorner = 185;
char topRightCorner = 187;

char middleTopCorner = 203;
char middleBottomCorner = 202;
char centerCorner = 206;
#pragma endregion
#pragma region Text colors for sudoku numbers
Color correctT = DarkGreen;
Color correctB = White;

Color wrongT = DarkRed;
Color wrongB = White;

Color nothingT = Grey;
Color nothingB = Grey;
#pragma endregion


//Information about the puzzle
unsigned short size = 0;
unsigned short width = 0;
unsigned short height = 0;

//Array of numbers in the puzzle and the size of the array
sudokuNumber** numbers;
unsigned int numberCount = 0;

/// Create a sudoku puzzle given the amount of square
/// The should exist in the puzzle
void CreateSudoku(int _size) {

	//Set the local information about the puzzle
	size = _size;
	height = size * size + size;
	width = height * 2;

	//Create the numbers that are in the puzzle
	CreateNumbers(size*size*size*size);
}

/// De-allocate all of the numbers that were allocated
/// For the sudoku puxxle and the array itself
void DestroySudoku(void) {
	for (int i = 0; i < numberCount; i++) {
		free(numbers[i]);
	}

	free(numbers);
}

/// Generaly display function that update the border and numbers
/// On the sudoku puzzle
void Display(void) {
	ShowBorders();
	ShowNumbers();
}

/// Create and store the numbers that are on the sudoku puzzle
/// amount - The amount of numbers on the puzzle
void CreateNumbers(int amount) {

	//Malloc enough memory to store all of the number for the sudoku puzzle
	numbers = malloc(amount * sizeof(sudokuNumber));
	numberCount = amount;

	//The current sudoku number being edited in the array
	int currentNumber = 0;

	//Loop through the entire sudoku puzzle
	for (int y = 1; y <= height; y++) {

		//Skip all rows that are border
		if (y % (size + 1) == 0) { continue; }

		for (int x = 1; x < width; x++) {

			//Skip all columns that are borders
			//And skip every other row for spacing
			if (x % ((size + 1) * 2) == 0 || x % 2 == 1) { continue; }

			//Create a new number to display
			sudokuNumber* newNumber = malloc(sizeof(sudokuNumber));
			newNumber->number = 0;
			newNumber->x = x;
			newNumber->y = y;
			newNumber->backgroundColor = nothingB;
			newNumber->textColor = nothingT;

			//Add the number to an array of sudoku numbers
			numbers[currentNumber] = newNumber;
			currentNumber++;
		}
	}
}

/// Display the numbers and information that is
/// Filled in on the sudoku puzzle
void ShowNumbers(void) {

	//Loop through all of the numbers in the sudoku puzzle
	for (int i = 0; i < numberCount; i++) {

		//Get a pointer to the number in the array
		sudokuNumber* num = numbers[i];

		//Set the cursor position and the color of the text
		SetCursorPosition(num->x, num->y);
		SetConsoleColors(num->textColor, num->backgroundColor);

		//Display the number if there is one
		if (num->number != 0) {
			printf("%d", num->number);
		}
		//If there isn't one display an empty space
		else {
			SetConsoleColors(nothingT, nothingB);
			printf(" ");
		}
	}
}

/// Diplsay the borders and background of the sudoku puzzle
void ShowBorders(void)
{
	//Return if there is no sudoku puzzle
	if (size == 0) { return; }

	//Set the colors to use for the background and the text
	SetConsoleColors(Black, White);

	//Loop thorugh the entire sudoku puzzle
	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {

			//Display the four outer corners
			if (x == 0 && y == 0) {
				printf("%c", topLeftCorner);
				continue;
			}
			else if (x == 0 && y == height) {
				printf("%c", bottomLeftCorner);
				continue;
			}
			else if (x == width && y == 0) {
				printf("%c", topRightCorner);
				continue;
			}
			else if (x == width && y == height) {
				printf("%c", bottomRightCorner);
				continue;
			}

			//Check for Y corners and rows
			if (y%(size+1) == 0) {

				//Check for X corners and rows
				if (x % ((size+1) * 2) == 0) {

					//Display the top and bottom corners
					if (y == 0) {
						printf("%c", middleTopCorner);
						continue;
					}
					else if (y == height) {
						printf("%c", middleBottomCorner);
						continue;
					}

					//Display the left and Right corners
					if (x == 0) {
						printf("%c", middleLeftCorner);
						continue;
					}
					else if (x == width) {
						printf("%c", middleRightCorner);
						continue;
					}
					else {
						printf("%c", centerCorner);
						continue;
					}
				}

				//Display the horizontal borders
				printf("%c", horizontalBorder);
				continue;
			}

			//Display the vertical borders
			if (x % ((size + 1) * 2) == 0) {
				printf("%c", verticalBorder);
				continue;
			}

			//Display the Spaces (for numbers or for cleanliness)
			printf(" ");
		}

		//Go to the next display row
		printf("\n");
	}
}