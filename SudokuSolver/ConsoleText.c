#include "ConsoleText.h"

//Window that is currently active
HANDLE consoleWindow = NULL;

//The font and background color to dispay
unsigned short fontColor = 15;
unsigned short backgroundColor = 0;

/// Set the window that is active
/// window - The console window that will be set to active
void SetWindow(HANDLE window) {
	consoleWindow = window;
}

/// Set that there is no window active
void UnsetWindow(void) {
	consoleWindow = NULL;
}

/// Test if there is a window that is active
/// Returns true if there is a window, false if not
bool ConsoleWindowSet() {
	if (!consoleWindow) {
		return false;
	}
	else {
		return true;
	}
}

/// Set the position of the cursor
/// x - X position of the cursor
/// y - Y position of the cursor
void SetCursorPosition(int x, int y) {
	if (!ConsoleWindowSet) { return; }
	SetConsoleCursorPosition(consoleWindow, (COORD) { x, y });
}

/// Clear the entire screen of any text
/// The background color will be the same as the
/// Current background color
void ClearScreen(void) {
}

/// Update the color font to match the current color
/// Pulls the color font and background color to set
/// And update the color pallette to diaply
void UpdateFontColor(void) {
	if (!ConsoleWindowSet) { return; }
	unsigned short setColor = fontColor + backgroundColor*16;
	SetConsoleTextAttribute(consoleWindow, setColor);
}

/// Set the text color with a number or the color enum
/// color - The color wanted for the text
void SetFontColor(unsigned short color) {
	fontColor = color%16;
	UpdateFontColor();
}

/// Set the background color with a number or the color enum
/// color - The color wanted for the background
void SetBackgroundColor(unsigned short color) {
	backgroundColor = (color%16);
	UpdateFontColor();
}

/// Set both the text and background color with a number or the color enum
/// textColor - The color wanted for the text
/// backgroundColor - The color wanted for the background
void SetConsoleColors(unsigned short textColor, unsigned short backgroundColor) {
	SetFontColor(textColor);
	SetBackgroundColor(backgroundColor);
}

/// Set both the text and background color to the same color number or enum
/// color - The color wanted
void SetSolidColor(unsigned short color) {
	SetFontColor(color);
	SetBackgroundColor(color);
}

/// Reset the font color back to black background and
/// White text like the default
void ResetConsoleColor() {
	fontColor = 15;
	backgroundColor = 0;
	UpdateFontColor();
}