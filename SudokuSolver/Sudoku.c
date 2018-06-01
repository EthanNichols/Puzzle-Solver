#include "Sudoku.h"

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

unsigned short size = 0;
unsigned short width = 0;
unsigned short height = 0;

void CreateSudoku(int _size) {
	size = _size;
	height = size * size + size;
	width = height * 2;
}

void Display(void)
{
	if (size == 0) { return; }

	SetConsoleColors(Black, White);

	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {

			//The four outer corners
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

					//Top and bottom corners
					if (y == 0) {
						printf("%c", middleTopCorner);
						continue;
					}
					else if (y == height) {
						printf("%c", middleBottomCorner);
						continue;
					}

					//Left and Right corners
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

				//Horizontal borders
				printf("%c", horizontalBorder);
				continue;
			}

			//Vertical borders
			if (x % ((size + 1) * 2) == 0) {
				printf("%c", verticalBorder);
				continue;
			}

			//Spaces (for numbers or for cleanliness)
			printf(" ");
		}

		//Next row
		printf("\n");
	}
}