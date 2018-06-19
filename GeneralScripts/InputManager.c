#include "InputManager.h"

char inBuf[128];

int InputInt(void)
{
	return InputFloat();
}

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
