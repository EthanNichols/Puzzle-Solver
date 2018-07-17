#include "Sudoku.h"

//Information that every number in the sudoku puzzle  needs
typedef struct {
	int id;
	unsigned short number;
	unsigned short correctNum;
	short x;
	short y;
	Color backgroundColor;
	Color textColor;
	bool hint;
	bool hovering;
	bool* possibleNum;
} sudokuNumber;

#pragma region Codes for the borders characters
const char horizontalBorder = 205;
const char verticalBorder = 186;

const char bottomLeftCorner = 200;
const char middleLeftCorner = 204;
const char topLeftCorner = 201;

const char bottomRightCorner = 188;
const char middleRightCorner = 185;
const char topRightCorner = 187;

const char middleTopCorner = 203;
const char middleBottomCorner = 202;
const char centerCorner = 206;
#pragma endregion
#pragma region Text colors for sudoku numbers
const Color correctT = DarkGreen;
const Color correctB = White;

const Color wrongT = DarkRed;
const Color wrongB = White;

const Color nothingColor = Grey;
const Color hoveringColor = Blue;
const Color defaultTextColor = Black;
const Color defaultBackgrounColor = White;
#pragma endregion

/// Information about the puzzle
unsigned short size = 0;
unsigned short width = 0;
unsigned short height = 0;

//Offset of the sudoke puzzle
unsigned short xOffset = 0;
unsigned short yOffset = 1;

//Array of numbers in the puzzle and the size of the array
sudokuNumber** numbers;
unsigned int numberCount = 0;
unsigned int hoveringNumber = 0;

bool editingPuzzle = true;

#pragma region Creations and Deletion of the Sudoku puzzle
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
			newNumber->id = currentNumber;
			newNumber->number = 0;
			newNumber->correctNum = 0;
			newNumber->x = x;
			newNumber->y = y;
			newNumber->possibleNum = malloc(sizeof(bool) * (size*size));
			newNumber->backgroundColor = nothingColor;
			newNumber->textColor = Black;
			newNumber->hovering = false;
			newNumber->hint = false;

			//Add the number to an array of sudoku numbers
			numbers[currentNumber] = newNumber;
			SetPossibleNumsTrue(currentNumber);
			currentNumber++;
		}
	}

	numbers[hoveringNumber]->hovering = true;
}

/// De-allocate all of the numbers that were allocated
/// For the sudoku puxxle and the array itself
void DestroySudoku(void) {

	//Free all the numbers in the sudoku puzzle
	for (int i = 0; i < numberCount; i++) {
		free(numbers[i]->possibleNum);
		free(numbers[i]);
	}

	//Free the array itself
	free(numbers);
}
#pragma endregion

#pragma region Getter Functions
unsigned short GetSudokuSize() {
	return size;
}
unsigned short GetSudokuWidth() {
	return width;
}
unsigned short GetSudokuHeight() {
	return height;
}
/// Get the value that a sudoku number has
///
/// id - The position of the sudoku number
/// return - The value of the sudoku number
unsigned short GetSudokuNumber(unsigned short id) {
	if (id >= numberCount) {
		return 0;
	}
	return numbers[id]->number;
}

/// Get all of the possible values in a sudoku number
///
/// return The possible numbers array
bool* GetPossibleNumbers(unsigned short id) {
	return numbers[id]->possibleNum;
}
#pragma endregion

#pragma region Possible Number Setting Functions
/// Set all of the possible numbers that a sudoku number to true
///
/// sudokuNum - The sudoku number being edited
void SetPossibleNumsTrue(unsigned short id) {
	for (int i = 0; i < (size*size); i++) {
		numbers[id]->possibleNum[i] = true;
	}
}

/// Set all of the possible numbers that a sudoku number to false
///
/// sudokuNum - The sudoku number being edited
void SetPossibleNumsFalse(unsigned short id) {
	for (int i = 0; i < (size*size); i++) {
		numbers[id]->possibleNum[i] = true;
	}
}

