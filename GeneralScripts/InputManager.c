#include "InputManager.h"

char inBuf[128];

void* ThreadInputInt(void* val) {

	*((unsigned short*)val) = InputFloat();

	return NULL;
}

float InputFloat(void)
{
	InputString();
	int num = strtol(inBuf, NULL, 10);

	return num;
}

int InputInt(void)
{
	return (int)InputFloat();
}

char InputChar(void)
{
	InputString();
	return inBuf[0];
}

char* InputString(void)
{
	fgets(inBuf, 128, stdin);
	return inBuf;
}

char KeyInput(void) {
	return _getch();
}

void* KeyInputThread(void* out) {
	printf("%c\t", *(char*)out);
	char ch = 0;
	while ((ch = _getch()) != EOF && ch != 'q') {
		*(char*)out = ch;
	}
}