#include "InputManager.h"

char inBuf[128];

int InputInt(void)
{
	return InputFloat();
}

void* ThreadInputInt(void* val) {
	val = (int)InputFloat();
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
	scanf_s("%c", inBuf);
	return inBuf;
}
