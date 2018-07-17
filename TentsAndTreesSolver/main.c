#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB 

#include <stdio.h>
#include <Windows.h>
#include <pthread.h>

#include "../GeneralScripts/InputManager.h"

int main(int argc, char* argv[]) {

	pthread_t inputThread;
	char keyInput = 'a';
	pthread_create(&inputThread, NULL, KeyInputThread, &keyInput);



	while (1) {
		printf("%c\n", keyInput);
	}

	pthread_join(inputThread, NULL);
	//KeyInput();

	return 0;
}