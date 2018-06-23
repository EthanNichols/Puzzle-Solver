#include "Solvers.h"

/// Information about the puzzle
unsigned short size;
unsigned short width;
unsigned short height;
unsigned short numberCount;

bool stop_threads = false;

void SetSudokuInfo(void) {
	size = GetSudokuSize();
	width = GetSudokuWidth();
	height = GetSudokuHeight();
	numberCount = size*size*size*size;
}

#pragma region Comparing Functions
/// Compare all of the numbers in the row of the position being tested
///
/// x - The x position being tested
/// y - The y position being tested
/// return - Whether there is another position with the same number
bool CompareRow(unsigned short x, unsigned short y)
{
	//The id of the number being tested and if there are conflicts
	unsigned short id1 = x + y * (size*size);
	bool conflicts = false;

	//Loop through the entire row
	for (int i = 0; i < size*size; i++) {
		
		//Don't compare the number being tested to itself
		if (i == x) continue;

		//Set the id of the number being tested against
		unsigned short id2 = i + y * (size*size);

		//Compare the numbers and set the result to conflict
		conflicts = CompareSudokuNumbers(id1, id2);

		//If there is a conflict stop comparing numbers
		if (conflicts) break;
	}

	//Return whether there was a number conflict or not
	return conflicts;
}

/// Compare all of the numbers in the column of the position being tested
///
/// x - The x position being tested
/// y - The y position being tested
/// return - Whether there is another position with the same number
bool CompareColumn(unsigned short x, unsigned short y)
{
	//The id of the number being tested and if there are conflicts
	unsigned short id1 = x + y * (size*size);
	bool conflicts = false;
	
	//Loop through the entire column
	for (int i = 0; i < size*size; i++) {

		//Don't compare the number being tested to itself
		if (i == y) continue;

		//Set the id of the number being tested against
		unsigned short id2 = x + i * (size*size);

		//Compare the numbers and set the result to conflict
		conflicts = CompareSudokuNumbers(id1, id2);

		//If there is a conflict stop comparing numbers
		if (conflicts) break;
	}

	//Return whether there was a number conflict or not
	return conflicts;
}

/// Compare all of the numbers in the square of the position being tested
///
/// x - The x position being tested
/// y - The y position being tested
/// return - Whether there is another position with the same number
bool CompareBlock(unsigned short x, unsigned short y)
{
	//The id of the number being tested and if there are conflicts
	unsigned short id1 = x + y * (size*size);
	bool conflicts = false;

	//Get the X and Y position of the square the number is in
	unsigned short squareX = (unsigned int)(x / size);
	unsigned short squareY = (unsigned int)(y / size);

	//Loop through the square that the number being tested is located int
	for (int y1 = 0; y1 < size; y1++) {
		for (int x1 = 0; x1 < size; x1++) {

			//Set the id of the number being tested against
			unsigned short id2 = squareX*size + squareY * (size*size*size) + x1 + (y1 * (size*size));

			//Don't compare the number being tested to itself
			if (id1 == id2) continue;

			//Compare the numbers and set the result to conflict
			conflicts = CompareSudokuNumbers(id1, id2);

			//If there is a conflict stop comparing numbers
			if (conflicts) break;
		}
		//If there is a conflict stop comparing numbers
		if (conflicts) break;
	}

	//Return whether there was a number conflict or not
	return conflicts;
}

