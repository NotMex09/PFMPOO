#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"

// Declare the GameState enumeration
enum GameState { MENU, DIFFICULTY_SELECTION, GAME, NOMBRE_SELECTION, HELP, DEVS };

// Declare the global game state variable
extern GameState currentState;
// Constants for window size
const int screenWidth ;
const int screenHeight;


bool isMultiplayer ; // Default is single-player mode
// Declare pictures
Texture2D HelpBut;
Texture2D ExitBut;
Texture2D DevsBut;
Texture2D BackBut;
Texture2D startbut;
Texture2D hardbut;
Texture2D easybut;
Texture2D normalbut;
Texture2D restart;
Texture2D scorebut;
Texture2D background;
int mazeCols; // Default maze columns
int mazeRows; // Default maze rows
int cellSize; // Default cell size
int mazeRows;
int cellSize;
Sound buttonSound; // Sounds declaration
Sound winnerSound;
Sound bgSound;
Sound hardSound;
Sound PantherSound;
#endif // GLOBALS_H
#pragma once
