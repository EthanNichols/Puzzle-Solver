#pragma once
#define HAVE_STRUCT_TIMESPEC
#define PTW32_STATIC_LIB 

#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <pthread.h>

void* ThreadInputInt(void* val);

int InputInt(void);
float InputFloat(void);
char InputChar(void);
char* InputString(void);

void KeyInput();
void* KeyInputThread(void* out);