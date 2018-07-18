#pragma once

#include "../GeneralScripts/GeneralStructs.h"
#include "../GeneralScripts/ConsoleText.h"
#include "../GeneralScripts/InputManager.h"

void CreateMap(int width, int height);
void CreateTiles();
void DestroyMap();

int GetTileID(Vector2 pos);

void ProcessInput();

void UpdateTileDisplay(int id);
void DisplayMap();