/// Set one of the numbers to be possible or not possible
///
/// id - The id of the sudoku number being edited
/// val - The possible number that is being changed
/// possible - Set whether the possible number is true or false
void SetPossibleNumValue(unsigned short id, unsigned short val, bool possible)
{
	if (val < 1 || val > size*size) return;
	numbers[id]->possibleNum[val - 1] = possible;
}
#pragma endregion

#pragma region Compare and solving functions
/// Compare two sudoku numbers to each other
///
/// id1 - First number being compared
/// id2 - Second number being compared
/// retun - Whether the numbers are the same or not 
bool CompareSudokuNumbers(unsigned short id1, unsigned short id2, bool testPossibleNumbers)
{
	//Test if the possible number matches in both sudoku numbers
	if (testPossibleNumbers) {
		for (int i = 0; i < size*size; i++) {
			if (numbers[id1]->possibleNum[i] && numbers[id2]->possibleNum[i]) {
				return true;
			}
		}
	}

	//If the numbers are the same return true
	if (numbers[id1]->number == numbers[id2]->number) {
		return true;
	}

	//If the numbers are different return false
	return false;
}

/// Test if a sudoku number only has one possible number
/// id - The sudoku number being tested
/// return - The single possible number or 0 (if there isn't a single possible number)
unsigned short TestSinglePossibleNumber(unsigned short id) {

	//The first possible number found
	unsigned short firstNum = 0;
	
	//Loop through all of the possible numbers
	for (int i = 0; i < size*size; i++) {
		if (numbers[id]->possibleNum[i]) {

			//If a first possible number was found return false;
			if (firstNum > 0) {
				return 0;
			}
			firstNum = i;
		}
	}

	return firstNum+1;
}

/// Get whether the sudoku number is a a hint for the puzzle
/// 
/// id - The position of the sudoku number
/// return - True if it is a hint, false if it isn't a hint
bool TestHintSudokuNumber(unsigned short id)
{
	return numbers[id]->hint;
}
#pragma endregion

/// Place a assigned number to a sudoku number
///
/// sudokuNum - The sudoku number being assigned
/// num - The value being set to the sudoku number
void PlaceNumber(sudokuNumber* sudokuNum, short num) {
	//Don't change the value of the number if it's already correct
	if (sudokuNum->hint && !editingPuzzle) {
		return;
	}

	//Set the new information about the number
	sudokuNum->number = num;
	sudokuNum->backgroundColor = defaultBackgrounColor;
	sudokuNum->textColor = defaultTextColor;
	UpdateNumber(hoveringNumber);

	//Set numbers that are changed in edit mode to be correct by default
	if (editingPuzzle) {
		sudokuNum->correctNum = num;
		sudokuNum->hint = true;

		if (num == 0)
		{
			SetPossibleNumsTrue(sudokuNum->id);
			sudokuNum->hint = false;
		}
		else
		{
			SetPossibleNumsFalse(sudokuNum->id);
			SetPossibleNumValue (sudokuNum->id, num, true);
		}
	}
}

/// Thread function for moving around the sudoku puzzle
///
/// stop - Whether testing for input should stop or not
void ProcessInput(bool stop)
{
	Display();
	
	short offset = (editingPuzzle) ? 5 : 6;

	while (!stop) {

		//Set the cursor to be below the sudoku puzzle
		SetCursorPosition(0, size * (size + 1) + offset + yOffset);
		ResetConsoleColor();

		//Get the char inputted by the user, and the value of the input
		char input = InputChar();
		int val = input - '0';

		//If the value inputted was a number update the sudoku number
		if (val >= 0 && val <= size*size) {

			PlaceNumber(numbers[hoveringNumber], val);
		}

		//Set the new position to the current position
		int newPosition = hoveringNumber;

		//Move the hovering position relative to the key input
		switch (input)
		{
		case 'w':
			//Move up
			newPosition -= size * size;
			if (newPosition <= 0) {
				newPosition = numberCount + hoveringNumber - (size*size);
			}
			break;
		case 'a':
			//Move left
			newPosition--;
			if ((newPosition + 1) % (size*size) == 0) {
				newPosition = hoveringNumber + (size*size) - 1;
			}
			break;
		case 's':
			//Move down
			newPosition += size * size;
			break;
		case 'd':
			//Move right
			newPosition++;
			if (newPosition % (size*size) == 0) {
				newPosition = hoveringNumber - (size*size) + 1;
			}
			break;
		case 'e':
			//Exit
			stop = true;
			break;
		}

		//Keep the new position inside the sudoku puzzle bounds
		newPosition = newPosition % numberCount;

		//Test if the new position is different from the current position
		if (newPosition != hoveringNumber) {
			SetHoverPosition(newPosition);
		}
	}

	editingPuzzle = false;
	return NULL;
}