/// Set any possible numbers that are wrong to be false
/// This function checks all other sudoku numbers in the same row
///
/// x - The X position of the sudoku being tested
/// y - The Y position of the sudoku number being tested
void ComparePossibleRowNumbers(unsigned short x, unsigned short y)
{
	
	//The id of the number being tested
	unsigned short id1 = x + y * (size*size);

	//Loop through the entire row
	for (int i = 0; i < size*size; i++) {

		//Don't compare the number being tested to itself
		if (i == x) continue;

		//Set the id of the number being tested against
		unsigned short id2 = i + y * (size*size);

		SetPossibleNumValue(id1, GetSudokuNumber(id2), false);
	}
}
/// Set any possible numbers that are wrong to be false
/// This function checks all other sudoku numbers in the same column
///
/// x - The X position of the sudoku being tested
/// y - The Y position of the sudoku number being tested
void ComparePossibleColumnNumbers(unsigned short x, unsigned short y)
{
	//The id of the number being tested
	unsigned short id1 = x + y * (size*size);

	for (int i = 0; i < size*size; i++) {

		//Don't compare the number being tested to itself
		if (i == y) continue;

		//Set the id of the number being tested against
		unsigned short id2 = x + i * (size*size);

		SetPossibleNumValue(id1, GetSudokuNumber(id2), false);
	}
}
/// Set any possible numbers that are wrong to be false
/// This function checks all other sudoku numbers in the same block
///
/// x - The X position of the sudoku being tested
/// y - The Y position of the sudoku number being tested
void ComparePossibleBlockNumbers(unsigned short x, unsigned short y)
{
	//The id of the number being tested
	//Get the X and Y position of the square the number is in
	unsigned short id1 = x + y * (size*size);
	unsigned short squareX = (unsigned int)(x / size);
	unsigned short squareY = (unsigned int)(y / size);

	//Loop through the square that the number being tested is located int
	for (int y1 = 0; y1 < size; y1++)
	{
		for (int x1 = 0; x1 < size; x1++)
		{
			//Set the id of the number being tested against
			unsigned short id2 = squareX * size + squareY * (size*size*size) + x1 + (y1 * (size*size));

			//Don't compare the number being tested to itself
			if (id1 == id2) continue;

			SetPossibleNumValue(id1, GetSudokuNumber(id2), false);
		}
	}
}
#pragma endregion

#pragma region Thread Compare Functions
void* RowThread(void* row)
{

}

void* ColumnThread(void* column)
{
}

void* BlockThread(void* block)
{
}

void RunThread()
{
	short sudokuNums = size * size;
	while (!stop_threads) {
		for (int i = 0; i < sudokuNums; i++) {

		}
	}
}
#pragma endregion

/// This is for testing purposes only
void TestSolve() {
	ComparePossibleRowNumbers(0, 0);
	ComparePossibleColumnNumbers(0, 0);
	ComparePossibleBlockNumbers(0, 0);

	bool* nums = GetPossibleNumbers(0);

	SetCursorPosition(0, 20);
	for (int i = 0; i < (size*size); i++) {
		(nums[i]) ? printf("%d, True, ", i+1) : printf("%d, False, ", i+1);
	}
}

#pragma region Solving Functions

/// Solve the sudoku puzzle using back tracing
/// Starting in the upper-left hand corner ( left -> right, top -> bottom)
/// At each position that isn't a hint increment the number and test if
/// The guessed number could possibly be correct
/// If it's wrong go to the previous position and increment that value by 1
/// Repeat the process until the puzzle is solved or is impossible to solve
void BackTracing(void) {

	//Loop through all the numbers in the puzzle
	for (int i = 0; i < numberCount; ++i) {

		SetHoverPosition(i);

		//Don't test or change hint values
		if (TestHintSudokuNumber(i)) continue;
		
		//Get the value of the sudoku number
		unsigned short curNum = GetSudokuNumber(i);

		//If the value is maxed reset the value and go back
		if (curNum >= size*size) {
			SetSudokuNumber(i, 0);
			UpdateNumber(i);
			i--;

			//Keep going back while the previous number is a hint
			while (TestHintSudokuNumber(i)) {
				i--;
			}

			//Counter the increment when it goes to the beginning of the for loop
			i--;
			continue;
		}

		//Get the position of the sudoku number
		unsigned short x = i % (size*size);
		unsigned short y = (unsigned short)(i / (size*size));

		//Set the new value of the sudoku number
		SetSudokuNumber(i, (curNum+1));

		//Update the display of the number
		UpdateNumber(i);

		//Test if it fits in the row
		if (CompareRow(x, y)) {
			i--;
			continue;
		}
		//Test if it fits in the column
		if (CompareColumn(x, y)) {
			i--;
			continue;
		}
		//Test if it fits in the square
		if (CompareBlock(x, y)) {
			--i;
			continue;
		}
	}
}

/// This is a simple Solve with randomness
/// The puzzle is first simple solved to find easy correct numbers
/// The randomly starts to solve all the squares for possible numbers
void BowmanBingo(void) {

}

/// This will try simple methodes of solving a puzzle
/// The puzzle will eventually get solved, but slowly
void SimpleSolve(void) {

}

/// This is the most advanced technique
/// Trying to solve the puzzle quickly and efficiently
void AdvancedSolve(void) {

}
#pragma endregion