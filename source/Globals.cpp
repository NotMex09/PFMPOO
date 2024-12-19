#include "Globals.h"

// Define the global variable
GameState currentState = MENU;
int mazeCols = 20; // Default maze columns
int mazeRows = 15; // Default maze rows
int cellSize = 40; // Default cell size
// Constants for window size
const int screenWidth = 800;
const int screenHeight = 600;
bool isMultiplayer = false; // Default is single-player mode