/// Set the number given the id of the sudoku number
///
/// id - The position of the sudoku number
/// number - The new number the sudoku should be set to
void SetSudokuNumber(unsigned short id, unsigned short number)
{
	if (id >= numberCount || numbers[id]->hint) {
		return;
	}
	numbers[id]->number = number;
}

#pragma region Display Functions
/// Set the hovering position on the puzzle
/// This basically just changes the background of the number
///
/// id - The position of the sudoku number
void SetHoverPosition(unsigned short id)
{
	//Reset the current number that is currently being hovered over
	numbers[hoveringNumber]->hovering = false;
	UpdateNumber(hoveringNumber);

	//Set the current position to the new position
	hoveringNumber = id;

	//Set the new number that is being hovered over and update the number
	numbers[hoveringNumber]->hovering = true;
	UpdateNumber(hoveringNumber);
}

/// Generaly display function that update the border and numbers
/// On the sudoku puzzle
void Display(void) {
	ShowBorders();
	ShowNumbers();
	ShowControls();
}

/// Update a specific number's content and colors
/// id - The location of the number in the array
void UpdateNumber(int id) {

	if (id >= numberCount) {
		return;
	}

	//Get a pointer to the number in the array
	sudokuNumber* num = numbers[id];

	//Set the cursor position and the the colors for the number
	SetCursorPosition(num->x + xOffset, num->y + yOffset);
	SetConsoleColors(num->textColor, num->backgroundColor);

	//Change the background color if the number is being hovered over
	if (num->hovering) {
		SetBackgroundColor(hoveringColor);
	}
	else if (num->number == 0) {
		SetSolidColor(nothingColor);
	}

	//Display the number if there is one
	if (num->number != 0) {
		printf("%d", num->number);
	}
	//If there isn't one display an empty space
	else {
		printf(" ");
	}
}

/// Display the numbers and information that is
/// Filled in on the sudoku puzzle
void ShowNumbers(void) {

	//Loop through all of the numbers in the sudoku puzzle
	for (int i = 0; i < numberCount; i++) {
		UpdateNumber(i);
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

			SetCursorPosition(x + xOffset, y + yOffset);

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
			if (y % (size + 1) == 0) {

				//Check for X corners and rows
				if (x % ((size + 1) * 2) == 0) {

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
	}
}

/// Display the controls for the sudoku puzzle
void ShowControls(void) {

	//Display the mode that the puzzle is in
	SetCursorPosition(0, 0);
	ResetConsoleColor();
	if (editingPuzzle) {
		printf("Editing Sudoku Puzzle");
	}
	else {
		printf("Solving Sudoku Puzzle");
	}

	//Display the controls
	SetCursorPosition(0, (size + 1)*size + 1 + yOffset);

	if (editingPuzzle) {
		printf("Move around the puzzle with the (blue) highlighted space using w/a/s/d\n");
		printf("Place a number using 1-%d on the (blue) highlighted space\n", size*size);
		printf("To finish editing the puzzle press 'e'\n");
		printf("Remember to press enter to run every command\n");
	}
	else {
		printf("Move around the puzzle with the (blue) highlighted space using w/a/s/d\n");
		printf("Place a number using 1-%d on the (blue) highlighted space\n", size*size);
		printf("Correct numbers are green, wrong numbers are red, and starting numbers are black\n");
		printf("Press 'q' if you would like the computer to solve the puzzle\n");
		printf("To stop solving the puzzle press 'e'\n");
	}
}
#pragma endregion