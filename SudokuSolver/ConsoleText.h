#pragma once

#ifndef CONSOLE_TEXT
#define CONSOLE_TEXT

#include <Windows.h>
#include <stdbool.h>

/// List of colors that can be used
/// Note:
/// These colors are relative to the computer
/// Which means they may be different for each user
typedef enum
{
	Black = 0,
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkPurple = 5,
	DarkYellow = 6,
	Grey = 7,
	DarkGrey = 8,
	Blue = 9,
	Green = 10,
	Cyan = 11,
	Red = 12,
	Purple = 13,
	Yellow = 14,
	White = 15
} Color;

/// Set the window that is active
/// window - The console window that will be set to active
void SetWindow(HANDLE window);

/// Set that there is no window active
void UnsetWindow(void);

/// Test if there is a window that is active
/// Returns true if there is a window, false if not
bool ConsoleWindowSet();

/// Set the position of the cursor
/// x - X position of the cursor
/// y - Y position of the cursor
void SetCursorPosition(int x, int y);

/// Clear the entire screen of any text
/// The background color will be the same as the
/// Current background color
void ClearScreen(void);

/// Update the color font to match the current color
/// Pulls the color font and background color to set
/// And update the color pallette to diaply
void UpdateFontColor(void);

/// Set the text color with a number or the color enum
/// color - The color wanted for the text
void SetFontColor(unsigned short color);

/// Set the background color with a number or the color enum
/// color - The color wanted for the background
void SetBackgroundColor(unsigned short color);

/// Set both the text and background color with a number or the color enum
/// textColor - The color wanted for the text
/// backgroundColor - The color wanted for the background
void SetConsoleColors(unsigned short textColor, unsigned short backgroundColor);

/// Set both the text and background color to the same color number or enum
/// color - The color wanted
void SetSolidColor(unsigned short color);

/// Reset the font color back to black background and
/// White text like the default
void ResetConsoleColor();
#endif