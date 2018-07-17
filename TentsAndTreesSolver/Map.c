
#include "map.h";

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

typedef enum
{
	Tree,
	Ground,
	Tent
} TileType;

typedef struct {
	int id;
	int x;
	int y;
	TileType tileType;
} Tile;

Tile** tiles;
int tileCount;
int width;
int height;

void CreateMap(int w, int h) {
	width = w;
	height = h;
	tileCount = w * h;

	tiles = malloc(w * h * sizeof(Tile));
	CreateTiles();
}

void CreateTiles() {

	int currentNumber = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Tile* newTile = malloc(sizeof(Tile));
			newTile->id = currentNumber;
			newTile->x = x;
			newTile->y = y;
			newTile->tileType = Ground;

			currentNumber++;
		}
	}
}

void DestroyMap() {
	for (int i = 0; i < tileCount; i++) {
		free(tiles[i]);
	}
	free(tiles);
}

void ProcessInput(bool stop) {
	while (!stop) {

	}
}