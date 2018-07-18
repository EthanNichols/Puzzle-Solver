
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

const char treeChar = 209;
const char groundChar = 176;
const char tentChar = 'A';
#pragma endregion
#pragma region Text colors for sudoku numbers
const Color treeColor = DarkGreen;
const Color groundColor = Black;
const Color tentColor = Cyan;
const Color tileBackgroundColor = DarkYellow;
const Color hoveringColor = Blue;
#pragma endregion

typedef enum
{
	Tree,
	Ground,
	Tent
} TileType;

typedef struct {
	int id;
	Vector2 position;
	TileType tileType;
	bool hovering;
} Tile;

Tile** tiles;
int tileCount;
Vector2 mapSize;
Vector2 hoverPosition;

void CreateMap(int w, int h) {
	mapSize.x = w;
	mapSize.y = h;
	tileCount = w * h;

	tiles = malloc(w * h * sizeof(Tile));
	CreateTiles();
}

void CreateTiles() {

	int currentNumber = 0;
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			Tile* newTile = malloc(sizeof(Tile));
			newTile->id = currentNumber;
			newTile->position.x = x;
			newTile->position.y = y;
			newTile->tileType = Ground;
			newTile->hovering = false;

			tiles[currentNumber] = newTile;
			currentNumber++;
		}
	}
	tiles[0]->hovering = true;
}

void DestroyMap() {
	for (int i = 0; i < tileCount; i++) {
		free(tiles[i]);
	}
	free(tiles);
}

int GetTileID(Vector2 pos) {
	return pos.x + pos.y * mapSize.x;
}

void ProcessInput() {

	bool stop = false;
	while (!stop) {

		SetCursorPosition(20, 0);
		char ch = InputChar();
		if (ch == 'e') {
			stop = true;
			continue;
		}
		
		int numVal = ch - '0';
		if (numVal >= 0 && numVal <= 9) {
			switch (numVal)
			{
			case 1:
				tiles[GetTileID(hoverPosition)]->tileType = Ground;
				break;
			case 2:
				tiles[GetTileID(hoverPosition)]->tileType = Tree;
				break;
			case 3:
				tiles[GetTileID(hoverPosition)]->tileType = Tent;
				break;
			default:
				continue;
			}
			UpdateTileDisplay(GetTileID(hoverPosition));
		}

		Vector2 prevHoverPos = hoverPosition;

		switch (ch)
		{
			case 'w':
				hoverPosition.y--;
				if (hoverPosition.y < 0) {
					hoverPosition.y += mapSize.y;
				}
				break;
			case 'a':
				hoverPosition.x--;
				if (hoverPosition.x < 0) {
					hoverPosition.x += mapSize.x;
				}
				break;
			case 's':
				hoverPosition.y = (hoverPosition.y + 1) % mapSize.y;
				break;
			case 'd':
				hoverPosition.x = (hoverPosition.x + 1) % mapSize.x;
				break;
			default:
				break;
		}

		if (!CompareVector2(prevHoverPos, hoverPosition)) {
			tiles[GetTileID(prevHoverPos)]->hovering = false;
			UpdateTileDisplay(GetTileID(prevHoverPos));
			tiles[GetTileID(hoverPosition)]->hovering = true;
			UpdateTileDisplay(GetTileID(hoverPosition));
		}
	}
}

void UpdateTileDisplay(int id) {

	char ch = 0;
	Color charColor = White;

	SetCursorPosition(tiles[id]->position.x, tiles[id]->position.y);

	switch (tiles[id]->tileType)
	{
		case Ground:
			ch = groundChar;
			charColor = groundColor;
			break;
		case Tree:
			ch = treeChar;
			charColor = treeColor;
			break;
		case Tent:
			ch = tentChar;
			charColor = tentColor;
			break;
	}
	SetConsoleColors(charColor, tileBackgroundColor);

	if (tiles[id]->hovering) {
		SetBackgroundColor(hoveringColor);
	}

	printf("%c", ch);
}

void DisplayMap() {
	for (int i = 0; i < tileCount; i++) {
		UpdateTileDisplay(i);
	}
}