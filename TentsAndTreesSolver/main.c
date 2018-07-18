#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB 

#include <stdio.h>
#include <Windows.h>
#include <pthread.h>

#include "../GeneralScripts/InputManager.h"

#include "Map.h"

int main(int argc, char* argv[]) {

	SetWindow(GetStdHandle(STD_OUTPUT_HANDLE));

	int width = 0;
	int height = 0;

	printf("Input width: ");
	width = InputInt();
	printf("Input Height: ");
	height = InputInt();

	CreateMap(width, height);
	DisplayMap();
	ProcessInput();

	getchar();

	UnsetWindow();
	return 0;
}